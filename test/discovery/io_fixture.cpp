#include "pch.h"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <regex>

#include "io_fixture.h"
#include "Err.h"
#include "Str.h"


void RedirectAppsStdIO::RedirectIO(fs::path dir, fs::path file_cin, fs::path file_cout)
	{
	auto fout = dir / file_cout;
	auto fin = dir / file_cin;
	
	assert(fs::exists(fin));
	
	// redirect fin to cin
	std::cout << "Input source will be redirected from: " << std::endl << fin << std::endl;
	in_fs = std::ifstream(fin);
	cin_buf = std::cin.rdbuf();
	std::cin.rdbuf(in_fs.rdbuf());
	
	// redirect cout to fout
	std::cout << "Output target will be duplicated to: " << std::endl << fout;
	out_fs = std::ofstream(fout, std::ios_base::trunc);
	cout_buf = std::cout.rdbuf();
	std::cout.rdbuf(out_fs.rdbuf());
	}


void RedirectAppsStdIO::TearDown()
	{
	//reset to standard IO again
	if (cin_buf)
		{
		std::cin.rdbuf(cin_buf);
		cin_buf = nullptr;
		}
		
	if (cout_buf)
		{
		std::cout.rdbuf(cout_buf);
		cout_buf = nullptr;
		}
	}


VStrPairs DiscoverApps::DiscoverAppTests(fs::path apps_dir)
	{
	assert(apps_dir.filename() == "apps");
	VStrPairs result;
	
	for (fs::path& app : FIO::get_files(apps_dir))
		{
		fs::path cases_dir = app / "test/fixtures";
		if (!fs::exists(cases_dir))
			{
			Log::Warning("Test cases not found in: " + cases_dir.string());
			continue;
			}
			
		for (fs::path& f : FIO::get_files(cases_dir))
			{
			if (IsGoodTestFile(f))
				result.push_back({ GuessTestName(f), GetTestCaseName(f) });
			}
		}
	return result;
	}


string DiscoverApps::GuessTestName(fs::path file)
	{
	fs::path test_dir = file.parent_path().parent_path().parent_path();
	assert(test_dir.parent_path().filename() == APPS_DIR);
	
	return  test_dir.filename().string();
	}


bool DiscoverApps::IsGoodTestFile(fs::path file)
	{
	string f_name = file.filename().string();
	if (!Str::starts_with(f_name, TEST_FILE_PREFIX_IN))
		return false;
		
	// TODO need correct out, not just out
	fs::path expected_out = GetCorrectOutputFName(f_name);
	if (!fs::exists(expected_out))
		Log::Warning("Test case missing correct output: " + f_name);
		
	return true;
	}


fs::path DiscoverApps::GetCorrectOutputFName(fs::path in_fname)
	{
	string fname = in_fname.string();
	Str::replace_all(fname, TEST_FILE_PREFIX_IN, TEST_FILE_PREFIX_CORRECT_OUT, true);
	return fname;
	}


fs::path DiscoverApps::GenOutputFName(fs::path in_fname)
	{
	string fname = in_fname.string();
	Str::replace_all(fname, TEST_FILE_PREFIX_IN, TEST_FILE_PREFIX_OUT, true);
	return fname;
	}


string DiscoverApps::GetTestCaseName(fs::path file)
	{
	assert(file.extension() == TEST_FILE_EXT);
	return file.filename().string();
	}

fs::path DiscoverApps::GuessTestDir(string name)
	{
	fs::path dir = fs::path(EXPECTED_APPS_DIR) / name / EXPECTED_TEST_FILES_DIR;
	
	assert(fs::exists(dir));
	return dir;
	}


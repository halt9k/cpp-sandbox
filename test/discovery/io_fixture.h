#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

#include <Vec.h>
#include "FIO.h"

using StrPair = std::pair<string, string>;
using VStrPairs = vector<StrPair>;
namespace fs = std::filesystem;

constexpr auto EXPECTED_APPS_DIR = "../../src/apps";
// ..\..\src\apps\TEST_NAME\test\fixtures
constexpr auto EXPECTED_TEST_FILES_DIR = "test/fixtures";

// in_*.txt, out_*.txt
constexpr auto TEST_FILE_EXT = ".txt";
constexpr auto TEST_FILE_PREFIX_IN = "in_";
constexpr auto TEST_FILE_PREFIX_OUT = "out_";
constexpr auto TEST_FILE_PREFIX_CORRECT_OUT = "out_correct_";
constexpr auto APPS_DIR = "apps";


class RedirectAppsStdIO: public::testing::TestWithParam<StrPair>
	{
	protected:
		// TODO
		std::streambuf* cin_buf = NULL;
		std::streambuf* cout_buf = nullptr;
		
		std::ifstream in_fs;
		std::ofstream out_fs;
		
		void SetUp() override {};
		void TearDown() override;
		
	public:
		void RedirectIO(fs::path dir, fs::path file_cin, fs::path file_cout);
	};


class DiscoverApps
	{
	public:
		static fs::path GenOutputFName(fs::path input_fname);
		static fs::path GenCorrectOutputFName(fs::path input_fname);
		
		static fs::path GuessTestDir(string test_name);
		static string GuessTestName(fs::path input_file);
		static string GetTestCaseName(fs::path input_file);
		
		static bool IsGoodTestFile(fs::path file);
		
		static VStrPairs DiscoverAppTests(fs::path dir);
	};

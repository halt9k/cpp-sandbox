#include <filesystem>

#include <windows.h>

#include "hr_wrap.h"

#include "IO.h"
#include "Str.h"


VStr IO::read_input()
	{
	VStr result;
	
	string line;
	while (getline(cin, line))
		result.push_back(line);
	return result;
	}


// TODO improve
VStr IO::read_text_input(string fname)
	{
	
	assert(std::filesystem::exists(fname));
	
	VStr result;
	std::ifstream fin(fname);
	string line;
	
	while (getline(fin, line))
		result.push_back(line);
		
	fin.close();
	
	return result;
	}


void IO::write_text_output(string fname, VStr& lines)
	{
	// ofstream fout("./out/out.txt");
	std::ofstream fout(fname);
	
	for (auto& line : lines)
		{
		cout << line << endl;
		fout << line << endl;
		}
		
	fout.close();
	}

void IO::open_dir(string dirname)
	{
	ShellExecuteA(NULL, "open", dirname.c_str(), NULL, NULL, SW_SHOWDEFAULT);
	}


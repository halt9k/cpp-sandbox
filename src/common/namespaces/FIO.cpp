#include <windows.h>
#include <iostream>
#include <stdexcept>

#include "FIO.h"
#include "Str.h"
#include "Err.h"

using std::cout;
using std::cin;
using std::getline;
using std::endl;


VStrs FIO::cin_read_lines()
	{
	VStrs result;
	
	string line;
	while (getline(cin, line))
		result.push_back(line);
	return result;
	}


VPaths FIO::get_files(fs::path dir)
	{
	VPaths files;
	if (!fs::exists(dir))
		{
		Log::Warning("Unexpected missing dir: " + dir.string());
		return files;
		}
		
	for (const auto& entry : fs::directory_iterator(dir))
		files.push_back(entry.path());
	return files;
	}


void FIO::cout_output_lines(VStrs& lines)
	{
	for (auto& line : lines)
		cout << line << endl;
	}


void FIO::open_windows_explorer_at(string dirname)
	{
	ShellExecuteA(NULL, "open", dirname.c_str(), NULL, NULL, SW_SHOWDEFAULT);
	}


#include <windows.h>
#include <iostream>
#include <fstream>
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
		{
		if (line.empty())
			{
			Log::Warning("Input is finished due to empty line.\n\
						 Supposed to happen only under manual input mode.\n");
			break;
			}
		result.push_back(line);
		}
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


class input_line
	{
	std::string data;
	public:
		friend std::istream& operator>>(std::istream& is, input_line& l)
			{
			std::getline(is, l.data);
			return is;
			}
		operator std::string() const { return data; }
	};
using line_iterator = std::istream_iterator<input_line>;


VStrs FIO::read_file_lines(fs::path fpath)
	{
	auto fs = std::ifstream(fpath);
	return VStrs{ line_iterator(fs), line_iterator() };
	}


/*
bool FIO::compare_text_files(fs::path f1, fs::path f2)
	{
	auto s1 = std::ifstream(f1);
	auto s2 = std::ifstream(f2);

	lines1 = VStrs{ line_iterator(f1), line_iterator() };
	lines2 = VStrs{ line_iterator(f2), line_iterator() };
	
	return lines1 == lines2;
	}
*/


void FIO::open_windows_explorer_at(string dirname)
	{
	ShellExecuteA(NULL, "open", dirname.c_str(), NULL, NULL, SW_SHOWDEFAULT);
	}


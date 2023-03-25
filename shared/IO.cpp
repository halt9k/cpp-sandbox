#include <filesystem>
#include <cassert>

#include "IO.h"
#include "Str.h"



VecStr IO::read_input()
	{
	VecStr result;
	
	string line;
	while (getline(cin, line))
		result.push_back(line);
	return result;
	}


// TODO improve
VecStr IO::read_text_input(string fname)
	{
	assert(filesystem::exists(fname));
	
	VecStr result;
	ifstream fin(fname);
	string line;
	
	while (getline(fin, line))
		result.push_back(line);
		
	fin.close();
	
	return result;
	}


void IO::write_text_output(string fname, VecStr& lines)
	{
	// ofstream fout("./out/out.txt");
	ofstream fout(fname);
	
	for (auto& line : lines)
		{
		cout << line << endl;
		fout << line << endl;
		}
		
	fout.close();
	}

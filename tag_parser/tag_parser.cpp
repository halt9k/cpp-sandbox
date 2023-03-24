#include <cassert>
#include <exception>

#include "stdc++.h"

#include "Str.h"
#include "Arr.h"
#include "IO.h"


typedef map<string, string> DictStr;


void parse(string& line, DictStr& dict_str)
	{
	dict_str[line] = "test";
	}


void tag_parser()
	{
	VecStr lines = IO::read_text_input("test/test_parser/in_1.txt");
	
	VecInt inputs = Arr::str_to_int(Str::split(lines[0]));
	int N = inputs[0];
	int Q = inputs[1];
	
	cout << N << Q;
	
	DictStr dict_str;
	FOR(x, 1, N + 1)
		{
		parse(lines[x], dict_str);
		}
		
		
	VecStr out_lines;
	for (auto const& [key, val] : dict_str)
		out_lines.push_back(key + ' ' + val);
		
		
	IO::write_text_output("test/test_parser/out_1.txt", out_lines);
	}


int main()
	{
	tag_parser();
	return getwchar();
	}
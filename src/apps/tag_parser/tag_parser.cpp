#include <sstream>

#include "hr_extended.h"
#include "sandbox_adapter.h"

using DictStr = std::map<string, string>;


void parse(string& line, DictStr& dict_str, string& cur_path)
	{
	assert(line.size() > 2);
	VStrs words = Str::split(line, " =");
	assert(words.size() > 0);
	
	string& tag = words.front();
	string& w_last = words.back();
	
	Str::safe_erase(w_last, -1, ">");
	Str::safe_erase(tag, 0, "<");
	
	bool is_closing_tag = (tag[0] == '/');
	if (is_closing_tag)
		{
		Str::safe_erase(tag, 0, "/");
		Str::safe_erase(cur_path, cur_path.size() - tag.size(), tag);
		if (cur_path.size() > 1)
			Str::safe_erase(cur_path, -1, ".");
		return;
		}
	else
		{
		if (cur_path.size() > 0)
			cur_path += '.';
		cur_path += tag;
		words.erase(words.begin());
		}
		
	while (words.size() > 0)
		{
		assert(words.size() % 2 == 0);
		string attr = words[0];
		string attr_val = words[1];
		
		Str::safe_erase(attr_val, 0, "\"");
		Str::safe_erase(attr_val, -1, "\"");
		
		dict_str[cur_path + '~' + attr] = attr_val;
		
		words.erase(words.begin(), words.begin() + 2);
		}
		
	}


void tag_parser()
	{
	VStrs lines = FIO::cin_read_lines();
	
	VInts inputs = Vec::str_to_int(Str::split(lines[0]));
	int N = inputs[0];
	int Q = inputs[1];
	
	// cout << N << Q << endl;
	
	DictStr dict_str;
	string cur_path = "";
	FOR(x, 1, N)
		{
		parse(lines[x], dict_str, cur_path);
		}
		
	VStrs out_lines;
	FOR(x, N + 1, N + Q)
		{
		string req = lines[x];
		
		if (dict_str.count(req) > 0)
			out_lines.push_back(dict_str[req]);
		else
			out_lines.push_back("Not Found!");
		}
		
	FIO::cout_output_lines(out_lines);
	}


int main()
	{
	tag_parser();
	return 0;
	}
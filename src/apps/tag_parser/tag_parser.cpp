#include <cassert>
#include <sstream>

#include "hr_wrap.h"
#include "surpress_crt.h"
#include "sandbox.h"

#include "Str.h"
#include "Vec.h"
#include "IO.h"


typedef std::map<string, string> DictStr;


void parse(string& line, DictStr& dict_str, string& cur_path)
	{
	assert(line.size() > 2);
	VStr words = Str::split(line, " =");
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
	VStr lines = IO::read_text_input("../test/tag_parser/in_5.txt");
	
	VInt inputs = Vec::str_to_int(Str::split(lines[0]));
	int N = inputs[0];
	int Q = inputs[1];
	
	// cout << N << Q << endl;
	
	DictStr dict_str;
	string cur_path = "";
	FOR(x, 1, N)
		{
		parse(lines[x], dict_str, cur_path);
		}
		
	VStr out_lines;
	FOR(x, N + 1, N + Q)
		{
		string req = lines[x];
		
		if (dict_str.count(req) > 0)
			out_lines.push_back(dict_str[req]);
		else
			out_lines.push_back("Not Found!");
		}
		
	IO::write_text_output("test/tag_parser/out_1.txt", out_lines);
	}


int main()
	{
	surpress_crt();
	
	tag_parser();
	return 0;
	}
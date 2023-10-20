#pragma once
#include <functional>
#include <cstring>

#include "Vec.h"

using std::vector;
using std::string;

using StrRef = const string&;


// Not using boost, etc intentionally in this specific project
namespace Str
	{
	void safe_erase(string& str, int pos, StrRef sub_str);
	VStrs split(StrRef str, string delims = "");
	bool is_not_space(char c);
	string ltrim(StrRef str);
	string rtrim(StrRef str);
	
	bool starts_with(StrRef str, StrRef prefix);
	
	void replace_all(string& str, StrRef match, StrRef replace, bool must_occur);
	
	}
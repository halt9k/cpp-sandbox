#pragma once
#include "stdc++.h"
#include <functional>

#include "Arr.h"

// Not using boost, etc intentionally in this specific project
namespace Str
	{
	void safe_erase(string& str, int pos, string sub_str);
	VecStr split(const string& str, string delims = "");
	bool is_not_space(char c);
	string ltrim(const string& str);
	string rtrim(const string& str);
	}
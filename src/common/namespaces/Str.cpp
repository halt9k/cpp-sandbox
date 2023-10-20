#include <cassert>
#include <algorithm>

#include <stdexcept>

#include "Str.h"


void Str::safe_erase(string& str, int pos, StrRef sub_str)
	{
	if (pos < 0)
		pos = str.length() + pos;
		
	assert(str.substr(pos, sub_str.size()) == sub_str);
	str.erase(pos, sub_str.size());
	}


VStrs Str::split(StrRef str, string delims)
	{
	string str_copy = str;
	
	if (delims.empty())
		delims = " ";
		
	char separator = delims[0];
	if (delims.size() > 1)
		for (auto& delim : delims)
			replace(str_copy.begin(), str_copy.end(), delim, separator);
			
	VStrs tokens;
	
	string::size_type start = 0;
	
	str_copy = separator + str_copy + separator;
	for (int i = 1; i < str_copy.size(); ++i)
		{
		char& c = str_copy[i];
		char& prev = str_copy[i - 1];
		
		if ((prev == separator) == (c == separator))
			continue;
			
		if (c != separator)
			{
			start = i;
			continue;
			}
			
		tokens.push_back(str_copy.substr(start, i - start));
		}
		
	return tokens;
	}


bool Str::is_not_space(char c)
	{
	return !isspace(c);
	}


string Str::ltrim(StrRef str)
	{
	string s(str);
	s.erase(s.begin(), find_if(s.begin(), s.end(), is_not_space));
	
	return s;
	}


string Str::rtrim(StrRef str)
	{
	string s(str);
	s.erase(find_if(s.rbegin(), s.rend(), is_not_space).base(), s.end());
	
	return s;
	}


bool Str::starts_with(StrRef str, StrRef prefix)
	{
	return strncmp(str.c_str(), prefix.c_str(), prefix.size()) == 0;
	}


void Str::replace_all(string& str, StrRef from, StrRef to, bool must_occur = false)
	{
	if (must_occur)
		if (str.find(from) == string::npos)
			throw std::runtime_error("Replace substring missing");
			
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos)
		{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}
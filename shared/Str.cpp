#include "Str.h"


VecStr Str::split(const string& str)
	{
	VecStr tokens;
	
	string::size_type start = 0;
	string::size_type end = 0;
	
	while ((end = str.find(" ", start)) != string::npos)
		{
		tokens.push_back(str.substr(start, end - start));
		start = end + 1;
		}
		
	tokens.push_back(str.substr(start));
	return tokens;
	}


bool Str::is_not_space(char c)
	{
	return !isspace(c);
	}


string Str::ltrim(const string& str)
	{
	string s(str);
	s.erase(s.begin(), find_if(s.begin(), s.end(), is_not_space));
	
	return s;
	}


string Str::rtrim(const string& str)
	{
	string s(str);
	s.erase(find_if(s.rbegin(), s.rend(), is_not_space).base(), s.end());
	
	return s;
	}

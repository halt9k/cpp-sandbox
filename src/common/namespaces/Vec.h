#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

using VInts = vector<int>;
using VVInts = vector<vector<int>>;
using VStrs = vector<string>;

#define FOR_XY(x0, x1, y0, y1) for(int y = y0; y <= y1; ++y) for(int x = x0; x <= x1; ++x)
#define FOR(x, x0, x1) for(int x = x0; x <= x1; ++x)

// Not using boost, etc intentionally in this specific project
namespace Vec
	{
	template<class T>
	void print(vector<T>& arr);
	
	template<class T>
	void print_2d(vector<vector<T>>& arr_2d);
	
	VInts strs_to_ints(VStrs& strs);
	string strs_to_text(VStrs& strs);
	
	bool contains(VInts& v, int elem);
	void add_unique(VInts& arr, int n);
	}
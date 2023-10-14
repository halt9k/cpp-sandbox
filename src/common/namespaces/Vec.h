#pragma once
#include "hr_wrap.h"

typedef vector<int> VInt;
typedef vector<vector<int>> VVInt;
typedef vector<string> VStr;

#define FOR_XY(x0, x1, y0, y1) for(int y = y0; y <= y1; ++y) for(int x = x0; x <= x1; ++x)
#define FOR(x, x0, x1) for(int x = x0; x <= x1; ++x)

// Not using boost, etc intentionally in this specific project
namespace Vec
	{
	template<class T>
	void print(vector<T>& arr);
	
	template<class T>
	void print_2d(vector<vector<T>>& arr_2d);
	
	VInt str_to_int(VStr strs);
	
	bool contains(VInt& v, int elem);
	void add_unique(VInt& arr, int n);
	}
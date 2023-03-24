#pragma once
#include "stdc++.h"


typedef vector<int> VecInt;
typedef vector<vector<int>> VecVecInt;
typedef vector<string> VecStr;

#define FOR_XY(x0, x1, y0, y1) for(int y = y0; y <= y1; ++y) for(int x = x0; x <= x1; ++x)
#define FOR(x, x0, x1) for(int x = x0; x <= x1; ++x)


namespace Arr
	{
	void print_arr(VecInt& arr);
	void print_2d_arr(VecVecInt& arr_2d);
	VecInt str_to_int(VecStr strs);
	}
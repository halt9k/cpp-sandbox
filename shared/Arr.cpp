#include <iomanip>

#include "Arr.h"


void Arr::print_arr(VecInt& arr)
	{
	for (auto& it : arr)
		cout << setw(3) << it << ' ';
	cout << endl;
	}

void Arr::print_2d_arr(VecVecInt& arr_2d)
	{
	for (auto& arr : arr_2d)
		print_arr(arr);
	}

VecInt Arr::str_to_int(VecStr strs)
	{
	VecInt result;
	transform(strs.begin(), strs.end(), back_inserter(result),
	[&](string s) { return stoi(s); }
			 );
	return result;
	}


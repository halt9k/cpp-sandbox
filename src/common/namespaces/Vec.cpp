#include <iterator>
#include <algorithm>

#include "Vec.h"

using std::vector;
using std::string;


template<class T>
void Vec::print(vector<T>& arr)
	{
	for (auto& it : arr)
		cout << setw(3) << it << ' ';
	cout << endl;
	}


template<class T>
void Vec::print_2d(vector<vector<T>>& arr_2d)
	{
	for (auto& arr : arr_2d)
		print_arr(arr);
	}


VInts Vec::str_to_int(VStrs strs)
	{
	VInts result;
	result.reserve(strs.size());
	
	transform(strs.begin(), strs.end(), std::back_inserter(result),
	[&](string s) { return stoi(s); }
			 );
	return result;
	}


bool Vec::contains(VInts& v, int elem)
	{
	return std::find(v.begin(), v.end(), elem) != v.end();
	}


void Vec::add_unique(VInts& arr, int n)
	{
	if (!contains(arr, n))
		arr.push_back(n);
	}
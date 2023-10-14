#include "hr_wrap.h"
#include "sandbox.h"

#include "Vec.h"


int count_safe(VVInt& arr, int min, int max)
	{
	int n = arr.size();
	int m = n > 0 ? m = arr[0].size() : 0;
	
	VInt ex_cols, ex_rows;
	for (int y = 0; y < n; y++)
		{
		for (int x = 0; x < m; x++)
			{
			int& v = arr[y][x];
			
			if (v == max || v == min)
				{
				Vec::add_unique(ex_cols, x);
				Vec::add_unique(ex_rows, y);
				}
			}
			
		}
		
	int safe_nums_count = (m - ex_cols.size()) * (n - ex_rows.size());
	return safe_nums_count;
	}


void read_test_input(VVInt& arr, int& min, int& max)
	{
	int n, m;
	cin >> n >> m;
	
	arr = VVInt(n, VInt(m));
	min = INT_MAX;
	max = -1;
	
	for (auto& row : arr)
		{
		for (auto& l : row)
			{
			cin >> l;
			min = std::min(min, l);
			max = std::max(max, l);
			}
		}
	}


int main()
	{
	int test_count;
	cin >> test_count;
	
	int min, max;
	
	for (int _i = 0; _i < test_count; _i++)
		{
		VVInt arr;
		read_test_input(arr, min, max);
		
		int _count = count_safe(arr, min, max);
		cout << _count << endl;
		}
		
	return 0;
	}
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

using ints = vector<int>;
using ints2d = vector<vector<int>>;
bool DEBUG = false;
struct elem { int x =-1, y=-1;};


void print_arr(ints2d& arr){
	for(auto& row : arr){
		for(auto& l : row)
			cout << l << " ";
		cout << endl;
	}
}


void print_arr(ints& arr){
	for(auto& l : arr)
		cout << l << " ";
	cout << endl;
}

bool vec_contains(ints& v, int elem){
	return std::find(v.begin(), v.end(), elem) != v.end();
}


void add_unique(ints& arr, int n){
	if (!vec_contains(arr, n))
		arr.push_back(n);	
}


int count_safe(ints2d& arr, elem& el_min, elem& el_max, int min, int max){
	int n = arr.size();

	int m = 0;
	if (n > 0)
		m = arr[0].size();
	
	ints ex_cols, ex_rows;
	for (int y = 0; y < n; y++){
		ints& row = arr[y];

		for (int x = 0; x < m; x++){
			if (row[x] == max || row[x] == min){
				if (DEBUG)
					printf("match %i %i \n", x, y);

				add_unique(ex_cols, x);
				add_unique(ex_rows, y);
			}
		}

	}

	if (DEBUG){
		printf("excludes: \n");
		print_arr(ex_cols);
		print_arr(ex_rows);
	}

	int safe = (m - ex_cols.size()) * (n - ex_rows.size());

	return safe;
}


void run_test_input(ints2d& arr, elem& el_min, elem& el_max, int& min, int& max){
	int n, m;	
	cin >> n >> m;
	
	arr = ints2d(n, ints(m));
	el_min.x = 1; el_min.y = 1; min = INT_MAX;
	el_max.x = 1; el_max.y = 1; max = -1;

	if (DEBUG)
		printf("n %i m %i \n", n, m);

	for (auto& row : arr){
		for (auto& l : row){
			cin >> l;
			min = std::min(min, l);
			max = std::max(max, l);
		}
	}

	if (DEBUG){
		print_arr(arr);
		printf("min x %i y %i v %i \n", el_min.x, el_min.y, min);
		printf("max x %i y %i v %i \n", el_max.x, el_max.y, max);
	}
}


int main(){
	int tests;
	cin >> tests;

	elem el_min, el_max;
	int min, max;

	for(int test = 0; test < tests; test++){
		if (DEBUG)
			printf("test# %i \n", test);
		
		ints2d arr;
		run_test_input(arr, el_min, el_max, min, max);

		int safe = count_safe(arr, el_min, el_max, min, max);
		cout << safe << endl;
	}
}
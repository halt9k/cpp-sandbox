#include "stdc++.h"
#include <functional>
#include <cassert>
#include <iomanip>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
    Complete the 'formingMagicSquare' function below.

    The function is expected to return an INTEGER.
    The function accepts 2D_INTEGER_ARRAY m_sq as parameter.
*/

typedef vector<int> ArrInt;
typedef vector<vector<int>> Arr2D;

#define FOR_XY(x0, x1, y0, y1) for(int y = y0; y <= y1; ++y) for(int x = x0; x <= x1; ++x)


struct Pt
	{
	int x, y;
	};

typedef vector<Pt> ArrPts;

void print_arr(ArrInt& arr)
	{
	for (auto& it : arr)
		cout << setw(3) << it << ' ';
	cout << endl;
	}


void print_2d_arr(Arr2D& arr_2d)
	{
	for (auto& arr : arr_2d)
		print_arr(arr);
	}


ArrPts get_abs_max_pts(Arr2D nums)
	{
	int abs_max = abs(nums[0][0]);
	
	FOR_XY(0, 2, 0, 2)
	if (abs(nums[y][x]) > abs_max)
		abs_max = abs(nums[y][x]);
		
	ArrPts pts_max;
	if (abs_max == 0)
		return pts_max;
		
	FOR_XY(0, 2, 0, 2)
	if (abs(nums[y][x]) == abs_max)
		pts_max.push_back({x, y});
		
	return pts_max;
	}


int is_main_diag(int x, int y)
	{
	return (x == y);
	}


int is_sup_diag(int x, int y)
	{
	return (x == 2 - y);
	}


int vsum(ArrInt& arr)
	{
	return accumulate(arr.begin(), arr.end(), 0);
	}


struct LineSums
	{
	ArrInt rows = ArrInt(3);
	ArrInt cols = ArrInt(3);
	Arr2D sq;
	int diag_m = 0, diag_r = 0;
	
	int& operator[](int id)
		{
		return id < 3 ? rows[id] : cols[id - 3];
		}
		
	void calc_from(Arr2D& m_sq)
		{
		sq = m_sq;
		FOR_XY(0, 2, 0, 2)
			{
			cols[x] += m_sq[y][x];
			rows[y] += m_sq[y][x];
			
			if (is_main_diag(x, y))
				diag_m += m_sq[y][x];
			if (is_sup_diag(x, y))
				diag_r += m_sq[y][x];
			}
		}
		
	int get_magic()
		{
		int r = vsum(rows);
		int c = vsum(cols);
		assert(r == c);
		int total = vsum(rows) * 2 + diag_m + diag_r;
		return (int)round(total / 8.0);
		// return 15;
		}
		
	void print()
		{
		printf("%3s %3s %3s %3i \n", "", "", "", diag_r);
		printf("%3i %3i %3i %3i \n", sq[0][0], sq[0][1], sq[0][2], rows[0]);
		printf("%3i %3i %3i %3i \n", sq[1][0], sq[1][1], sq[1][2], rows[1]);
		printf("%3i %3i %3i %3i \n", sq[2][0], sq[2][1], sq[2][2], rows[2]);
		printf("%3i %3i %3i %3i \n\n", cols[0], cols[1], cols[2], diag_m);
		}
	};


void calc_diffs(LineSums line_sums, Arr2D& diff_sq, Arr2D& diff_sq_abs, int try_magic_n)
	{
	FOR_XY(0, 2, 0, 2)
		{
		int v = line_sums.cols[x] - try_magic_n;
		diff_sq[y][x] += v;
		diff_sq_abs[y][x] += abs(v);
		
		v = line_sums.rows[y] - try_magic_n;
		diff_sq[y][x] += v;
		diff_sq_abs[y][x] += abs(v);
		
		if (is_main_diag(x, y))
			{
			v = line_sums.diag_m - try_magic_n;
			diff_sq[y][x] += v;
			diff_sq_abs[y][x] += abs(v);
			}
		if (is_sup_diag(x, y))
			{
			v = line_sums.diag_r - try_magic_n;
			diff_sq[y][x] += v;
			diff_sq_abs[y][x] += abs(v);
			}
		}
	}


template <typename T> int sgn(T val)
	{
	return (T(0) < val) - (val < T(0));
	}


int try_fix(Arr2D nums, int step, int initial_diff, int target_magic_n, Arr2D& final_sq)
	{
	final_sq = nums;
	
	// cout << endl << " --------------------- Step " << step << endl;
	LineSums line_sums;
	line_sums.calc_from(nums);
	//print_sq(nums, line_sums);
	
	Arr2D diff_sq(3, ArrInt(3));
	Arr2D diff_sq_abs(3, ArrInt(3));
	calc_diffs(line_sums, diff_sq, diff_sq_abs, target_magic_n);
	
	// cout << "Diffs: " << endl;
	// print_2d_arr(diff_sq);
	
	// cout << "Abs diffs: " << endl;
	// print_2d_arr(diff_sq_abs);
	
	ArrPts pts = get_abs_max_pts(diff_sq);
	
	if (pts.size() == 0)
		{
		cout << "Finished for " << target_magic_n << " steps " << step << endl;
		line_sums.print();
		return step;
		}
		
	int min_step = -1;
	for (auto& pt : pts)
		{
		if (initial_diff == -1)
			initial_diff = abs(nums[pt.y][pt.x]);
			
		if (step > initial_diff + 1)
			{
			// cout << "stopped: no progress" << endl;
			return -1;
			}
			
		// cout << "Selected: " << pt.x << " " << pt.y << endl;
		Arr2D next_nums = nums;
		next_nums[pt.y][pt.x] -= sgn(diff_sq[pt.y][pt.x]);
		int fin_step = try_fix(next_nums, step + 1, initial_diff, target_magic_n, final_sq);
		if (fin_step > -1)
			{
			if (min_step == -1 || min_step > fin_step)
				min_step = fin_step;
			}
		}
		
	return min_step;
	}


int formingMagicSquare(vector<vector<int>> s)
	{
	cout << "Started with " << endl;
	LineSums line_sums;
	line_sums.calc_from(s);
	line_sums.print();
	
	Arr2D final_sq = s;
	int min_steps = -1;
	for (int tgt_m = 3; tgt_m < 3 * 9; ++tgt_m)
		{
		int steps = try_fix(s, 0, -1, tgt_m, final_sq);
		if (steps == -1)
			continue;
			
		if (min_steps == -1 || min_steps > steps)
			min_steps = steps;
		}
	return min_steps;
	}


int main()
	{
	// ofstream fout("./out/out.txt");
	ofstream fout;
	ifstream fin("./in/test_msquare1.txt");
	
	vector<vector<int>> s(3);
	
	for (int i = 0; i < 3; i++)
		{
		s[i].resize(3);
		
		string s_row_temp_temp;
		getline(fin, s_row_temp_temp);
		
		vector<string> s_row_temp = split(rtrim(s_row_temp_temp));
		
		for (int j = 0; j < 3; j++)
			{
			int s_row_item = stoi(s_row_temp[j]);
			
			s[i][j] = s_row_item;
			}
		}
		
	string s_correct_answer;
	getline(fin, s_correct_answer);
	int result = formingMagicSquare(s);
	
	cout << "Correct: " << s_correct_answer << endl;
	cout << result << "\n";
	fout << result << "\n";
	
	fout.close();
	fin.close();
	
	return getwchar();
	}

string ltrim(const string& str)
	{
	string s(str);
	
	s.erase(
		s.begin(),
		find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
	);
	
	return s;
	}

string rtrim(const string& str)
	{
	string s(str);
	
	s.erase(
		find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
		s.end()
	);
	
	return s;
	}

vector<string> split(const string& str)
	{
	vector<string> tokens;
	
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

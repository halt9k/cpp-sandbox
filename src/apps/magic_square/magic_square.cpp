#include <functional>

#include "hr_wrap.h"
#include "sandbox.h"

#include "Vec.h"
#include "Str.h"

// TODO redefine to improve
using std::ofstream;
using std::ifstream;


/*
    Complete the 'formingMagicSquare' function below.

    The function is expected to return an INTEGER.
    The function accepts 2D_INTEGER_ARRAY m_sq as parameter.
*/


struct Pt
	{
	int x, y;
	};

typedef vector<Pt> ArrPts;


ArrPts get_abs_max_pts(VVInt nums)
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


int vsum(VInt& arr)
	{
	return accumulate(arr.begin(), arr.end(), 0);
	}


struct LineSums
	{
	VInt rows = VInt(3);
	VInt cols = VInt(3);
	VVInt sq;
	int diag_m = 0, diag_r = 0;
	
	int& operator[](int id)
		{
		return id < 3 ? rows[id] : cols[id - 3];
		}
		
	void calc_from(VVInt& m_sq)
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


void calc_diffs(LineSums line_sums, VVInt& diff_sq, VVInt& diff_sq_abs, int try_magic_n)
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


int try_fix(VVInt nums, int step, int initial_diff, int target_magic_n, VVInt& final_sq)
	{
	final_sq = nums;
	
	// cout << endl << " --------------------- Step " << step << endl;
	LineSums line_sums;
	line_sums.calc_from(nums);
	//print_sq(nums, line_sums);
	
	VVInt diff_sq(3, VInt(3));
	VVInt diff_sq_abs(3, VInt(3));
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
		VVInt next_nums = nums;
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
	
	VVInt final_sq = s;
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
		
		vector<string> s_row_temp = Str::split(Str::rtrim(s_row_temp_temp));
		
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

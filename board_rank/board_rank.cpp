#include "stdc++.h"
#include <functional>
#include <cassert>
#include <iomanip>

#include "Arr.h"
#include "Str.h"
#include "IO.h"


using namespace std;
using namespace Str;


/*
    Complete the 'climbingLeaderboard' function below.

    The function is expected to return an INTEGER_ARRAY.
    The function accepts following parameters:
    1. INTEGER_ARRAY prev_scores
    2. INTEGER_ARRAY new_scores
*/

// prev_scores         100 100 50 40 40 20 10
// prev_positions      1   1   2  3  3  4  5

// new_scores          5 25 50 120
// new_ranks       ? ?  ?  ?

vector<int> estimate_ranks(vector<int>& scores)
	{
	vector<int> ranks(scores.size());
	
	int rank = 1;
	ranks[0] = 1;
	for (int i = 1; i < scores.size(); i++)
		{
		if (scores[i] < scores[i - 1])
			rank++;
		ranks[i] = rank;
		}
	return ranks;
	}

vector<int> climbingLeaderboard(vector<int> prev_scores, vector<int> new_scores)
	{
	vector<int> prev_ranks = estimate_ranks(prev_scores);
	vector<int> new_ranks(new_scores.size());
	
	for (int i = 0; i < new_scores.size(); i++)
		{
		int unk_score = new_scores[i];
		auto it = upper_bound(prev_scores.rbegin(), prev_scores.rend(), unk_score);
		int idx = - 1 - distance(prev_scores.rend(), it);
		
		if (it != prev_scores.rend())
			new_ranks[i] = prev_ranks[idx] + 1;
		else
			new_ranks[i] = 1;
		}
		
	return new_ranks;
	}


#pragma warning(disable: 4996)

#define cin fin
// int main_board_rank()
int main()
	{
	string out_f = ".\\out.txt";
	
	ofstream fout(out_f);
	if (!fout.is_open())
		{
		cout << 'ERR';
		exit(-1);
		}
		
	ifstream fin("../test/board_rank/in_1.txt");
	
	
	string ranked_count_temp;
	getline(cin, ranked_count_temp);
	
	int ranked_count = stoi(ltrim(rtrim(ranked_count_temp)));
	
	string ranked_temp_temp;
	getline(cin, ranked_temp_temp);
	
	vector<string> ranked_temp = split(rtrim(ranked_temp_temp));
	
	vector<int> ranked(ranked_count);
	
	for (int i = 0; i < ranked_count; i++)
		{
		int ranked_item = stoi(ranked_temp[i]);
		
		ranked[i] = ranked_item;
		}
		
	string player_count_temp;
	getline(cin, player_count_temp);
	
	int player_count = stoi(ltrim(rtrim(player_count_temp)));
	
	string player_temp_temp;
	getline(cin, player_temp_temp);
	
	vector<string> player_temp = split(rtrim(player_temp_temp));
	
	vector<int> player(player_count);
	
	for (int i = 0; i < player_count; i++)
		{
		int player_item = stoi(player_temp[i]);
		
		player[i] = player_item;
		}
		
	vector<int> result = climbingLeaderboard(ranked, player);
	
	for (size_t i = 0; i < result.size(); i++)
		{
		fout << result[i];
		
		if (i != result.size() - 1)
			fout << "\n";
		}
		
	fout << "\n";
	
	fout.flush();
	fout.close();
	fin.close();
	
	IO::open_dir(out_f);
	
	return 0;
	}
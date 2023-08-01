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
    2. INTEGER_ARRAY new_player_scores
*/


int get_score_position(vector<int> prev_scores, vector<int> prev_positions, int player_score, int& below_idx)
	{
	// prev_scores      100 100 50 40 40 20 10
	// prev_positions   1   1   2  3  3  4  5
	
	for (int i = below_idx; i >= 0; i--)
		{
		if (player_score < prev_scores[i])
			{
			below_idx = i;
			return prev_positions[below_idx] + 1;
			}
		}
		
	return 1;
	}


vector<int> estimate_prev_positions(vector<int> ranked)
	{
	vector<int> rank_positions(ranked.size());
	
	int cur_rank = 1;
	int prev_score = ranked[0];
	
	for (int i = 0; i < ranked.size(); ++i)
		{
		int v = ranked[i];
		if (v < prev_score)
			{
			prev_score = v;
			cur_rank++;
			}
		rank_positions[i] = cur_rank;
		}
		
	return rank_positions;
	}

vector<int> climbingLeaderboard(vector<int> prev_scores, vector<int> new_player_scores)
	{
	// prev_scores           100 100 50 40 40 20 10  idx_r<-
	// prev_positions        1   1   2  3  3  4  5
	
	// new_player_scores           5 25 50 120             idx_p->
	// player_positions            ? ?  ?  ?
	
	vector<int>& prev_positions = estimate_prev_positions(prev_scores);
	
	int below_idx = prev_scores.size() - 1;
	vector<int> player_positions(new_player_scores.size());
	for (int i = 0; i < new_player_scores.size(); ++i)
		player_positions[i] = get_score_position(prev_scores, prev_positions, new_player_scores[i], below_idx);
		
	return player_positions;
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


/*
    int main_magic_square()
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
*/
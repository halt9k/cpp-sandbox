#include <functional>

#include "hr_extended.h"
#include "sandbox_adapter.h"

using namespace Str;

// TODO redefine to improve
using std::ofstream;
using std::ifstream;
#define cin fin

/*
    Complete the 'climbingLeaderboard' function below.

    The function is expected to return an INTEGER_ARRAY.
    The function accepts following parameters:
    1. INTEGER_ARRAY prev_scores
    2. INTEGER_ARRAY new_scores
*/

// prev_scores         100 100 50 40 40 20 10  idp->
// prev_positions      1   1   2  3  3  4  5

// new_scores          5 25 50 120             idn<-
// new_ranks       ? ?  ?  ?

VInts climbingLeaderboard(VInts prev_scores, VInts new_scores)
	{
	VInts new_ranks(new_scores.size());
	
	int idp = 0, idn = new_scores.size() - 1, idp_rank = 1;
	int max_cycles = prev_scores.size() + new_scores.size();
	
	for (int i = 0; i < max_cycles; i++)
		{
		if (new_scores[idn] >= prev_scores[idp])
			{
			new_ranks[idn] = idp_rank;
			idn--;
			}
		else if (idp < prev_scores.size() - 1)
			{
			idp++;
			
			if (prev_scores[idp] < prev_scores[idp - 1])
				idp_rank++;
			}
		else // score below lowest
			{
			new_ranks[idn] = idp_rank + 1;
			idn--;
			}
			
		if (idn < 0)
			break;
		}
		
	return new_ranks;
	}


#pragma warning(disable: 4996)

void board_rank()
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
	
	VStrs ranked_temp = split(rtrim(ranked_temp_temp));
	
	VInts ranked(ranked_count);
	
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
	
	VStrs player_temp = split(rtrim(player_temp_temp));
	
	VInts player(player_count);
	
	for (int i = 0; i < player_count; i++)
		{
		int player_item = stoi(player_temp[i]);
		
		player[i] = player_item;
		}
		
	VInts result = climbingLeaderboard(ranked, player);
	
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
	
	FIO::open_windows_explorer_at(out_f);
	}


int main()
	{
	board_rank();
	return 0;
	}
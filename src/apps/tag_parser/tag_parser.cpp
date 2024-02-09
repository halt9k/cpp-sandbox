#include <sstream>

#include "hr_extended.h"
#include "sandbox_adapter.h"

using DictStr = std::map<string, string>;
using std::string_view;


inline void push_and_erase_word(VStrs& words, string& word)
	{
	words.push_back(word);
	word.clear();
	}


inline VStrs get_words_and_quotes(std::string_view& line)
	{
	assert(line.size() > 0);

	VStrs words;
	string next_word = "";
	bool in_quote = false;
	char prev_c = '\n';

	for (const char& c : line)
		{
		if (c == '"')
			{
			in_quote = !in_quote;
			if (!in_quote)
				push_and_erase_word(words, next_word);
			continue;
			}

		if (in_quote)
			{
			next_word.push_back(c);
			continue;
			}

		assert(!in_quote);

		// in word
		if (c != ' ')
			{
			next_word.push_back(c);
			continue;
			}

		// word end cases
		if (c == '=' ||
			(c == ' ' && next_word.size() > 0))
			push_and_erase_word(words, next_word);

		prev_c = c;
		}

	if (next_word.size() > 0)
		push_and_erase_word(words, next_word);

	assert(!in_quote);
	return words;
	}


void parse(string& braced_line, DictStr& dict_str, string& cur_path)
	{
	// strip braces
	assert(braced_line.front() == '<' && braced_line.back() == '>');
	string_view line(braced_line.data() + 1, braced_line.size() - 2);

	VStrs words = get_words_and_quotes(line);
	assert(words.size() > 0 && (words.size() - 1) % 3 == 0);

	string& full_tag = words.front();
	assert(full_tag.size() > 0);
	bool is_closing_tag = (full_tag[0] == '/');
	string_view tag;
	if (is_closing_tag) 
		tag = string_view(full_tag.data() + 1);
	else
		tag = string_view(full_tag);

	if (is_closing_tag)
		{
		Str::safe_erase(cur_path, cur_path.size() - tag.size(), tag.data());
		if (cur_path.size() > 1)
			Str::safe_erase(cur_path, -1, ".");
		return;
		}
	else
		{
		if (cur_path.size() > 0)
			cur_path += '.';
		cur_path += tag;
		words.erase(words.begin());
		}

	assert(words.size() % 3 == 0);
	int eqs = words.size() / 3;
	FOR(eq, 0, eqs - 1)
		{
		string attr = words[eq * 3];
		string attr_val = words[eq * 3 + 2];
		dict_str[cur_path + '~' + attr] = attr_val;
		}
	}


void tag_parser()
	{
	VStrs lines = FIO::cin_read_lines();

	VInts inputs = Vec::strs_to_ints(Str::split(lines[0]));
	int N = inputs[0];
	int Q = inputs[1];

	// cout << N << Q << endl;

	DictStr dict_str;
	string cur_path = "";
	FOR(x, 1, N - 1)
		{
		parse(lines[x], dict_str, cur_path);
		}

	VStrs out_lines;
	FOR(x, N + 1, N + Q)
		{
		string req = lines[x];

		if (dict_str.count(req) > 0)
			out_lines.push_back(dict_str[req]);
		else
			out_lines.push_back("Not Found!");
		}

	FIO::cout_output_lines(out_lines);
	}


int main()
	{
	tag_parser();
	return 0;
	}
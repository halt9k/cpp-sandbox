#include <sstream>

#include "hr_extended.h"
#include "sandbox_adapter.h"

#include <cstdio>
#include <iostream>
#include <string>

template <typename T> std::string to_str(const T& t)
	{
	std::ostringstream ss;
	ss << t;
	return ss.str();
	}

template <typename T> std::string to_str(const T& t);

void embedded_test()
	{
	// VStrs lines = FIO::cin_read_lines();

	bool service_pin_unlocked = true;
	auto test = ("pin_unlocked.val=" + to_str<int>(service_pin_unlocked)).c_str();
	cout << test;

	// VInts inputs = Vec::strs_to_ints(Str::split(lines[0]));
	// int N = inputs[0];
	// int Q = inputs[1];

	// cout << N << Q << endl;
	}


int main()
	{
	embedded_test();
	return 0;
	}
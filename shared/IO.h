#pragma once
#include "Arr.h"

// Not using boost, etc intentionally in this specific project
namespace IO
	{
	VecStr read_input();
	VecStr read_text_input(string fname);
	void write_text_output(string fname, VecStr& lines);
	}
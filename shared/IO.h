#pragma once
#include "Arr.h"

namespace IO
	{
	VecStr read_input();
	VecStr read_text_input(string fname);
	void write_text_output(string fname, VecStr& lines);
	}
#pragma once
#include "Vec.h"

// Not using boost, etc intentionally in this specific project
namespace IO
	{
	VStr read_input();
	VStr read_text_input(string fname);
	void write_text_output(string fname, VStr& lines);
	void open_dir(string dirname);
	}
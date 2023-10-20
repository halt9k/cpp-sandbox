#pragma once
#include <filesystem>

#include "Vec.h"

namespace fs = std::filesystem;
using VPaths = vector<fs::path>;

// Not using boost, etc intentionally in this specific project
namespace FIO
	{
	VStrs cin_read_lines();
	VPaths get_files(fs::path dir);
	void cout_output_lines(VStrs& lines);
	void open_windows_explorer_at(std::string dirname);
	}
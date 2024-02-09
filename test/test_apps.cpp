#include "pch.h"

#include "tag_parser/tag_parser.h"
#include "io_fixture.h"
#include "Err.h"
#include "FIO.h"
#include "Vec.h"

using std::endl;


// TODO separate into other file
string report_comparsion(VStrs& expected, VStrs& actual)
	{
	const int COLUMN_SIZE = 20;

	string result = "\n\n";
	expected.insert(expected.begin(), "Expected: ");
	actual.insert(actual.begin(), "Actual: ");

	int line_count = std::max(expected.size(), actual.size());

	if (expected.size() < line_count)
		expected.resize(line_count);
	if (actual.size() < line_count)
		actual.resize(line_count);

	for (int line = 0; line < line_count; line++)
		{
		string left = expected[line];
		if (left.size() < COLUMN_SIZE)
			left.resize(COLUMN_SIZE, ' ');
		result += left + ' ' + actual[line] + '\n';
		}
	return result + '\n';
	}



TEST_P(RedirectAppsStdIO, AutoDetect)
	{
	string app_name = GetParam().first;
	string input_file = GetParam().second;

	auto dir = DiscoverApps::GuessTestDir(app_name);
	auto fin = fs::path(input_file);
	auto fout = dir / DiscoverApps::GenOutputFName(input_file);
	auto fok = dir / DiscoverApps::GetCorrectOutputFName(input_file);

	RedirectIO(dir, fin, fout);

	if (app_name == "tag_parser")
		tag_parser();
	else
		FAIL() << "Entry function not implemented: " << app_name;

	if (!fs::exists(fok))
		FAIL() << "Expected output is missing for: " << input_file;

	// TODO optimize with intercept before file?
	VStrs result_lines = FIO::read_file_lines(fout);
	VStrs correct_result = FIO::read_file_lines(fok);

	// 	EXPECT_EQ(result_lines, correct_result);
	if (result_lines != correct_result)
		{
		FAIL() << report_comparsion(correct_result, result_lines);
		}
	else
		SUCCEED();
	}


// MSVC 2019 internal Test Adapter allows runtime test discovery,
// but has problems of too old versions
// for example, incorrect msg "!! This test has probably CRASHED !!"
// alternative extension Google Test Adapter from marketplace works fine
INSTANTIATE_TEST_CASE_P(Apps,
						RedirectAppsStdIO,
						testing::ValuesIn(DiscoverApps::DiscoverAppTests(EXPECTED_APPS_DIR)));
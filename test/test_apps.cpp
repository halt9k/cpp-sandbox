#include "pch.h"

#include "tag_parser/tag_parser.h"
#include "io_fixture.h"
#include "Err.h"


TEST_P(RedirectAppsStdIO, AutoDetect)
	{
	string app_name = GetParam().first;
	string input_file = GetParam().second;
	
	auto dir = DiscoverApps::GuessTestDir(app_name);
	auto fin = fs::path(input_file);
	auto fout = DiscoverApps::GenOutputFName(input_file);
	
	RedirectIO(dir, fin, fout);
	
	if (app_name == "tag_parser")
		tag_parser();
	else
		FAIL("Entry function not implemented: " + app_name);
		
	// TODO check with output
	EXPECT_TRUE(true);
	}


// MSVC 2019 internal Test Adapter has problem which allows runtime test discovery,
// but not proper execution; alternative extension from marketplace works fine
INSTANTIATE_TEST_CASE_P(Apps,
						RedirectAppsStdIO,
						testing::ValuesIn(DiscoverApps::DiscoverAppTests(EXPECTED_APPS_DIR)));
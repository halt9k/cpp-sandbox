#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "tag_parser.h"

TEST_CASE("TestCaseName1", "[TestName]")
	{
	REQUIRE(1 == 1);
	REQUIRE(true);
	}



TEST_CASE("set_duplicates", "[util]")
	{
	tag_parser();
	REQUIRE(true);
	}

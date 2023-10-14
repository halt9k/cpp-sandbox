#include "pch.h"
#include "surpress_crt.h"

int main(int argc, char** argv)
	{
	surpress_crt();
	
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	}
// #include "sandbox.h"
// sandbox.h has any main() are auto-renamed
// #undef main


#include "tag_parser/tag_parser.h"
#include "surpress_crt.h"


int main()
	{
	surpress_crt();
	
	// an app to run by default
	tag_parser();
	
	return 0;
	};


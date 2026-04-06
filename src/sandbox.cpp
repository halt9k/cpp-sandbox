// #include "sandbox.h"
// sandbox.h has any main() are auto-renamed
// #undef main


#include "embedded_test/embedded_test.h"
#include "surpress_crt.h"


int main()
	{
	surpress_crt();
	
	// an app to run by default
	embedded_test();
	
	return 0;
	};


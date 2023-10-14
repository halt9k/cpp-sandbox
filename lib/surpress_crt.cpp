#include "surpress_crt.h"

#include <cassert>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <iostream>

#include <windows.h>

/*
    Call of surpress_crt()
    Bypasses into breakpoints next MSVC messages:

    -------------------------- -
    Microsoft Visual C++ Runtime Library
    -------------------------- -
    Debug Error!

    Program: *

    abort() has been called

    (Press Retry to debug the application)

    -------------------------- -
    Abort   Retry   Ignore
    -------------------------- -


    -------------------------- -
    Microsoft Visual C++ Runtime Library
    -------------------------- -
    Debug Assertion Failed!

    Program: *
    File : *
    Line : 1553

    Expression : vector subscript out of range

    For information on how your program can cause an assertion
    failure, see the Visual C++ documentation on asserts.

    (Press Retry to debug the application)

    -------------------------- -
    Abort   Retry   Ignore
    -------------------------- -
*/


int __cdecl CrtDbgHook(int nReportType, char* szMsg, int* pnRet)
	{
	// void (*jump_back_to_return)(void) = (void (*)())pnRet;
	// jump_back_to_return();
	
	std::string msg = szMsg;
	std::cout << msg;
	
	std::string msg_info = msg.substr(msg.rfind(':') + 1);
	OutputDebugStringA(msg_info.c_str());
	
	// asserts will exit() silent without this
	// throw std::runtime_error(szMsg);
	
	// TODO
	// If you exclude this file from your code, breakpoint will be unwinded above as desired!
	if (nReportType == 1)
		_CrtDbgBreak(pnRet);
		
	// Abort, Retry, Ignore dialog will not be displayed
	return false;
	}

void surpress_crt()
	{
	// Note: to prevent MSVC entering _CrtDbgBreak(); disable symbols load and enable "Just My Code"
	
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	
	// _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_WNDW);
	// _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	
	_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, CrtDbgHook);
	}

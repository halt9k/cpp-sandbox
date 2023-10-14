/*
    MSVC tends to show Abort Retry Ignore message on misc errors
    where you would like to step on a breakpoint directly

    This cpp tries to fix this and to bypass into breakpoint.

    Fixes next MSVC messages:

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


#include "surpress_crt.h"

#include <cassert>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <iostream>

#include <windows.h>


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
	
	// To prevent MSVC entering _CrtDbgBreak(),
	// 1) disable symbols load
	// 2) enable "Just My Code"
	// 3) Set specifically for this cpp:
	//      Debug information format -> None
	
	if (nReportType == 1)
		_CrtDbgBreak(pnRet);
		
	// Abort, Retry, Ignore dialog will not be displayed
	return true;
	}

void surpress_crt()
	{
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	
	_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, CrtDbgHook);
	}

#include "surpress_crt.h"

// #include <stdexcept>
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
	// 1) disable all-auto symbols load
	// 2) enable "Just My Code"
	// 3) Set specifically for this cpp (right click on this file in Solution Explorer):
	//      Debug information format -> None (clean .obj if it was createdd previously)
	
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

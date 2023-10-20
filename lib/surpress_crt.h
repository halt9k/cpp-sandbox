#pragma once

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


// Bypasses Abort Retry Ignore dialog under MSVC
void surpress_crt();

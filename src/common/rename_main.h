#pragma once
// use case:
// multiple examples in same project simultaneously tested
// and easy copy-paste to/from without renaming main()

#include <vector>

// do not delete 2nd line
#define STR(x) XSTR(x)
#define XSTR(x) #x

#define MERGE_(a,b)  a##b
#define LABEL_(a) MERGE_(main_, a)

// # define UNDER_COUNTER_ MERGE_(_, __COUNTER__)
// #define UNIQUE_RENAME(prev_name) MERGE_(prev_name, UNDER_COUNTER_)


#define UNIQUE_MAIN_ LABEL_(__LINE__)
#define main UNIQUE_MAIN_
#pragma message("Main redefined; example: " STR(main))

// -------------------------------------------------
// Contain Macros to use throughout the code.
// -------------------------------------------------
#pragma once

#include <cstdio>

#ifdef _DEBUG
    #define DEBUG_PRINT(...) std::printf(__VA_ARGS__);
#else
    #define DEBUG_PRINT(...)
#endif
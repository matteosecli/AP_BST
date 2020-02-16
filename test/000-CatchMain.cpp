// 000-CatchMain.cpp

// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN   // This has to appear ONLY in one file!

#include "catch.hpp"

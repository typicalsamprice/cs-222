/**
 * Week {WEEKNUM} - CS 222 - UW Whitewater - Spring 2024
 * Sam Price - DATE - TIME STARTED
 * Compiled with both Clang and GCC. Not MSVC since I
 * don't run Windows.
 *
 * Compliant with C++11, and should be forward compatible with
 * C++14, C++17 and C++20 (maybe the last is shaky?)
 */

#include <iostream>
#include <iomanip>
// Live by the uint32_t, die by the uint32_t
#include <cstdint>
#include <string>

// For me :)
// Remember (to me and the reader!) you can disable
// assertions with the -DNDEBUG flag (define the NDEBUG symbol)
#include <cassert>

// Document symbols used for ifdefs:

// Document way to format arguments for command line input:

// This program will validate/expect malicious input: TRUE or FALSE
// If false, expected input is:

int main(int argc, char *argv[]) {
    // If you ever see a `using namespace std;` without justification
    // from me, you have permission to immediately fail me (that is a joke)
    using std::cout;
    using std::endl;
    using std::string;

    // Yes, they're used I prommy
    (void)argc;
    (void)argv;

    return 0;
}

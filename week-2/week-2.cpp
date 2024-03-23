/**
 * Week 2 - CS 222 - UW Whitewater - Spring 2024
 * Sam Price - 2/5 - 13:53
 * Compiled with both Clang and GCC. Not MSVC since I
 * don't run Windows.
 *
 * Compliant with C++11, and should be forward compatible with
 * C++14, C++17 and C++20 (maybe the last is shaky?)
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
// Live by the uint32_t, die by the uint32_t
#include <cstdint>
#include <string>

// For me :)
// Remember (to me and the reader!) you can disable
// assertions with the -DNDEBUG flag (define the NDEBUG symbol)
#include <cassert>
#include <vector>

#include <numeric>

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

    double wage = 0;
    int32_t days = 0;

    cout << "Enter hourly rate: ";
    std::cin >> wage;
    if (wage < 15) {
        cout << "Required wage at least $15.00. Exiting" << endl;
        return 1;
    }

    cout << "Enter number of days to input: ";
    std::cin >> days;
    if (days <= 0) {
        cout << "Please enter at least 1 day" << endl;
        return 2;
    }

    // A true std::vector is the best you can get I believe, since VLAs only exist in C, not C++.
    double *wages = (double *)calloc(days, sizeof(double));

    for (int i = 0; i < days; i++) {
        cout << "Day " << i + 1 << " Hours: ";
        double hours = 0;
        std::cin >> hours;
        if (hours < 0) {
            cout << "Cannot work negative hours, exiting." << endl;
            return 3;
        } else if (hours > 24) {
            cout << "How on Earth did you work more than 24 hours in a day? Not required to, but I'll exit anyways." << endl;
            return 3;
        }
        wages[i] = hours;
    }

    double total_hours = 0.0;
    for (int i = 0; i < days; i++)
        total_hours += wages[i];

    free(wages); // I didn't do this in the lab, but it doesn't matter. We have an OS that will reclaim the memory after the program ends.
    wages = nullptr; // Just do this to avoid double-free or UAF errors.

    double total_wages = wage * total_hours;
    double avg_wages = total_wages/total_hours;
    double avg_hours = total_hours / double(days);
    double month_expected = avg_hours * 30.00 * wage;

    cout << "You worked a total of " << total_hours << " hours over " << days << " days." << endl;
    cout << "During this time, you made $" << total_wages << "." << endl;
    cout << "On average, you worked " << avg_hours << " hours per day." << endl;
    cout << "Over the next 30 days, you can expect to make $" << month_expected << "." << endl;

    return 0;
}

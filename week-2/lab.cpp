/**
 * Lab 2 - CS 222 - UW Whitewater - Spring 2024
 * Sam Price - 2/5 - 14:20
 * Compiled with both Clang and GCC. Not MSVC since I
 * don't run Windows.
 *
 * Compliant with C++11, and should be forward compatible with
 * C++14, C++17 and C++20 (maybe the last is shaky?)
 */

#include <cstddef>
#include <iostream>
#include <iomanip>
// Live by the uint32_t, die by the uint32_t
#include <cstdint>
#include <numeric>
#include <string>

// For me :)
// Remember (to me and the reader!) you can disable
// assertions with the -DNDEBUG flag (define the NDEBUG symbol)
#include <cassert>

#include <vector>

// Document symbols used for ifdefs:

// Document way to format arguments for command line input:

// This program will validate/expect malicious input: TRUE
// If false, expected input is:

double get_average(double*, size_t);

int main(int argc, char *argv[]) {
    // If you ever see a `using namespace std;` without justification
    // from me, you have permission to immediately fail me (that is a joke)
    using std::cout;
    using std::endl;
    using std::string;

    // Yes, they're used I prommy
    (void)argc;
    (void)argv;

    cout << "Number of assignments to enter: ";
    int32_t assignments_count = 0;
    std::cin >> assignments_count;
    if (assignments_count <= 0) {
        cout << "Cannot analyze 0 or fewer assignments" << endl;
        return 1;
    }
    double *grades = (double *)calloc(assignments_count, sizeof(double));

    for (int i = 0; i < assignments_count; i++) {
        cout << "Assignment " << i + 1 << " Grade [0-100]: ";
        double grade = 0;
        std::cin >> grade;
        if (grade < 0 || grade > 100) {
            cout << "That is not a possible grade within [0, 100]. Exiting." << endl;
            return 2;
        }
        grades[i] = grade;
    }

    double avg_grade = get_average(grades, assignments_count);
    cout << "\nReport Card" << endl;
    cout << "-----------------" << endl;
    cout << "Scores: ";
    for (size_t i = 0; i < assignments_count; i++)
        cout << grades[i] << (i == assignments_count - 1 ? "" : ", ");

    cout << endl;
    cout << "Average: " << avg_grade << endl;


    return 0;
}

double get_average(double *vec, size_t len) {
    double rv = 0;
    for (size_t i = 0; i < len; i++) {
        rv += vec[i];
    }
    return rv/double(len);
}

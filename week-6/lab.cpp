// -*- compile-command: "g++ -o lab lab.cpp -std=c++17 -Wall"; -*-
#include <string>
#include <iostream>

// Hacky but eat it, no dynamically allocated arrays
#define LEN(x) ((sizeof(x))/(sizeof(*x)))

template <typename T>
void print(T arr[], size_t len) {
    std::cout << "{";
    for (size_t i = 0; i < len; i++) {
        // You say no other classes, but not sure how to without using
        // this.
        std::cout << arr[i] << (i < (len - 1) ? "," : "");
    }
    std::cout << "}" << std::endl;
}

template <typename T>
void sort(T arr[], size_t len) {
    // Bubble sort that garbo
    bool swapped = false;
    do {
        swapped = false;
        for (size_t i = 1; i < len; i++) {
            if (arr[i - 1] < arr[i]) {
                std::swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        len--;
    } while(swapped);
}
int main() {

// {{{
int integers[100] = { 31, 21, 47, 16, 48, 26, 62, 11, 82, 96, 45, 20, 75, 37,
39, 24, 18, 38, 35, 13, 36, 93, 23, 3, 67, 51, 59, 28, 94, 61, 98, 64, 1, 52, 65,
60, 34, 76, 78, 25, 32, 12, 44, 14, 92, 17, 66, 53, 74, 56, 42, 99, 71, 50, 83, 57,
5, 86, 68, 80, 8, 81, 30, 43, 49, 33, 40, 87, 85, 63, 89, 100, 90, 46, 70, 73, 88,
9, 84, 54, 97, 58, 10, 55, 27, 95, 6, 91, 69, 72, 22, 41, 4, 29, 15, 77, 79, 2, 19,
7 };
double doubles[100] = { 0.15, 0.12, 0.31, 0.21, 0.49, 0.44, 0.07, 0.11, 0.02,
0.22, 0.3, 0.43, 0.08, 0.05, 0.09, 0.25, 0.41, 0.16, 0.47, 0.46, 0.19, 0.48, 0.01,
0.17, 0.18, 0.46, 0.23, 0.23, 0.29, 0.38, 0.41, 0.13, 0.28, 0.04, 0.32, 0.18, 0.45,
0.16, 0.44, 0.38, 0.42, 0.43, 0.42, 0.02, 0.3, 0.36, 0.35, 0.27, 0.2, 0.34, 0.37,
0.29, 0.01, 0.15, 0.48, 0.09, 0.33, 0.13, 0.26, 0.37, 0.2, 0.36, 0.06, 0.4, 0.08,
0.34, 0.1, 0.27, 0.17, 0.24, 0.12, 0.47, 0.4, 0.5, 0.33, 0.14, 0.06, 0.14, 0.28,
0.03, 0.49, 0.03, 0.31, 0.39, 0.26, 0.5, 0.05, 0.19, 0.35, 0.22, 0.21, 0.32, 0.25,
0.1, 0.39, 0.11, 0.07, 0.04, 0.24, 0.45 };
char characters[10] = { 'I', 'A', 'u', 'e', 'E', 'U', 'O', 'i', 'a', 'o' };
std::string strings[26] = { "november", "sierra", "romeo", "juliett",
"yankee", "bravo", "mike", "hotel", "victor", "delta", "oscar", "papa", "foxtrot",
"whiskey", "echo", "kilo", "uniform", "lima", "zulu", "quebec", "india", "tango",
"golf", "x-ray", "alpha", "charlie" };
// }}}

print(characters, LEN(characters));
print(doubles, LEN(doubles));
print(integers, LEN(integers));
print(strings, LEN(strings));
sort(characters, LEN(characters));
sort(doubles, LEN(doubles));
sort(integers, LEN(integers));
sort(strings, LEN(strings));
print(characters, LEN(characters));
print(doubles, LEN(doubles));
print(integers, LEN(integers));
print(strings, LEN(strings));

return 0;
}

/**
 * Week 1 - CS 222 - UW Whitewater - Spring 2024
 * Sam Price - 01/21/2024 - 00:29
 * Compiled with both Clang and GCC. Not MSVC since I
 * don't run Windows.
 *
 * Compliant with C++11, and should be forward compatible with
 * C++14, C++17 and C++20 (maybe the last is shaky?)
 *
 * Also quick note hidden here, the reason I asked the first
 * day what to compile with/against (in terms of C++ standard)
 * is because I *don't* use an IDE, but I write in Emacs
 * and just compile the code manually since that's what works for me.
 */

#include <iostream>
#include <iomanip>
// Live by the uint32_t, die by the uint32_t
#include <cstdint>
#include <string>

#include <cassert>

int parseInt(std::string s, int &err);
double parseFloat(std::string s, int &err);

int main(int argc, char *argv[]) {
    // Should I do this with std::string too? Yeah probably, but I won't
    using std::cout;
    using std::endl;

    // All units in USD
    double bookingFee = 19.99;
    double perDiem = 29.99;
    double salesTaxPerc = 10;
    double salesTaxMult = 1 + (salesTaxPerc/100);

    std::string name = {};
    cout << "Name: ";
    std::getline(std::cin, name);

    if (name.length() == 0) {
        cout << "No name given, aborting" << endl;
        return 1;
    }

    // "Full name" was specified, if this doesn't
    // actually matter it can be ignored by you
    // using -DDISABLE_FULLNAME_CHECK compiler flag.
#ifndef DISABLE_FULLNAME_CHECK
    if (name.find(' ') == std::string::npos) {
        cout << "Did not give full name (requires space between first and last name), aborting" << endl;
        return 1;
    }
#endif

    std::string daysStr = {};
    cout << "Number of Days: ";
    std::getline(std::cin, daysStr);
    int err = 0;
    double days = double(parseInt(daysStr, err));
    // I don't care, you CANNOT say 7.3 days.
    // It's a valid number but not here it ain't.
    if (days <= 0 || err) {
        cout << "You cannot rent a car for " << daysStr << " days. Aborting" << endl;
        return 2;
    }

    double subtotal = bookingFee + (perDiem * days);
    double total = subtotal * salesTaxMult;

    // Not sure if you meant for me to cite this but a couple days later I just remembered to (01/23 23:59)
    // This is from a cppreference page about fixed floating decimal representation. This laptop doesn't have UWW wifi right
    // now so I will find it at a later date (This Thursday or so) and submit it with that below.
    // https://en.cppreference.com/w/cpp/io/manip/fixed
    // Not sure if I need to set these stream manipulators each time, will experiment.
    cout << "Thank you for booking a rental with us today " << name << ", your total today is $" <<
        std::fixed << std::setprecision(2) << total << endl;

    // END PART 1


    std::string paymentStr = {};
    cout << "Payment Amount: ";
    std::getline(std::cin, paymentStr);
    err = 0; // You think the functions clear it? Up to you, bucko.
    double amt = parseFloat(paymentStr, err);

    if (amt < total || err) {
        cout << "You are not paying in full, so your rental will be cancelled. Good Day!" << endl;
        return 3;
    }

    double difference = amt - total;
    assert(difference >= 0);
    cout << "Your change today is $"
         << std::fixed << std::setprecision(2) << difference << endl;

    // END PART 2

    cout << "--- RECIEPT ---\n"
        << "CUSTOMER: " << name << '\n'
        << "# of DAYS: " << int(days)
        << std::fixed << std::setprecision(2)
        << " (@ $" << perDiem << " per day)\n"
        << "SUBTOTAL: $" << subtotal << '\n'
        << "TAX: $" << (total - subtotal) << '\n'
        << "-----\n"
        << "TOTAL: $" << total << "\n\n"
        << "AMOUNT PAID: $" << amt << '\n'
        << "CHANGE DUE: $" << difference << "\n\n"
        << "THANK YOU FOR CHOOSING US TODAY" << endl;

    // END PART 3
}

// My very very good functions that
// aren't totally scuffed.
//
// Should I use std::optional instead of int references
// for error handling + tracking through calls?
// Maybe something like Rust's Result<T, E> type stuff?
int parseInt(std::string s, int &err) {
    int rv = 0;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c < '0' || c > '9') {
            err = 1;
            return rv; // It's invalid anyways, who cares if it's malformed? Blame the caller
        }

        int p = c - '0';
        // Please for the love of god don't make me do UB checks here, just don't put insane numbers.
        // TODO Do UB checks.
        rv *= 10;
        rv += p;
    }

    return rv;
}

double parseFloat(std::string s, int &err) {
    double rv = 0.0;

    bool afterDec = false;
    double afterDecPart = 0.0;
    int afterDecPlaces = 1;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == '.') {
            if (afterDec) {
                err = 1;
                return rv;
            }

            afterDec = true;
            continue;
        }

        if (c < '0' || c > '9') {
            err = 1;
            return rv;
        }

        double p = double(c - '0');
        if (afterDec) {
            for (int i = 0; i < afterDecPlaces; i++) {
                p /= 10;
            }
            afterDecPart += p;
            afterDecPlaces++;
        } else {
            rv *= 10.0;
            rv += p;
        }
    }

    rv += afterDecPart;
    return rv;
}

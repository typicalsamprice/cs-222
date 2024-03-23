#include <iostream>
#include <iomanip>

#include <cstdint>
#include <string>

using std::string;

bool is_valid_title(string title);
// Actually just proxy-call to the title check, since there were no requirements otherwise
bool is_valid_artist(string artist);
bool is_valid_year(int32_t year);
bool is_valid_rating(double rating);

int main(int argc, char **argv) {
    // Requires C++17 for this to compile!
    // GCC lets you with a warning, but still
    using std::cout, std::cin, std::endl;

    (void)argc, (void)argv;

    string album_title("");
    string artist("");
    int32_t year = 0;
    double rating = 0.0;
    bool explicitly_awesome = false; // Reserved keywords my beloved

    cout << "Welcome! Please tell me some information about your favorite musical album! :)\n"
        << "Title: ";

    std::getline(cin, album_title);
    if (!is_valid_title(album_title)) {
        cout << "Invalid title! Aborting." << endl;
        return 1;
    }

    cout << "Artist/Group Name: ";
    std::getline(cin, artist);
    if (!is_valid_artist(artist)) {
        cout << "Invalid artist name! Aborting." << endl;
        return 1;
    }

    cout << "Release Year: ";
    cin >> year;
    if (!is_valid_year(year)) {
        cout << "Invalid year! Aborting." << endl;
        return 1;
    }

    cout << "Rating (0-5): ";
    cin >> rating;
    if (!is_valid_rating(rating)) {
        cout << "Invalid rating! Aborting." << endl;
        return 1;
    }

    char expl_check('\0');

    cout << "Is Explicit (Y/N): ";
    cin >> expl_check;
    // I feel like it should default to "no", but I'll leave it as needing input as per requirements.
    if (expl_check != 'Y' && expl_check != 'N') {
        cout << "Invalid response (only Y/N)! Aborting." << endl;
        return 1;
    }

    if (expl_check == 'Y') {
        explicitly_awesome = true;
    }

    cout << "Your favorite album is '" << album_title << "' by " << artist
         << ". It was released in " << year << " and has an overall rating of " << std::fixed << std::setprecision(2) << rating << "." << endl;
    if (explicitly_awesome) {
        // Because 2 Chainz was 2 awesome
        // and not only because they solidified parody as protected free speech in the USA.
        cout << "Parental Advisory - Contains Explicit Content" << endl;
    }

    // GGs. Go Next :)
}

bool is_valid_title(string title) {
    return !title.empty();
}

bool is_valid_artist(string artist) { return is_valid_title(artist); }
bool is_valid_year(int32_t year) {
    return year >= 1900 && year <= 2024;
}
bool is_valid_rating(double rating) {
    return rating >= 0.0 && rating <= 5.0;
}

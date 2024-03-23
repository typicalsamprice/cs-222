#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using std::string;

class Movie {
  string _name;
  string _director;
  int _year;
  double _rating;

public:
  Movie() { Movie("", "", 0, 0); };
  Movie(string n, string d, int y, double r)
      : _name(n), _director(d), _year(y), _rating(r){};
  string name() const;
  string director() const;
  int year() const;
  double rating() const;

  void name(string name);
  void director(string director);
  void year(int year);
  void rating(double rating);
};

void sort_in_place(Movie *, size_t);
std::ostream &operator<<(std::ostream &os, const Movie &mov) {
  os << mov.name() << " by " << mov.director() << " (" << mov.year() << ") ["
     << mov.rating() << " / 10]";

  return os;
}

inline string Movie::name() const { return _name; }
inline string Movie::director() const { return _director; }
inline int Movie::year() const { return _year; }
inline double Movie::rating() const { return _rating; }

inline void Movie::name(string name) { _name = std::move(name); }
inline void Movie::director(string director) {
  _director = std::move(director);
}
inline void Movie::year(int year) { _year = year; }
inline void Movie::rating(double rating) {
  assert(rating <= 10 && rating >= 0);
  _rating = rating;
}

int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  Movie *movieList = new Movie[256];
  size_t length = 0;

  int k;
  int _dummy;
  cout << "Number of movies to enter: ";
  cin >> k;

  while (k > 0) {
    // I'm getting very lazy, sue me.
    // Tell me if it has to be "real" names though
    // it's not actually a problem.
    string n, d;
    int y;
    double r;

    cout << "Name of Movie: ";
    // Gross...ewww!!!!!!! Get rid of that newline from before!!!1
    // Seen here:
    // https://stackoverflow.com/questions/21567291/why-does-stdgetline-skip-input-after-a-formatted-extraction

    // See how good I am at bugfixing? Wasn't really an issue, it'd just restart
    // immediately for the first one. Not a huge deal.
    std::getline(cin >> std::ws, n);

    if (n.length() == 0) {
      cout << "Movie cannot be named nothing! Restarting..." << endl;
      continue;
    }

    cout << "Name of Director: ";
    std::getline(cin, d);

    if (d.length() == 0) {
      cout << "Movie cannot be directed by someone named nothing! Restarting..."
           << endl;
      continue;
    }

    cout << "Year: ";
    cin >> y;
    if (y < 0 || y > 2024) {
      cout << "Movie cannot be released in a weird year, start making sense! "
              "Restarting..."
           << endl;
      continue;
    }

    cout << "Rating (0-10): ";
    cin >> r;
    if (r < 0 || r > 10) {
      cout << "I just told you to rate it between 0 and 10. Restarting..."
           << endl;
      continue;
    }

    movieList[length].name(n);
    movieList[length].director(d);
    movieList[length].year(y);
    movieList[length].rating(r);

    length++;
    k--; // Only decrement at end
  }

  // SORT list by year
  sort_in_place(movieList, length);

  Movie *max = movieList;
  for (size_t i = 0; i < length; i++) {
    cout << movieList[i] << endl;

    if (movieList[i].rating() > max->rating())
      max = movieList + i;
  }

  cout << "Movie with Highest Rating:\n" << *max << endl;
}

// Bubblllleeesorttt
void sort_in_place(Movie *ptr, size_t length) {
  for (size_t i = 0; i < (length - 1); ++i) {
    for (size_t j = 0; j < (length - 1 - i); ++j) {
      if (ptr[j].year() > ptr[j + 1].year()) {
        Movie p = std::move(ptr[j]);
        ptr[j] = std::move(ptr[j + 1]);
        ptr[j + 1] = p;
      }
    }
  }
}

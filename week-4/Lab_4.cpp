#include "movie_lab4.h"
#include <iostream>
#include <string>
#include <cassert>

void part_one(Movie Movies[], int num_Movies) {
  using std::string;

  string mov;
  std::cout << "Enter movie title: ";
  std::getline(std::cin, mov);

  for (int i = 0; i < num_Movies; i++) {
    if (Movies[i].get_title() == mov) {
      Movies[i].print();
      return;
    }
  }

  std::cout << "Movie not found." << std::endl;
}

void part_two(Movie Movies[], int num_Movies) {
  Movie *high = &Movies[0];
  Movie *low = &Movies[0];
  for (int i = 1; i < num_Movies; i++) {
    Movie *mov = Movies + i;
    double rat = mov->get_rating();
    if (rat > high->get_rating())
      high = mov;
    else if (rat < low->get_rating())
      low = mov;
  }

  std::cout << "Highest rated movie: ";
  high->print();
  std::cout << "\nLowest rated movie: ";
  low->print();
  std::cout << std::endl;
}

void part_three(Movie Movies[], int num_Movies) {
  // Not doing it, but good to note:
  // std::sort wouldn't require a modification of Movie *necessarily*, although it's probably easier to overload the '<' operator.
  // You could create your own custom struct with a relation on it, then pass that along. Either case, it could work still.

  // Bubble sort, hope that is clear by the code though.
  int lim = num_Movies;
  while (lim > 1) {
    int sor = 0;
    for (int i = 1; i < lim; i++) {
      Movie a = Movies[i - 1];
      Movie b = Movies[i];
      if (a.get_year() <= b.get_year()) {
        if (a.get_year() == b.get_year()) {
          if (a.get_rating() < b.get_rating())
            continue; // Ignore if not sub-sorting.
        }

        // No need for temp var, since we already copied out the Movie types.
        // If they were space restrictive, you might want to do some pointer trickery,
        // but we aren't really concerned about that here.
        Movies[i - 1] = b;
        Movies[i] = a;
        sor = i;
      }
    }
    lim = sor;
  }

  for (int i = 0; i < num_Movies; i++)
    Movies[i].print();
}


#pragma region DO NOT MODIFY ANY CODE IN THIS REGION
int main() {
  const int num_Movies = 15;
  Movie *Movies = new Movie[num_Movies]{
      Movie("12 Angry Men", "Sidney Lumet", 1957, 4.52),
      Movie("1917", "Sam Mendes", 2019, 4.08),
      Movie("2001: A Space Odyssey", "Stanley Kubrick", 1968, 4.29),
      Movie("Blade Runner", "Ridley Scott", 1982, 4.09),
      Movie("Blade Runner 2049", "Denis Villeneuve", 2017, 4.10),
      Movie("The Dark Knight", "Christopher Nolan", 2008, 4.44),
      Movie("Dunkirk", "Christopher Nolan", 2017, 3.79),
      Movie("The Godfather", "Francis Ford Coppola", 1972, 4.54),
      Movie("Interstellar", "Christopher Nolan", 2014, 4.23),
      Movie("Nausicaa of the Valley of the Wind", "Hayao Miyazaki", 1984, 4.07),
      Movie("Paths of Glory", "Stanley Kubrick", 1957, 4.34),
      Movie("Princess Mononoke", "Hayao Miyazaki", 1997, 4.33),
      Movie("Whiplash", "Damien Chazelle", 2014, 4.39),
      Movie("Whisper of the Heart", "Yoshifumi Kondo", 1995, 4.12),
      Movie("The Wind Rises", "Hayao Miyazaki", 2013, 4.00),
  };
  part_one(Movies, num_Movies);
  part_two(Movies, num_Movies);
  part_three(Movies, num_Movies);
  delete[] Movies;
  return 0; // Redundant :).
}
#pragma endregion

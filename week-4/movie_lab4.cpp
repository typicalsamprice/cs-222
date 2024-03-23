// DO NOT MODIFY THIS FILE IN ANY WAY
#include <string>
#include <iomanip>
#include "movie_lab4.h"
Movie::Movie(std::string title, std::string director, int year, double rating) {
this->title = title;
this->director = director;
this->year = year;
this->rating = rating;
}
std::string Movie::get_title() {
return title;
}
std::string Movie::get_director() {
return director;
}
int Movie::get_year() {
return year;
}
double Movie::get_rating() {
return rating;
}
void Movie::set_rating(double rating) {
if (rating >= 0.5 && rating <= 5.0) {
this->rating = rating;
}
}
void Movie::print() {
std::cout << title
<< " ("
<< year
<< ") by "
<< director
<< " [Rated "
<< std::setprecision(2)
<< std::fixed
<< std::showpoint
<< rating
<< " / 5.00]"
<< std::endl;
}

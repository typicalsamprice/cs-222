#include <iostream>
// Glad you mentioned this! I already used it, but it's cool :)
#include <iomanip>
#include <string>

class Item {
public:
  Item() : name(""), price(0), rating(0){};
  Item(std::string name, float price, float rating)
      : name(name), price(price), rating(rating){};
  std::string name;
  float price;
  float rating;
};

std::ostream &operator<<(std::ostream &os, const Item &item) {
  os << std::fixed << std::setprecision(2);
  os << item.name << " | $" << item.price << " | " << item.rating
     << " out of 5.0 stars";

  return os;
}

int main() {
  // Demo of part one, see above
  Item xbox("Xbox 360", 499.99, 4.2);
  std::cout << xbox << std::endl;

  // Part 2
  Item arr[]{
      Item("iPhone 14", 685.99, 3.6),     Item("Galaxy S22", 417.97, 4.2),
      Item("Xbox Series X", 259.00, 4.4), Item("PlayStation 5", 499.99, 4.8),
      Item("Dell XPS 17", 3137.97, 3.9),  Item("MacBook Pro", 2099.00, 4.7)};

  for (const Item& i : arr) {
      std::cout << i << std::endl;
  }

  // Part 3
  for (const Item& i : arr) {
      if (i.price <= 500.00) {
          std::cout << i << std::endl;
      }
  }

  // Part 4
  for (Item& i: arr) {
      i.price *= 1.25;
  }
  for (const Item& i : arr) {
      std::cout << i << std::endl;
  }
}

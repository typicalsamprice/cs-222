#include <iostream>
#include <string>

using std::string;

class Item {
protected:
  double price;
  string model;
  string manufacturer;

public:
  Item(double p, string mo, string ma)
      : price(p), model(mo), manufacturer(ma) {}
  virtual void print() const {}; // Can't be undefined, since we are printing
                                 // off *any* derived OR base Item, even if we
                                 // know it's just derived ones.

  void setPrice(double p) {
    if (p >= 0)
      price = p;
  }
  double getPrice() const { return price; }
};

class Computer : public Item {
protected:
  int storage; // In Gigabytes

public:
  Computer(double p, string mo, string ma, int gb)
      : Item(p, mo, ma), storage(gb) {}
  void print() const override {
    std::cout << "The " << manufacturer << " " << model << " ($" << price
              << ") has " << storage << " GB of storage" << std::endl;
  }
};
class Television : public Item {
  double size; // In inches
public:
  Television(double p, string mo, string ma, double diag)
      : Item(p, mo, ma), size(diag) {}
  void print() const override {
    std::cout << "The " << manufacturer << " " << model << " television ($"
              << price << ") is " << size << " inches along the diagonal"
              << std::endl;
  }
};
class Laptop : public Computer {
  double battery_lt; // Hours
public:
  Laptop(double p, string mo, string ma, int gb, double blt)
      : Computer(p, mo, ma, gb), battery_lt(blt) {}
  void print() const override {
    std::cout << "The " << manufacturer << " " << model << " television ($"
              << price << ") has " << storage << " GB of storage and "
              << battery_lt << " hours of battery life" << std::endl;
  }
};

class Desktop : public Computer {
  using Computer::Computer;
};

int main() {
  Item *items[]{new Television(1097.99, "Q60B", "Samsung", 75),
                new Television(179.99, "F20", "Insignia", 32),
                new Television(14997.99, "QN90A", "Samsung", 98),
                new Desktop(2229.39, "Z2G4", "HP", 1024),
                new Desktop(699.99, "Inspiron 3910", "Dell", 256),
                new Desktop(204.62, "M92p", "Lenovo", 3072),
                new Laptop(1093.60, "EliteBook 850 G8", "HP", 512, 4),
                new Laptop(1879.00, "XPS 17", "Dell", 1024, 10),
                new Laptop(169.99, "A4-9120e", "Gateway", 64, 8)};

  for (Item *item : items) {
    item->print();
  }

  for (Item *item : items) {
    Computer *c = dynamic_cast<Computer *>(item);
    if (c)
      c->setPrice(c->getPrice() * 0.75);
  }

  std::cout << "\n\n--------- Prices reduced!! -----------\n\n";

  for (Item *item : items) {
    item->print();
  }
}

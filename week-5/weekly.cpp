#include <algorithm>
#include <array>
#include <fstream>
#include <ios>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

// Order of table
// A_id, Size, Weight, Sweetness, Crunchiness, Juiciness, Ripeness, Acidity,
// Quality

const char *filename = "apple_quality.csv";
const int NUM_ROWS = 1000; // Hardcoded, eat my shirt.

class AppleInfo {
public:
  AppleInfo()
      : _id(0), _size(0), _wt(0), _sweet(0), _crunch(0), _juice(0), _ripe(0), _acid(0),
        _quality(false) {}
  AppleInfo(int _i, float _s, float _w, float _sw, float _c, float _j, float _r,
            float _a, bool _q)
      : _id(_i), _size(_s), _wt(_w), _sweet(_sw), _crunch(_c), _juice(_j), _ripe(_r),
        _acid(_a), _quality(_q) {}

    int id() const { return _id; }
    float size() const { return _size; }
    float wt() const { return _wt; }
    float sweet() const { return _sweet; }
    float crunch() const { return _crunch; }
    float juice() const { return _juice; }
    float ripe() const { return _ripe; }
    float acid() const { return _acid; }
    bool quality() const { return _quality; }
private:
  int   _id;
  float _size;
  float _wt;
  float _sweet;
  float _crunch;
  float _juice;
  float _ripe;
  float _acid;
  bool  _quality;
};

std::array<AppleInfo, NUM_ROWS> apples;

void read_apple_csv() {
  std::ifstream f(filename, std::ios::in);
  if (!f.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    exit(1);
  }

  f >> std::skipws;
  // Burn the headers. Not a comma yet, but the name is funny
  std::string data;
  std::getline(f, data);

  // A_id, Size, Weight, Sweetness, Crunchiness, Juiciness, Ripeness, Acidity,
  // Quality
  for (AppleInfo &a : apples) {
    std::getline(f, data, ',');
    int id = ::atof(data.c_str());
    std::getline(f, data, ',');
    float size = ::atof(data.c_str());
    std::getline(f, data, ',');
    float wt = ::atof(data.c_str());
    std::getline(f, data, ',');
    float sweet = ::atof(data.c_str());
    std::getline(f, data, ',');
    float crunch = ::atof(data.c_str());
    std::getline(f, data, ',');
    float juice = ::atof(data.c_str());
    std::getline(f, data, ',');
    float ripe = ::atof(data.c_str());
    std::getline(f, data, ',');
    float acid = ::atof(data.c_str());

    std::getline(f, data);
    bool quality = data == "good";

    a = AppleInfo(id, size, wt, sweet, crunch, juice, ripe, acid, quality);
  }

  f.close();
}

void sort_apple_csv() {
  // Sorty by juiciness, since that's what *I* care about most.
  std::sort(apples.begin(), apples.end(),
            [](AppleInfo a, AppleInfo b) { return a.juice() > b.juice(); });
}

std::ostream& operator<<(std::ostream &os, const AppleInfo &a) {
  os << a.id() << "," << a.size() << "," << a.wt() << "," << a.sweet() << ","
     << a.crunch() << "," << a.juice() << "," << a.ripe() << "," << a.acid() << ",";
  os << (a.quality() ? "good" : "bad") << "\n";
  return os;
}

void overwrite_apple_csv() {
  std::ofstream file("sorted_apples.csv");
  if (!file.is_open()) {
    std::cerr << "Sorted CSV file already open in another process!"
              << std::endl;
    exit(2);
  }

  file << "";
  file.close();
  file.open("sorted_apples.csv", std::ios::app | std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Sorted CSV file already open in another process!"
              << std::endl;
    exit(2);
  }

  file << "A_id "
          ",Size,Weight,Sweetness,Crunchiness,Juiciness,Ripeness,Acidity,"
          "Quality\n";
  for (const AppleInfo &a : apples) {
    file << a;
  }
  file.flush(); // Just in case! Although close() probably does this anyways..
                // Too lazy to check!

  file.close();
}

int main() {
  std::cout << "Reading apple_quality.csv" << std::endl;
  read_apple_csv();
  std::cout << "Done" << std::endl;

  std::cout << "Sorting apple_quality.csv" << std::endl;
  sort_apple_csv();
  std::cout << "Done" << std::endl;

  std::cout << "Writing apple_quality.csv" << std::endl;
  overwrite_apple_csv();
  std::cout << "Done" << std::endl;
}

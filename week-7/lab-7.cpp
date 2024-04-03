// -*- compile-command: "g++ -o lab-7 lab-7.cpp"; -*-
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

using std::string, std::map, std::set;

// What is this, advent of code? Feels weird to do part_one, part_two again so
// soon...

void part_one() {
  string fname = "PeriodicTable.csv";
  std::ifstream f;
  f.open(fname);
  if (!f.is_open())
    std::exit(1); // No point in continuing.

  map<int, string> elems;

  for (string line; std::getline(f, line);) {
    std::stringstream ss(line);
    string name, numS;
    std::getline(ss, numS, ',');
    std::getline(ss, name);
    int num = atoi(numS.c_str());
    elems[num] = name;
  }

  int found = 0;
  for (int i = 1; found < elems.size(); i++) {
    if (elems.count(i) == 0)
      continue;
    found++;
    std::cout << i << " - " << elems[i] << std::endl;
  }
}
void part_two() {
  string fname = "Chemists.txt";
  std::ifstream f;
  f.open(fname);
  if (!f.is_open())
    std::exit(1); // No point in continuing.

  set<string> chemU;

  for (string line; std::getline(f, line);)
    chemU.insert(line);

  std::cout << chemU.size() << " unique chemists" << std::endl;
}

int main() {
  part_one();
  part_two();

  return 0;
}

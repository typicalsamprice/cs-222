// -*- compile-command: "g++ -o week-7 week-7.cpp"; -*-
#include <iostream>
#include <string>
#include <typeinfo>

using std::string;

class Person {
protected:
  string first;
  string last;
  int id;

public:
  Person(string f, string l, int i) : first(f), last(l), id(i) {}

  virtual void print() {
    std::cout << first << " " << last << " [" << id << "]" << std::endl;
  }

  void setFirst(string s) {
    if (s.length() > 0)
      first = s;
  }
  void setLast(string s) {
    if (s.length() > 0)
      last = s;
  }
  void setID(int i) {
    if (i > 0)
      id = i;
  }

  string getFirst() const { return first; }
  string getLast() const { return last; }
  int getID() const { return id; }
};

class Student : virtual public Person {
protected:
  string major;
  string minorOrMajor;
  bool doubleMajor;
  double gpa;

public:
  Student(string first, string last, int id, string maj, string aux,
          bool isDouble, double g)
      : Person(first, last, id), major(maj), minorOrMajor(aux),
        doubleMajor(isDouble), gpa(g) {}

  void setMajor(string s) {
    if (s.length() > 0)
      major = s;
  }
  void setAux(string s) {
    if (s.length() > 0)
      minorOrMajor = s;
  }
  void setDoubleMajor(bool isDouble) { doubleMajor = isDouble; }
  void setGPA(double g) {
    if (g >= 0.0 && g <= 4.0)
      gpa = g;
  }

  string getMajor() const { return major; }
  string getAuxDegree() const { return minorOrMajor; }
  bool isDoubleMajor() const { return doubleMajor; }
  double getGPA() const { return gpa; }

  void print() override {
    std::cout << getLast() << ", " << getFirst() << " (" << getID() << ") [ "
              << getMajor() << " Major / " << getAuxDegree();
    if (isDoubleMajor())
      std::cout << " Major ]";
    else
      std::cout << " Minor ]";
    std::cout << " GPA: " << getGPA() << std::endl;
  }
};

class Instructor : virtual public Person {
protected:
  string department;

public:
  Instructor(string first, string last, int id, string dept)
      : Person(first, last, id), department(dept) {}

  void setDepartment(string d) {
    if (d.length() > 0)
      department = d;
  }

  string getDepartment() const { return department; }
  void print() override {
    std::cout << "Prof. " << getLast() << " (" << getID() << ") [Dept. of "
              << getDepartment() << "]" << std::endl;
  }
};

int main() {
  Person **people = new Person *[10] {
    new Student("Sam", "Price", 2060736, "Mathematics", "Computer Science",
                true, 4.0),
        new Student("Jing", "McL.", 999, "Mathematics", "Education", false,
                    4.0),
        new Student("Boaty", "McBoatface", 369121518, "History",
                    "Gender Studies", false, 3.8),
        new Student("Ferris", "Bueller", 1, "Screwing Around",
                    "Skipping School", true, 1.8),
        new Student("Simba", "Mufasason", 41, "Ruling Over 'France'", "No",
                    false, 3.2),
        new Student("Walt", "Disney", 444523, "Filmography",
                    "Exploitative Labor", false, 4.0),
        new Instructor("Hayley", "Bertrand", 3334, "Mathematics"),
        new Instructor("Dylan", "Spence", 47721, "Mathematics"),
        // Yes, this is negative. You never said it couldn't be! Also, it's
        // "Bridge" in ASCII
        new Instructor("Tamas", "Szabo", int(668273687169), "Mathematics"),
        new Instructor("Wesley", "Hough", 123456789, "Mathematics")
  };

  for (int i = 0; i < 10; i++) {
    Person *p = people[i];
    p->print();
  }

  double sum = 0;
  double tot = 0;
  for (int i = 0; i < 10; i++) {
    if (Student *s = dynamic_cast<Student *>(people[i])) {
      sum += s->getGPA();
      tot += 1;
    }
  }

  std::cout << "Average GPA: " << sum / tot << std::endl;

  delete[] people;
  return 0;
}

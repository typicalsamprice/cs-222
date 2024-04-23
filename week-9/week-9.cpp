// -*- compile-command: "g++ -o week-9 week-9.cpp"; -*-
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

class Employee : virtual public Person {
  protected:
    int salary;

  public:
    Employee(string f, string l, int i, int s) : Person(f, l, i), salary(s) {};
    int getSal() const { return salary; }
    void setSal(int s) { if (s >= 0) salary = s;
    };

    void print() override {
      std::cout << first << " " << last << " [" << id << "] Salary: $" << salary << std::endl;
    }
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

class GradStudent : virtual public Student, virtual public Employee {
    public:
    GradStudent(string f, string l, int i, string maj, double g, int sal)
      : Person(f, l, i), Student(f, l, i, maj, "", false, g), Employee(f, l, i, sal) {};
    void print() override {
      std::cout << getLast() << ", " << getFirst() << " (" << getID() << ") [ "
                << getMajor() << " Major ]";
      std::cout << " GPA: " << getGPA() << std::endl;
    }
};

class Instructor : virtual public Employee {
protected:
  string department;

public:
  Instructor(string first, string last, int id, string dept, int sal)
      : Person(first, last, id), Employee(first, last, id, sal), department(dept) {};

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
  Person **people = new Person *[6] {
    new Student("Sam", "Price", 2060736, "Mathematics", "Computer Science",
                true, 4.0),
        new Student("Jing", "McL.", 999, "Mathematics", "Education", false,
                    4.0),
        new GradStudent("Simba", "Mufasason", 41, "Ruling Over 'France'", 3.2, 13000),
        new GradStudent("Walt", "Disney", 444523, "Filmography", 4.0, 25000),
        new Instructor("Hayley", "Bertrand", 3334, "Mathematics", 65000),
        new Instructor("Dylan", "Spence", 47721, "Mathematics", 65000),
  };

  for (int i = 0; i < 6; i++) {
    Person *p = people[i];
    p->print();
  }

  for (int i = 0; i < 6; i++) {
    Person *p = people[i];
    if (GradStudent *gs = dynamic_cast<GradStudent *>(p))
      gs->print();
  }

  Employee *emax = nullptr;
  Employee *emin = nullptr;
  for (int i = 0; i < 6; i++) {
    Person *p = people[i];
    if (Employee *e = dynamic_cast<Employee *>(p)) {
      if (emax == nullptr) {
        emax = e;
        emin = e;
      } else {
        if (emax->getSal() < e->getSal())
          emax = e;
        else if (emin->getSal() > e->getSal())
          emin = e;
      }
    }
  }
  std::cout << "Max salary: ";
  emax->print();
  std::cout << "Min salary: ";
  emin->print();


  delete[] people;
  return 0;
}

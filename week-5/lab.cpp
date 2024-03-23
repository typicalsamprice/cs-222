// -*- compile-command: "g++ -o lab lab.cpp -std=c++11"; -*-
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

#ifndef SCOREFILE
#define SCOREFILE "scores.csv"
#endif // SCOREFILE
[[maybe_unused]] std::string ignore(SCOREFILE);

class Score {
    public:
        Score() : _name(), _score() {};
        Score(std::string name, unsigned score) : _name(name), _score(score) {};

        unsigned score() const { return _score; }
        std::string name() const { return _name; }

    private:
        unsigned _score;
        std::string _name;
};

std::ostream& operator<<(std::ostream& os, const Score &score) {
    os << score.name() << ","<< score.score() << "\n";
    return os;
}

bool validName(std::string name) {
    if (name.length() != 3)
        return false;
    for (const char c : name)
        if (c > 'Z' || c < 'A')
            return false;
    return true;
}

void enter_score() {
    std::string ip;
    std::cout << "Enter score: ";
    std::getline(std::cin, ip);
    unsigned score = ::atoi(ip.c_str()); // Yeah, don't care if atoi is bad practice. Good luck getting a malformed string past getline()
    if (std::isnan(score)) {
        std::cerr << "Invalid score." << std::endl;
        std::exit(1);
    }
    std::cout << "Enter name: ";
    std::getline(std::cin, ip);
    if (!validName(ip)) {
        std::cerr << "Valid names are 3-character all-caps. Exiting" << std::endl;
        std::exit(1);
    }

    std::ofstream f(SCOREFILE, std::ios::app);
    if (!f.is_open()) {
        std::cerr << "File being used by another process." << std::endl;
        std::exit(1);
    }
    f << Score(ip, score);
}

void print_scores() {
    std::ifstream f(SCOREFILE);
    if (!f.is_open()) {
        std::cerr << "File open in another process" << std::endl;
        std::exit(1);
    }
    std::string line;
    while (std::getline(f, line)) {
        std::istringstream ss(line);
        std::string name;
        std::getline(ss, name, ',');
        std::string s_score;
        std::getline(ss, s_score);
        unsigned score = ::atoi(s_score.c_str());
        Score scr(name, score);
        std::cout << scr.score() << " by " << scr.name() << std::endl;
    }
}

int main() {
    std::string ip;
    std::cout << "Would you like to\n"
        << "1) Enter your score\n"
        << "2) View scores\n";
    std::getline(std::cin, ip);
    if (ip != "1" && ip != "2") {
        std::cerr << "Invalid input!" << std::endl;
        std::exit(1);
    }

    if (ip == "1") {
        enter_score();
    } else {
        print_scores();
    }
}

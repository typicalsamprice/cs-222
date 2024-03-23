#include <string>
#include <iostream>

class K {
    public:
        std::string name;
        K(std::string s);
};

K::K(std::string s) {
    name = s;
}

int main() {
    K k(std::string("Hello, World!"));
    std::cout << k.name << std::endl;
}

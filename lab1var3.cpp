#include <iostream>

bool FindOne(unsigned int num) {
    bool found = false;
    bool ok = true;
    while (num > 0) {
        if (num & 1) {
            if (found) {
                ok = false;
                break;
            }
            found = true;
        }
        num >>= 1;
    }
    if (found && ok) return true;
    return false;
}

 int main() {
    unsigned int number;
    std::cin >> number;
    if (FindOne(number)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
    return 0;
 }

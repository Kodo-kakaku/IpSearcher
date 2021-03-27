#include <iostream>
#include "printus.h"

int main() {

    print_ip(static_cast<char>(-1));
    std::cout << "\n";

    print_ip(static_cast<short>(0));
    std::cout << "\n";

    print_ip(static_cast<int>(2130706433));
    std::cout << "\n";

    print_ip(static_cast<long long>(8875824491850138409));
    std::cout << "\n";

    print_ip(std::string("Hello, World!"));
    std::cout << "\n";

    const std::vector<int> v{ 100, 200, 300, 400 };
    print_ip(std::vector<int>(v));
    std::cout << "\n";

    const std::list<short> l{ 400, 300, 200, 100 };
    print_ip(std::list<short>(l));
    std::cout << "\n";

    print_ip(std::make_tuple(123, 456, 789, 0));
    std::cout << std::endl;

    return 0;
}
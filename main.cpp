#include <iostream>

#include "low/all.hpp"

using namespace TT::low;

uintptr_t core_ptr, b_ptr;

namespace TT::low {
static void restore_core() {
    std::cout << "Restoring core" << std::endl;
    current_switcher::swticher(&b_ptr, &core_ptr);
}
}

void MyTest() {
    std::cout << "Something happend" << std::endl;
}

void MyExit() {
    std::cout << "Bye bye!";
    std::exit(10);
}

int main() {
    uintptr_t* a = new uintptr_t[100];
    std::cout << "Preparing b fiber:" << std::endl;
    b_ptr = current_switcher::preparer((uintptr_t)MyTest, a);
    std::cout << "Done!" << std::endl;
    std::cout << "Swtiching to b fiber:" << std::endl;
    current_switcher::swticher(&core_ptr, &b_ptr);
    std::cout << "Switched back!" << std::endl;
    MyExit();
}
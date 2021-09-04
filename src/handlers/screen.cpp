#include <iostream>


namespace barthes {
    void clearscreen() {
        std::cout << "\033[2J\033[1;1H";
    }
}

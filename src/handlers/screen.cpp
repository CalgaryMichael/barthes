#include <iostream>
#include <stdlib.h>


namespace barthes {
    void clearscreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    void init_screen() {
        clearscreen();
        std::atexit(clearscreen);
    }
}

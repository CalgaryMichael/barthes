#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <utility>


namespace barthes {
    void clearscreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    void init_screen() {
        clearscreen();
    }

    void to_screen(std::string text) {
        std::cout << text << std::endl;
    }

    std::pair<int, int> get_window_size() {
        winsize ws;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
            throw std::runtime_error("Unable to gather the size of the window");
        }
        return std::pair<int, int>(ws.ws_col, ws.ws_row);
    }
}

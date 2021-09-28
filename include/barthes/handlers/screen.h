#ifndef _BARTHES_SCREEN_H
#define _BARTHES_SCREEN_H

#include <utility>


namespace barthes {
    void clearscreen();
    void init_screen();
    void to_screen(std::string text);

    std::pair<int, int> get_window_size();
}

#endif

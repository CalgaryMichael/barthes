#ifndef _BARTHES_SCREEN_H
#define _BARTHES_SCREEN_H

#include <utility>


namespace barthes {
    void clearscreen();
    void init_screen();

    std::pair<int, int> get_window_size();
}

#endif

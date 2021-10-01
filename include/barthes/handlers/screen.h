#ifndef _BARTHES_SCREEN_H
#define _BARTHES_SCREEN_H

#include <utility>
#include <vector>

#include <barthes/config.h>


namespace barthes {
    void set_cursor(int row, int col);
    void set_cursor(TermConfig *tc);
    void teardown_screen();
    void init_screen();

    void to_screen(std::string text);
    void to_screen(std::vector<std::string> text);

    std::pair<int, int> get_window_size();
}

#endif

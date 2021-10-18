#ifndef _BARTHES_SCREEN_H
#define _BARTHES_SCREEN_H

#include <utility>
#include <vector>

#include <barthes/config.h>


namespace barthes {
    void teardown_screen();
    void init_screen();

    void to_screen(std::string text);
    void to_screen(std::vector<std::string> text, TermConfig *tc);
    void to_screen(std::vector<std::string> text);
    bool adjust_view(TermConfig *tc);
    void set_cursor(int row, int col, bool refresh_screen);
    void set_cursor(TermConfig *tc);
    void move_cursor(TermConfig *tc, int row_diff, int col_diff);
    void move_cursor_absolute(TermConfig *tc, int row, int col);

    std::pair<int, int> get_window_size();
}

#endif

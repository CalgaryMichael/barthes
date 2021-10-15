#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <utility>
#include <vector>

#include <fmt/core.h>

#include <barthes/config.h>


namespace barthes {
    void teardown_screen() {
        endwin();
    }

    void init_screen() {
        initscr();
        raw();				/* Line buffering disabled	*/
        keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
        noecho();			/* Don't echo() while we do getch */
        clear();
        std::atexit(teardown_screen);
    }

    void to_screen(std::string text) {
        printw(text.c_str());
        refresh();
    }

    void to_screen(std::vector<std::string> buffer) {
        TermConfig *tc = get_config();
        int start = tc->view_line;
        int end = std::min<int>(tc->view_line + tc->window_size.first, buffer.size());

        // build the string that we are going to send to the screen
        std::string output;
        for (int i = start; i < end; i++) {
            output += fmt::format("{}\n", buffer[i]);
        }

        // actually handle putting stuff onto the screen
        clear();
        to_screen(output);
    }

    bool adjust_view(TermConfig *tc) {
        // Changes the `view_line` depending on whether or not the cursor is out of the window
        // Returns `true` if we have changed the `view_line` (e.g. scrolled)
        int old_view_line = tc->view_line;

        // scroll up
        if (tc->cursor.first < 0) {
            tc->view_line = std::max(tc->view_line - 1, 0);
            tc->cursor.first = 0;
        }

        // scroll down
        if (tc->cursor.first >= tc->window_size.first) {
            tc->view_line++;
            tc->cursor.first = tc->window_size.first - 1;
        }

        return old_view_line != tc->view_line;
    }

    void set_cursor(int row, int col, bool refresh_screen=true) {
        move(row, col);
        if (refresh_screen) {
            refresh();
        }
    }

    void set_cursor(TermConfig *tc) {
        bool scrolled = adjust_view(tc);
        if (scrolled) {
            to_screen(tc->file_buffer);
        }
        set_cursor(tc->cursor.first, tc->cursor.second, !scrolled);
    }

    void move_cursor(TermConfig *tc, int row_diff, int col_diff) {
        int row_max = get_row_max(tc);
        tc->cursor.first = std::min<int>(tc->cursor.first + row_diff, row_max);

        int col_max = get_col_max(tc);
        tc->cursor.second = std::min<int>(tc->cursor.second + col_diff, col_max);
        set_cursor(tc);
    }

    void move_cursor_absolute(TermConfig *tc, int row, int col) {
        int row_max = get_row_max(tc);
        tc->cursor.first = std::clamp<int>(row, 0, row_max);

        int col_max = get_col_max(tc);
        tc->cursor.second = std::clamp<int>(col, 0, col_max);
        set_cursor(tc);
    }

    std::pair<int, int> get_window_size() {
        winsize ws;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
            throw std::runtime_error("Unable to gather the size of the window");
        }
        return std::pair<int, int>(ws.ws_row, ws.ws_col);
    }
}

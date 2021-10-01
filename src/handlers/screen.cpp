#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <utility>
#include <vector>

#include <fmt/core.h>

#include <barthes/config.h>


namespace barthes {
    void set_cursor(int row, int col) {
        move(row, col);
        refresh();
    }

    void set_cursor(TermConfig *tc) {
        set_cursor(tc->cursor.first, tc->cursor.second);
    }

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
        std::string output;
        for (int i = 0; i < buffer.size(); i++) {
            output += fmt::format("~ {}\n", buffer[i]);
        }
        to_screen(output);
    }

    std::pair<int, int> get_window_size() {
        winsize ws;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
            throw std::runtime_error("Unable to gather the size of the window");
        }
        return std::pair<int, int>(ws.ws_row, ws.ws_col);
    }
}

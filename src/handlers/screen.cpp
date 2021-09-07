#include <iostream>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


namespace barthes {
    termios orig_termios;

    void clearscreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    void set_terminal() {
        // save original terminal state, so that we can
        // restore it when we are exiting the program
        tcgetattr(STDIN_FILENO, &orig_termios);
        termios raw = orig_termios;

        // diable raw mode (ECHO)
        // disable canonical mode (ICANON)
        raw.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    void reset_terminal() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    void init_screen() {
        clearscreen();
        set_terminal();
        std::atexit(reset_terminal);
    }
}

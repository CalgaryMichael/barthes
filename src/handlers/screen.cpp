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

        raw.c_lflag &= ~(
            ECHO            // prevent printing commands to screen
            | ICANON        // read input byte-by-byte, instead of line-by-line
            | IEXTEN        // prevent sending characters literally
            | ISIG          // prevent Ctrl-C/Ctrl-Z from suspending the program
        );
        raw.c_iflag &= ~(
            BRKINT          // prevents Ctrl-C from killing the program
            | ICRNL         // prevent carriage return newline fangling
            | INPCK         // prevent parity checking -- doubtfully being used by modern terms
            | ISTRIP        // prevent stripping the 8th bit of every character
            | IXON          // prevent pausing transmission of data to terminal
        );
        raw.c_oflag &= ~(
            OPOST           // stop translating `\n` -> `\r\n`
        );
        raw.c_cflag |= (
            CS8             // set the character size to 8
        );
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    void reset_terminal() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    void init_screen() {
        clearscreen();
        set_terminal();

        std::atexit(reset_terminal);
        std::atexit(clearscreen);
    }
}

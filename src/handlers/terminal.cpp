#include <iostream>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include <barthes/exceptions.h>


namespace barthes {
    termios orig_termios;

    /*
     * Save the original terminal state so that we can
     * restore it when we are exiting the program
     */
    termios save_original_terminal_flags() {
        int result = tcgetattr(STDIN_FILENO, &orig_termios);
        if (result < 0) {
            die("Unable to store original terminal state");
        }

        return orig_termios;
    }

    void reset_terminal_flags() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    void set_terminal_flags() {
        termios raw = save_original_terminal_flags();

        raw.c_lflag &= ~(
            ECHO            // prevent printing commands to screen
            | ICANON        // read input byte-by-byte, instead of line-by-line
            | IEXTEN        // prevent sending characters literally
            | ISIG          // prevent Ctrl-C/Ctrl-Z from suspending the program
        );
        raw.c_iflag &= ~(
            BRKINT          // prevent Ctrl-C from killing the program
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
        int result = tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        if (result < 0) {
            die("Unable to set terminal into \"raw mode\"");
        }
    }

    void init_terminal() {
        set_terminal_flags();
        std::atexit(reset_terminal_flags);
    }
}

#include <stdlib.h>
#include <unistd.h>

#include <barthes/handlers/screen.h>
#include <barthes/exceptions.h>


namespace barthes {
    char get_keypress() {
        char c = '\0';
        int result = read(STDIN_FILENO, &c, 1);
        if (result < 0) {
            die("Unable to read character");
        }
        return c;
    }

    void handle_keypress(char input) {
        switch (input) {
            case 'q':
                clearscreen();
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
    }

    void handle_input() {
        while (true) {
            char input = get_keypress();
            handle_keypress(input);
        }
    }
}

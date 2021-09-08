#include <stdlib.h>
#include <unistd.h>


namespace barthes {
    char get_input() {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        return c;
    }

    void handle_input() {
        while (true) {
            char input = get_input();
            switch (input) {
                case 'q':
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    break;
            }
        }
    }
}

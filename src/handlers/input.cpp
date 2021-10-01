#include <algorithm>
#include <stdlib.h>
#include <unistd.h>

#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>
#include <barthes/exceptions.h>


namespace barthes {
    void move_cursor(TermConfig *tc, int row_diff, int col_diff) {
        // TODO: disallow cursor from going farther than the text on the screen
        tc->cursor.first = std::min<int>(
            std::max<int>(tc->cursor.first + row_diff, 0),
            tc->window_size.first - 1
        );
        tc->cursor.second = std::min<int>(
            std::max<int>(tc->cursor.second + col_diff, 0),
            tc->window_size.second - 1
        );
        set_cursor(tc);
    }

    char get_keypress() {
        char c = '\0';
        int result = read(STDIN_FILENO, &c, 1);
        if (result < 0) {
            die("Unable to read character");
        }
        return c;
    }

    KeypressResponse handle_keypress(char input) {
        KeypressResponse response = KeypressResponse::Continue;
        TermConfig *tc = get_config();
        switch (input) {
            case 'j':
                move_cursor(tc, UP, 0);
                break;
            case 'k':
                move_cursor(tc, DOWN, 0);
                break;
            case 'l':
                move_cursor(tc, 0, RIGHT);
                break;
            case 'h':
                move_cursor(tc, 0, LEFT);
                break;
            case CTRL_KEY('q'):
                response = KeypressResponse::Exit;
                break;
            default:
                break;
        }

        return response;
    }

    void handle_input() {
        while (true) {
            char input = get_keypress();
            KeypressResponse response = handle_keypress(input);
            if (response == KeypressResponse::Exit) {
                return;
            }
        }
    }
}

#include <stdlib.h>
#include <unistd.h>

#include <barthes/handlers/input.h>
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

    KeypressResponse handle_keypress(char input) {
        KeypressResponse response = KeypressResponse::Continue;
        switch (input) {
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

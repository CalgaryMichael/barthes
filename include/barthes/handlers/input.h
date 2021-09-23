#ifndef _BARTHES_INPUT_H
#define _BARTHES_INPUT_H

namespace barthes {
    #define CTRL_KEY(k) ((k) & 0x1f)

    enum class KeypressResponse {
        Exit = 0,
        Continue = 1
    };

    char get_keypress();
    KeypressResponse handle_keypress(char input);
    void handle_input();
}

#endif

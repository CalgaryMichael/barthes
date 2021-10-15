#ifndef _BARTHES_INPUT_H
#define _BARTHES_INPUT_H

#include <barthes/config.h>

namespace barthes {
    #define CTRL_KEY(k) ((k) & 0x1f)

    const int UP    = 1;
    const int DOWN  = -1;
    const int RIGHT = 1;
    const int LEFT  = -1;

    enum class KeypressResponse {
        Exit = 0,
        Continue = 1
    };

    void add_newline(TermConfig *tc);
    void add_ch(TermConfig *tc, int input);
    void remove_ch(TermConfig *tc);

    int get_keypress();
    KeypressResponse handle_keypress(int input);
    KeypressResponse handle_view_keypress(TermConfig *tc, int input);
    KeypressResponse handle_edit_keypress(TermConfig *tc, int input);
    void handle_input();
}

#endif

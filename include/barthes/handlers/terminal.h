#ifndef _BARHTES_TERMINAL_H
#define _BARHTES_TERMINAL_H

#include <termios.h>

namespace barthes {
    termios save_original_terminal_flags();
    void reset_terminal_flags();
    void set_terminal_flags();
    void init_terminal();
}

#endif

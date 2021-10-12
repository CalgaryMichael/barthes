#ifndef _BARTHES_CONFIG_H
#define _BARTHES_CONFIG_H

#include <stdlib.h>
#include <utility>

namespace barthes {
    enum class EditorMode {
        View = 0,
        Edit = 1,
    };

    typedef struct {
        EditorMode mode;
        std::pair<int, int> window_size;
        std::pair<int, int> cursor;
    } TermConfig;

    void init_config();
    void set_mode(TermConfig *tc, EditorMode mode);
    TermConfig* get_config();
}

#endif

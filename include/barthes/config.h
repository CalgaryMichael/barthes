#ifndef _BARTHES_CONFIG_H
#define _BARTHES_CONFIG_H

#include <stdlib.h>
#include <utility>

namespace barthes {
    typedef struct {
        std::pair<int, int> size;
        std::pair<int, int> cursor;
    } TermConfig;

    void init_config();
    TermConfig* get_config();
}

#endif

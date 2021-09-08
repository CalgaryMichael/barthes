#include <utility>

#include "config.h"

namespace barthes {
    TermConfig config = {
        .size=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0)
    };

    void init_config() {
        // TODO: get size of screen and set it here
        return;
    }

    TermConfig* get_config() {
        return &config;
    }
}

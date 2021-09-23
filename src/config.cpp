#include <utility>

#include <barthes/config.h>
#include <barthes/handlers/screen.h>


namespace barthes {
    TermConfig config = {
        .window_size=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0)
    };

    void init_config() {
        config.window_size = get_window_size();
        return;
    }

    TermConfig *get_config() {
        return &config;
    }
}

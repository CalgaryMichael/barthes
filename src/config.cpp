#include <stdexcept>
#include <utility>

#include <barthes/config.h>
#include <barthes/exceptions.h>
#include <barthes/handlers/screen.h>


namespace barthes {
    TermConfig config = {
        .mode=EditorMode::View,
        .window_size=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0)
    };

    void init_config() {
        try {
            config.window_size = get_window_size();
        } catch (const std::runtime_error e) {
            die("Could not correctly get window size");
        }
    }

    void set_mode(TermConfig *tc, EditorMode mode) {
        tc->mode = mode;
    }

    TermConfig *get_config() {
        return &config;
    }
}

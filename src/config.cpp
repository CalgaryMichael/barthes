#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <fmt/core.h>

#include <barthes/config.h>
#include <barthes/exceptions.h>
#include <barthes/handlers/file.h>
#include <barthes/handlers/screen.h>


namespace barthes {
    TermConfig config = {
        .mode=EditorMode::View,
        .window_size=std::make_pair(0, 0),
        .cursor=std::make_pair(0, 0),
        .view=std::make_pair(0, 0)
    };

    TermConfig* init_config(std::string filepath) {
        try {
            config.window_size = get_window_size();
        } catch (const std::runtime_error e) {
            die("Could not correctly get window size");
        }

        // load file
        config.file_buffer = open_file(filepath);

        // TODO: create a window for file info
        // TODO: create a window for line number

        return &config;
    }

    void set_mode(TermConfig *tc, EditorMode mode) {
        tc->mode = mode;
    }

    int get_row_max(TermConfig *tc) {
        return std::max<int>(tc->file_buffer.size() - 1, 0);
    }

    int get_col_max(TermConfig *tc) {
        if (tc->file_buffer.size() < 1) {
            return 0;
        }
        std::pair<int, int> loc = get_file_loc(tc);
        return tc->file_buffer[loc.first].length();
    }

    std::pair<int, int> get_file_loc(TermConfig *tc) {
        return std::make_pair(
            tc->view.first + tc->cursor.first,
            tc->view.second + tc->cursor.second
        );
    }

    TermConfig *get_config() {
        return &config;
    }
}

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
        .view_line=0
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
        return tc->file_buffer.size() - 1;
    }

    int get_col_max(TermConfig *tc) {
        // TODO: handle scrolling sideways
        return std::min<int>(tc->file_buffer[tc->cursor.first].length() + 1, tc->window_size.second);
    }

    std::pair<int, int> file_loc(TermConfig *tc) {
        // TODO: handle col as well
        return std::make_pair(tc->view_line + tc->cursor.first, tc->cursor.second);
    }

    TermConfig *get_config() {
        return &config;
    }
}

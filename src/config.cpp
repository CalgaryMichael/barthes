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
        .cursor=std::make_pair(0, 0)
    };

    TermConfig* init_config(std::string filepath) {
        try {
            config.window_size = get_window_size();
        } catch (const std::runtime_error e) {
            die("Could not correctly get window size");
        }

        // load file
        std::vector<std::string> buffer;
        buffer.push_back(filepath);
        buffer.push_back(fmt::format("Screen size: {} x {}", config.window_size.first, config.window_size.second));
        buffer.push_back("");

        std::vector<std::string> file_buffer = open_file(filepath);
        buffer.insert(buffer.end(), file_buffer.begin(), file_buffer.end());
        config.file_buffer = buffer;

        return &config;
    }

    void set_mode(TermConfig *tc, EditorMode mode) {
        tc->mode = mode;
    }

    TermConfig *get_config() {
        return &config;
    }
}

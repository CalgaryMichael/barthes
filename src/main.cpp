#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#include <fmt/core.h>

#include <barthes/config.h>
#include <barthes/handlers/file.h>
#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>


int main(int argc, char *argv[]) {
    barthes::init_config();
    barthes::init_screen();

    std::string filepath = barthes::get_filepath(argc, argv);

    barthes::TermConfig *tc = barthes::get_config();
    std::vector<std::string> buffer;
    buffer.push_back(filepath);
    buffer.push_back(fmt::format("Screen size: {} x {}", tc->window_size.first, tc->window_size.second));
    buffer.push_back("");

    std::vector<std::string> file_buffer = barthes::open_file(filepath);
    buffer.insert(buffer.end(), file_buffer.begin(), file_buffer.end());

    // draw initial file
    barthes::to_screen(buffer);
    barthes::set_cursor(tc);

    barthes::handle_input();
    return EXIT_SUCCESS;
}

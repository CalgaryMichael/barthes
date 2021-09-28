#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#include <barthes/config.h>
#include <barthes/handlers/file.h>
#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>
#include <barthes/handlers/terminal.h>
#include <barthes/utils/string.h>


int main(int argc, char *argv[]) {
    barthes::init_terminal();
    barthes::init_config();
    barthes::init_screen();

    std::string filepath = barthes::get_filepath(argc, argv);
    barthes::to_screen(filepath);

    barthes::TermConfig *tc = barthes::get_config();
    barthes::to_screen(barthes::build_string("Screen size: %d x %d\n", tc->window_size.first, tc->window_size.second));

    std::vector<std::string> buffer = barthes::open_file(filepath);
    for (int i = 0; i < buffer.size(); i++) {
        barthes::to_screen(buffer[i]);
    }

    barthes::handle_input();
    return EXIT_SUCCESS;
}

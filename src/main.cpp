#include <iostream>
#include <unistd.h>

#include <barthes/config.h>
#include <barthes/handlers/file.h>
#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>
#include <barthes/handlers/terminal.h>


int main(int argc, char *argv[]) {
    barthes::init_terminal();
    barthes::init_config();
    barthes::init_screen();
    char *filepath = barthes::get_filepath(argc, argv);
    std::cout << filepath << std::endl;

    barthes::TermConfig *tc = barthes::get_config();
    std::cout << "Screen size: " << tc->window_size.first << " x " << tc->window_size.second << std::endl;

    std::vector<std::string> buffer = barthes::open_file(filepath);
    for (int i = 0; i < buffer.size(); i++) {
        std::cout << buffer[i] << std::endl;
    }

    barthes::handle_input();
    return EXIT_SUCCESS;
}

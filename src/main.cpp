#include <iostream>
#include <unistd.h>

#include "config.h"
#include "handlers/file.h"
#include "handlers/input.h"
#include "handlers/screen.h"
#include "handlers/terminal.h"


int main(int argc, char *argv[]) {
    barthes::init_terminal();
    barthes::init_config();
    barthes::init_screen();
    char *filepath = barthes::get_filepath(argc, argv);
    std::cout << filepath << std::endl;

    std::vector<std::string> buffer = barthes::open_file(filepath);
    for (int i = 0; i < buffer.size(); i++) {
        std::cout << buffer[i] << std::endl;
    }

    barthes::handle_input();
    return EXIT_SUCCESS;
}

#include <iostream>
#include <string>

#include <barthes/config.h>
#include <barthes/handlers/file.h>
#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>


int main(int argc, char *argv[]) {
    std::string filepath = barthes::get_filepath(argc, argv);
    barthes::TermConfig *tc = barthes::init_config(filepath);
    barthes::init_screen();

    // draw initial file
    barthes::to_screen(tc->file_buffer);
    barthes::set_cursor(tc);

    barthes::handle_input();
    return EXIT_SUCCESS;
}

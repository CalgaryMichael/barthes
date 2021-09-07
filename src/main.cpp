#include <iostream>

#include "handlers/file.h"
#include "handlers/screen.h"


int main(int argc, char *argv[]) {
    barthes::init_screen();
    char *filepath = barthes::get_filepath(argc, argv);
    std::cout << filepath << std::endl;

    std::vector<std::string> buffer = barthes::open_file(filepath);
    for (int i = 0; i < buffer.size(); i++) {
        std::cout << buffer[i] << std::endl;
    }

    while (true) {}
    return 0;
}

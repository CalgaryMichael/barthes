#include <limits.h>
#include <iostream>
#include <stdlib.h>


void clearscreen() {
    std::cout << "\033[2J\033[1;1H";
}

/* Returns the absolute path of the filepath that was passed into program */
char* get_filepath(int argc, char *argv[]) {
    if (argc < 2) {
        throw std::invalid_argument("Please provide a file to edit");
    }

    char *filepath = new char;
    realpath(argv[1], filepath);
    return filepath;
}


int main(int argc, char *argv[]) {
    clearscreen();
    char *filepath = get_filepath(argc, argv);
    std::cout << filepath << std::endl;
    return 0;
}

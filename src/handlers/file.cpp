#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>


namespace barthes {
    /* Returns the absolute path of the filepath that was passed into program */
    std::string get_filepath(int argc, char *argv[]) {
        if (argc < 2) {
            throw std::invalid_argument("Please provide a file to edit");
        }
    
        char *filepath = new char;
        realpath(argv[1], filepath);
        return std::string(filepath);
    }
    
    /*
     * Read contents from a file path and store each line
     * as a member of a vector
     */
    std::vector<std::string> open_file(std::string filepath) {
        std::ifstream file(filepath);
        std::vector<std::string> buffer;
    
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                buffer.push_back(line);
            }
        }
    
        return buffer;
    }
}

#ifndef _BARTHES_FILE_H
#define _BARTHES_FILE_H

#include <string>
#include <vector>

namespace barthes {
    std::string get_filepath(int argc, char *argv[]);
    std::vector<std::string> open_file(std::string filepath);
}

#endif

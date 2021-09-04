#include <string>
#include <vector>

namespace barthes {
    char* get_filepath(int argc, char *argv[]);
    std::vector<std::string> open_file(char *filepath);
}

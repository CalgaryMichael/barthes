#ifndef _BARTHES_STRING_H
#define _BARTHES_STRING_H

#include <string>

namespace barthes {
    template<typename ... Args>
    std::string build_string(const std::string& format, Args ... args);
}

#endif

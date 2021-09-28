#include <memory>
#include <string>
#include <stdexcept>

#include <barthes/utils/string.h>


namespace barthes {
    /* Source: https://stackoverflow.com/a/26221725/8122894 */
    template<typename ... Args>
    std::string build_string(const std::string& format, Args ... args) {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;  // Extra space for '\0'
        if (size_s <= 0) {
            throw std::runtime_error("Error during formatting.");
        }
        auto size = static_cast<size_t>(size_s);
        auto buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1);  // We don't want the '\0' inside
    }

    // TODO: this is such a terrible hack. Surely there is another way...
    template std::string build_string(const std::string& format, int arg1);
    template std::string build_string(const std::string& format, int arg1, int arg2);
}

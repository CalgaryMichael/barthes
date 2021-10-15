#ifndef _BARTHES_CONFIG_H
#define _BARTHES_CONFIG_H

#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>

namespace barthes {
    enum class EditorMode {
        View = 0,
        Edit = 1,
    };

    typedef struct {
        EditorMode mode;
        std::pair<int, int> window_size;
        std::pair<int, int> cursor;
        std::pair<int, int> view;
        std::string filepath;
        std::vector<std::string> file_buffer;
    } TermConfig;

    TermConfig* init_config(std::string filepath);
    void set_mode(TermConfig *tc, EditorMode mode);
    int get_row_max(TermConfig *tc);
    int get_col_max(TermConfig *tc);
    std::pair<int, int> file_loc(TermConfig *tc);
    TermConfig* get_config();
}

#endif

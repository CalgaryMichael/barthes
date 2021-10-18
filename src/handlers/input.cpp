#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>

#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>
#include <barthes/config.h>
#include <barthes/exceptions.h>


namespace barthes {
    void add_newline(TermConfig *tc) {
        std::pair<int, int> file_loc = get_file_loc(tc);

        std::string existing_line = tc->file_buffer[file_loc.first];
        std::string replacement_line = existing_line.substr(0, file_loc.second);
        std::string new_line = existing_line.substr(file_loc.second, existing_line.size());

        tc->file_buffer[file_loc.first] = replacement_line;
        tc->file_buffer.insert(tc->file_buffer.begin() + file_loc.first + 1, new_line);

        to_screen(tc->file_buffer);
        move_cursor_absolute(tc, tc->cursor.first + 1, 0);
    }

    void add_ch(TermConfig *tc, int input) {
        std::pair<int, int> loc = get_file_loc(tc);
        int row = loc.first;
        int col = loc.second;

        std::string input_str(1, input);
        tc->file_buffer[row].insert(col, input_str);
        to_screen(tc->file_buffer);
        move_cursor(tc, 0, 1);
    }

    void remove_ch(TermConfig *tc) {
        std::pair<int, int> loc = get_file_loc(tc);
        int file_row = loc.first;
        int file_col = loc.second;
        if (file_col - 1 >= 0) {
            // we are erasing a char in the middle of a string
            tc->file_buffer[file_row].erase(file_col - 1, 1);
            to_screen(tc->file_buffer);
            move_cursor(tc, 0, -1);
        } else {
            // we are erasing a newline character
            if (file_row == 0) {
                // we are on the first character of the first line,
                // so there is nothing to remove
                return;
            }
            std::string current_line = tc->file_buffer[file_row];
            int col_pos = tc->file_buffer[file_row - 1].length();

            tc->file_buffer[file_row - 1].append(current_line);
            tc->file_buffer.erase(tc->file_buffer.begin() + file_row);

            to_screen(tc->file_buffer);
            move_cursor_absolute(tc, tc->cursor.first - 1, col_pos);
        }
    }

    int get_keypress() {
        return getch();
    }

    KeypressResponse handle_keypress(int input) {
        TermConfig *tc = get_config();
        KeypressResponse response = tc->mode == EditorMode::View ?
            handle_view_keypress(tc, input) :
            handle_edit_keypress(tc, input);
        return response;
    }

    KeypressResponse handle_view_keypress(TermConfig *tc, int input) {
        KeypressResponse response = KeypressResponse::Continue;
        switch (input) {
            // KEY_DOWN moves you *visually* down, but "up" on current row number
            case KEY_DOWN:
            case 'j':
                move_cursor(tc, UP, 0);
                break;
            // KEY_UP moves you *visually* up, but "down" on the current row number
            case KEY_UP:
            case 'k':
                move_cursor(tc, DOWN, 0);
                break;
            case KEY_RIGHT:
            case 'l':
                move_cursor(tc, 0, RIGHT);
                break;
            case KEY_LEFT:
            case 'h':
                move_cursor(tc, 0, LEFT);
                break;
            case CTRL_KEY('e'):
                set_mode(tc, EditorMode::Edit);
                break;
            case CTRL_KEY('q'):
                response = KeypressResponse::Exit;
                break;
            default:
                break;
        }

        return response;
    }

    KeypressResponse handle_edit_keypress(TermConfig *tc, int input) {
        KeypressResponse response = KeypressResponse::Continue;
        switch (input) {
            // KEY_DOWN moves you *visually* down, but "up" on current row number
            case KEY_DOWN:
                move_cursor(tc, UP, 0);
                break;
            // KEY_UP moves you *visually* up, but "down" on the current row number
            case KEY_UP:
                move_cursor(tc, DOWN, 0);
                break;
            case KEY_RIGHT:
                move_cursor(tc, 0, RIGHT);
                break;
            case KEY_LEFT:
                move_cursor(tc, 0, LEFT);
                break;
            case CTRL_KEY('v'):
                set_mode(tc, EditorMode::View);
                break;
            case CTRL_KEY('q'):
                response = KeypressResponse::Exit;
                break;
            case KEY_F(1):
            case KEY_F(2):
            case KEY_F(3):
            case KEY_F(4):
            case KEY_F(5):
            case KEY_F(6):
            case KEY_F(7):
            case KEY_F(8):
            case KEY_F(9):
            case KEY_F(10):
            case KEY_F(11):
            case KEY_F(12):
                break;
            case KEY_ENTER:
            case '\n':
                add_newline(tc);
                break;
            case KEY_BACKSPACE:
            case KEY_DC:
            case 127:
                remove_ch(tc);
                break;
            default:
                add_ch(tc, input);
                break;
        }
        return response;
    }

    void handle_input() {
        while (true) {
            int input = get_keypress();
            KeypressResponse response = handle_keypress(input);
            if (response == KeypressResponse::Exit) {
                return;
            }
        }
    }
}

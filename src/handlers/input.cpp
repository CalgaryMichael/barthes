#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>

#include <barthes/handlers/input.h>
#include <barthes/handlers/screen.h>
#include <barthes/config.h>
#include <barthes/exceptions.h>


namespace barthes {
    void move_cursor(TermConfig *tc, int row_diff, int col_diff) {
        int row_max = tc->file_buffer.size() -1;
        tc->cursor.first = std::clamp<int>(tc->cursor.first + row_diff, 0, row_max);

        int col_max = tc->file_buffer[tc->cursor.first].length() + 1;
        tc->cursor.second = std::clamp<int>(tc->cursor.second + col_diff, 0, col_max);
        set_cursor(tc);
    }

    void move_cursor_absolute(TermConfig *tc, int row, int col) {
        int row_max = tc->file_buffer.size() -1;
        tc->cursor.first = std::clamp<int>(row, 0, row_max);

        int col_max = tc->file_buffer[tc->cursor.first].length() + 1;
        tc->cursor.second = std::clamp<int>(col, 0, col_max);
        set_cursor(tc);
    }

    void add_newline(TermConfig *tc) {
        int row = tc->cursor.first;
        int col = tc->cursor.second;

        std::string existing_line = tc->file_buffer[row];
        std::string replacement_line = existing_line.substr(0, col);
        std::string new_line = existing_line.substr(col, existing_line.size());

        tc->file_buffer[row] = replacement_line;
        tc->file_buffer.insert(tc->file_buffer.begin() + row + 1, new_line);

        to_screen(tc->file_buffer);
        move_cursor_absolute(tc, row + 1, 0);
    }

    void add_ch(TermConfig *tc, int input) {
        int row = tc->cursor.first;
        int col = tc->cursor.second;

        std::string input_str(1, input);
        tc->file_buffer[row].insert(col, input_str);
        to_screen(tc->file_buffer);
        move_cursor(tc, 0, 1);
    }

    void remove_ch(TermConfig *tc) {
        int row = tc->cursor.first;
        int col = tc->cursor.second;
        if (col - 1 >= 0) {
            tc->file_buffer[row].erase(col - 1, 1);
            to_screen(tc->file_buffer);
            move_cursor(tc, 0, -1);
        } else {
            if (row == 0) {
                // we are on the first character of the first line,
                // so there is nothing to remove
                return;
            }
            std::string current_line = tc->file_buffer[row];
            int col_pos = tc->file_buffer[row - 1].length();

            tc->file_buffer[row - 1].append(current_line);
            tc->file_buffer.erase(tc->file_buffer.begin() + row);

            to_screen(tc->file_buffer);
            move_cursor_absolute(tc, row - 1, col_pos);
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
        // TODO: set up keyboard handling when in "Edit" mode
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

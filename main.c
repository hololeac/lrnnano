#include <ncurses.h>
#include <stdlib.h>
#include "text.h"

int main() {
    FILE *fptr;
    text_t *content = initialize_content();

    fptr = fopen("test_text.txt", "rt");
    char line[250];

    while(fgets(line, 250, fptr)) {
        add_line(line, content);
    }

    // Close the file
    fclose(fptr);
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int ch;
    int row = 0;
    int col = 0;

    refresh();

    for (int i = 0; i < content->count; i++) {
        addstr(content->lines[i]->line);
        row++;
        move(row, col);
        refresh();
    }

    // Main input loop
    while (1) {
        ch = getch();
        if (ch == ('x' & 0x1F)) {
            clear();
            refresh();
            endwin();
            return 0;
        }

        if (ch == KEY_LEFT) {
            if (col > 0) {
                col--;
                move(row, col);
            } else if (row > 0) {
                row--;
                col = content->lines[row]->len;
                move(row, col);
            }
        } else if (ch == KEY_RIGHT) {
            //TODO: fix the seg fault for accessing the line that not exist
            if (col < content->lines[row]->len) {
                col++;
                move(row, col);
            } else if (row < content->count) {
                row++;
                col = 0;
                move(row, col);
            }
        } else if (ch == KEY_UP) {
            if (row > 0) row--;
            move(row, col);
        } else if (ch == KEY_DOWN) {
            if (row < LINES - 1) row--;
            move(row, col);
        }

        getyx(stdscr, row, col);
        refresh();
    }

    endwin();

    free_content(content);
    return 0;
}
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
    free_content(content);
    // initscr();
    // raw();
    // keypad(stdscr, TRUE);
    // noecho();

    // int ch;
    // int row = 0;
    // int col = 0;

    // refresh();

    // // Main input loop
    // while (1) {
    //     ch = getch();
    //     if (ch == ('x' & 0x1F)) {
    //         clear();
    //         refresh();
    //         endwin();
    //         return 0;
    //     }

    //     if (ch == KEY_LEFT) {
    //         if (col > 0) --col;
    //         move(row, col);
    //     } else if (ch == KEY_RIGHT) {
    //         if (col < COLS - 1) ++col;
    //         move(row, col);
    //     } else if (ch == KEY_UP) {
    //         if (row > 2) --row;   // don't overwrite the instruction line(s)
    //         move(row, col);
    //     } else if (ch == KEY_DOWN) {
    //         if (row < LINES - 1) ++row;
    //         move(row, col);
    //     }

    //     getyx(stdscr, row, col);
    //     addch(ch);
    //     refresh();
    // }

    // endwin();
    return 0;
}
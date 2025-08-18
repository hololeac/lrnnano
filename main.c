#include <ncurses.h>
#include <stdlib.h>

int main() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int ch;
    int row = 0;
    int col = 0;

    mvprintw(0, 0, "Type characters (Press Ctrl+: to exit):");
    move(2, 0);
    refresh();

    // Main input loop
    while (1) {
        ch = getch();
        if (ch == ':' && (ch & 0x1F)) {
            clear();
            refresh();
            endwin();
            return 0;
        }

        getyx(stdscr, row, col);
        addch(ch);
        refresh();
    }

    endwin();
    return 0;
}
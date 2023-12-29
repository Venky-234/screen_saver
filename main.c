#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void delay_millis(int millis)
{
    usleep(millis * 1000);
}
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("no string entered ... exiting\n");
        exit(-1);
    }

    initscr();
    curs_set(0);
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);

    if (has_colors() == FALSE)
    {
        printf("Your terminal does not support color\n");
        exit(1);
    }
    int str_len = strlen(argv[1]);

    WINDOW *win = newwin(3, str_len + 2, 3, 3);

    wattron(win, A_REVERSE);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, argv[1]);
    wattroff(win, A_REVERSE);

    wrefresh(win);
    refresh();
    int x = 3;
    int y = 3;
    int multiply_x = 1;
    int multiply_y = 1;
    while (true)
    {

        int max_x = getmaxx(stdscr);
        int max_y = getmaxy(stdscr);
        refresh();
        clear();
        mvwin(win, y, x);
        wrefresh(win);
        x += 1 * multiply_x;
        y += 1 * multiply_y;

        if (x + str_len + 2 >= max_x)
        {
            multiply_x = -1;
        }
        if (x <= 0)
        {
            multiply_x = 1;
        }
        if (y + 3 >= max_y)
        {
            multiply_y = -1;
        }
        if (y <= 0)
        {
            multiply_y = 1;
        }
        delay_millis(170);
    }
    getch();
    endwin();
}
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <ncurses.h>
#include "labyrinth.h"
#include "human.h"

#define STEP_SLEEP 300 //milliseconds

using namespace std;

/**
      0 1 2 3 4 5 6 7 8 9
      _ _ _ _ _ _ _ _ _ _
    0|X X                 |
    1|X X X X   X X X X E |
    2|X     X       X X X |
    3|X   X X X X   X X X |
    4|X         X   X   X |
    5|X   X X   X   X   X |
    6|X         X       X |
    7|B   X X       X   X |
    8|X X X X X X X X X X |

    B - (0,7)
    E - (9,1)

    Cell's value:
        B -- begin point
        E -- end point(exit)
        X -- wall
        S -- space

*/

int main() {
    char **N = nullptr;
    labyrinth foo; //creating labyrinth
    N = foo.getLabCopy(); //getting  modify lab (withouth deadlocks)
    char **original = nullptr;
    original = foo.getLabOriginal(); //getting original map
    human vasya(N, foo.getPointBegin(), foo.getPointEnd(), foo.genCorner()); //make human

    initscr();
    noecho();

    unsigned int maxX, maxY;
    const char* msg = "Labyrinth (press any key)";
    box(stdscr, '|', '-');
    getmaxyx(stdscr, maxY, maxX);
    mvwprintw(stdscr, 1, (maxX-strlen(msg))/2, msg);
    getch();

    while(vasya.run()) {
        for (int i = 0; i < foo.getWidth(); i++) //Drowing
            for (int j = 0; j < foo.getHeight(); j++) {
                mvaddch(j+3, i+2, N[i][j]); //Drowing modify lab
                mvaddch(j+3, i+17, original[i][j]); //Drowing original map
                if ((N[i][j]) == 'S') mvaddch(j+3, i+17, 'S'); //Drowing footseps on orgignal map
                mvprintw(12, 2, "Modifed map");
                mvprintw(12, 16, "Original map");

            }
        refresh();
        usleep(STEP_SLEEP*1000); //Timeout
    }

    box(stdscr, '|', '-');
    curs_set(0);
    getch();
    endwin();
    return 0;
}

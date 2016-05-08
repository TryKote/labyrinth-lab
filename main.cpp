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

int main() //Where is my mind -- Pixies
{
    char **N = nullptr;
    labyrinth foo; //creating labyrinth
    N = foo.getLabCopy();
    char **original = nullptr;
    original = foo.getLabOriginal();
    human vasya(N, foo.getPointBegin(), foo.getPointEnd(), foo.genCorner());
    int maxStepsToGoExitFromLab = 10 * 9; //I can do it with "while"(exit on end-cell), but i don't want.
    //for (int i = 0; i < maxStepsToGoExitFromLab; i++) vasya.run();

    initscr();

    unsigned int maxX, maxY;
    const char* msg = "Labyrinth (press any key)";
    box(stdscr, '|', '-');
    getmaxyx(stdscr, maxY, maxX);
    mvwprintw(stdscr, 1, (maxX-strlen(msg))/2, msg);
    getch();
    for (int i = 0; i < maxStepsToGoExitFromLab; i++) {
        for (int i = 0; i < foo.getWidth(); i++) //Drowing
            for (int j = 0; j < foo.getHeight(); j++) {
                mvaddch(j+2, i+2, N[i][j]);
                mvaddch(j+2, i+15, original[i][j]);
            }
        vasya.run();
        refresh();
        usleep(STEP_SLEEP*1000);

    }
    box(stdscr, '|', '-');
    curs_set(0);
    getch();
    endwin();
    return 0;
}

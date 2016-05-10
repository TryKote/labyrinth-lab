#include <iostream>
#include <ncurses.h>
#include "human.h"

using std::cout;
using std::endl;

human::human(char **map, point cellBegin, point cellEnd, point corner) {
    TheMap = map;
    width = corner.x + 1; //get width value of the corner
    height = corner.y + 1; //get height value of the corner
    CellBegin = cellBegin;
    CellEnd = cellEnd;
    TheMap[CellEnd.x][CellEnd.y] = ' ';

    first->place = CellBegin;
    first->prev = nullptr;
    current = first;
}

point human::goAround(point now) { //returning next cell, where we can to go
    point tempPoint;
    int x = now.x;
    int y = now.y;
    if ((x < width-1) && (x > 0) && (y < height-1) && (y > 0)) { //in square with border from 1 cell
        if (TheMap[x-1][y] == ' ') {
            TheMap[x-1][y] = 'S';
            tempPoint.x = x-1;
            tempPoint.y = y;
            return tempPoint;
        } else
        if (TheMap[x+1][y] == ' ') {
            TheMap[x+1][y] = 'S';
            tempPoint.x = x+1;
            tempPoint.y = y;
            return tempPoint;
        } else
        if (TheMap[x][y+1] == ' ') {
            TheMap[x][y+1] = 'S';
            tempPoint.x = x;
            tempPoint.y = y+1;
            return tempPoint;
        } else
        if (TheMap[x][y-1] == ' ') {
            TheMap[x][y-1] = 'S';
            tempPoint.x = x;
            tempPoint.y = y-1;
            return tempPoint;
        }
    } else {
        if ((x == 0) && (y > 0) && (y < height-1)) { //left border without (0;0) and (0; height-1)
            if (TheMap[x][y-1] == ' ') {
                TheMap[x][y-1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y-1;
                return tempPoint;
            } else
            if (TheMap[x][y+1] == ' ') {
                TheMap[x][y+1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y+1;
                return tempPoint;
            } else
            if (TheMap[x+1][y] == ' ') {
                TheMap[x+1][y] = 'S';
                tempPoint.x = x+1;
                tempPoint.y = y;
                return tempPoint;
            }
        } else
        if ((x == width-1) && (y > 0) && (y < height-1)) { //right border without (width-1;0) and (width-1;height-1)
            if (TheMap[x][y-1] == ' ') {
                TheMap[x][y-1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y-1;
                return tempPoint;
            } else
            if (TheMap[x][y+1] == ' ') {
                TheMap[x][y+1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y+1;
                return tempPoint;
            } else
            if (TheMap[x-1][y] == ' ') {
                TheMap[x-1][y] = 'S';
                tempPoint.x = x-1;
                tempPoint.y = y;
                return tempPoint;
            }
        } else
        if ((y == 0) && (x > 0) && (x < width-1)) { //top border without (0;0) and (width-1; 0)
            if (TheMap[x-1][y] == ' ') {
                TheMap[x-1][y] = 'S';
                tempPoint.x = x-1;
                tempPoint.y = y;
                return tempPoint;
            } else
            if (TheMap[x+1][y] == ' ') {
                TheMap[x+1][y] = 'S';
                tempPoint.x = x+1;
                tempPoint.y = y;
                return tempPoint;
            } else
            if (TheMap[x][y+1] == ' ') {
                TheMap[x][y+1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y+1;
                return tempPoint;
            }
        } else
        if ((y == height-1) && (x > 0) && (x < width-1)) { //bottom border without (0;height-1) and (width-1;height-1)
            if (TheMap[x-1][y] == ' ') {
                TheMap[x-1][y] = 'S';
                tempPoint.x = x-1;
                tempPoint.y = y;
                return tempPoint;
            } else
            if (TheMap[x+1][y] == ' ') {
                TheMap[x+1][y] = 'S';
                tempPoint.x = x+1;
                tempPoint.y = y;
                return tempPoint;
            } else
            if (TheMap[x][y-1] == ' ') {
                TheMap[x][y-1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y-1;
                return tempPoint;
            }
        } else
        if ((x == 0) && (y == 0)) { //top-left cell
            if (TheMap[x+1][y] == ' ') {
                TheMap[x+1][y] = 'S';
                tempPoint.x = x+1;
                tempPoint.y = y;
                return tempPoint;
            } else
            if (TheMap[x][y+1] == ' ') {
                TheMap[x][y+1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y+1;
                return tempPoint;
            }
        } else
        if ((x == width-1) && (y == 0)) { //top-right cell
            if (TheMap[x-1][y] == ' ') {
                TheMap[x-1][y] = 'S';
                tempPoint.x = x-1;
                tempPoint.y = y;
                return tempPoint;
            } else
            if (TheMap[x][y+1] == ' ') {
                TheMap[x][y+1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y+1;
                return tempPoint;
            }
        } else
        if ((x == 0) && (y == height-1)) { //bottom-left cell
            if (TheMap[x+1][y] == ' ') {
                TheMap[x+1][y] = 'S';
                tempPoint.x = x+1;
                tempPoint.y = y;
                return tempPoint;
            } else
            if (TheMap[x][y-1] == ' ') {
                TheMap[x][y-1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y-1;
                return tempPoint;
            }
        } else
        if ((x == width-1) && (y == height-1)) { //bottom-right cell
            if (TheMap[x-1][y] == ' ') {
                TheMap[x-1][y] = 'S';
                tempPoint.x = x-1;
                tempPoint.y = y;
                return tempPoint;
            } else
            if (TheMap[x][y-1] == ' ') {
                TheMap[x][y-1] = 'S';
                tempPoint.x = x;
                tempPoint.y = y-1;
                return tempPoint;
            }
        }
    }
    return tempPoint;
}

bool human::run() {
    WhereAmI *nextStep = new WhereAmI;
    nextStep->place = goAround(current->place);
    current->footprint++;
    nextStep->prev = current;
    current = nextStep;
    initscr();
    curs_set(0);
    if ((current->place.x != -1) || (current->place.y != -1)) { //if -1 nowhere to go (deadlock)
        mvwprintw(stdscr, 14, 7, "Go on: (%d;%d)", current->place.x,  current->place.y);
        box(stdscr, '|', '-');
    } else {
        return false; //saying, we are on finish-cell
        endwin();
    }
    return true;
    endwin();
}

char **human::getMap() {
    return TheMap;
}

human::~human()
{
    //dtor
}

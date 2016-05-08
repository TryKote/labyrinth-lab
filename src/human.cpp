#include <iostream>
#include <ncurses.h>
#include "human.h"

using std::cout;
using std::endl;

human::human(char **map, point cellBegin, point cellEnd, point corner) {
    TheMap = map;
    width = corner.x + 1;
    height = corner.y + 1;
    //cout << "HUMAN(begin): " << cellBegin.x << ":" << cellBegin.y << endl;
    //cout << "HUMAN(end): " << cellEnd.x << ":" << cellEnd.y << endl;
    CellBegin = cellBegin;
    CellEnd = cellEnd;
    TheMap[CellEnd.x][CellEnd.y] = ' ';

    first->direction = 'r'; //needlessly
    first->place = CellBegin;
    first->prev = nullptr;
    current = first;
}

point human::goAround(point now) {
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
    //cout << "BEFORE human::run() current->place: (" << current->place.x << ":" << current->place.y << ")\n";
    WhereAmI *nextStep = new WhereAmI;
    nextStep->place = goAround(current->place);
    current->footprint++;
    nextStep->prev = current;
    current = nextStep;
    initscr(); //12
    if ((current->place.x != -1) || (current->place.y != -1)) { //if -1 nowhere to go
        //cout << "Go on: (" << current->place.x << ":" << current->place.y << ")\n";
        mvwprintw(stdscr, 12, 1, "Go on: (%d;%d)", current->place.x,  current->place.y);
        box(stdscr, '|', '-');
        curs_set(0);
    } else {
        return false;
        endwin();
    }
    endwin();
}

char **human::getMap() {
    return TheMap;
}

human::~human()
{
    //dtor
}

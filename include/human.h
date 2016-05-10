#pragma once

#include "labyrinth.h"

struct WhereAmI {
    point place;
    int footprint = 0;
    WhereAmI *prev;
};

class human
{
    public:
        human(char **map, point cellBegin, point cellEnd, point corner); //corner to max sizes of labyrinth
        ~human();
        bool run();
        void goBack();
        char **getMap();

    protected:

    private:
        point goAround(point now);
        char **TheMap;
        int width, height;
        point CellBegin, CellEnd;
        WhereAmI *first = new WhereAmI;
        WhereAmI *current = nullptr;
};

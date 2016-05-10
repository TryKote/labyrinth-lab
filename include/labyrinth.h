#pragma once
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
       ' '-- space

*/
struct point{
    int x = -1;
    int y = -1;
};

class labyrinth
{
    public:
        labyrinth();
        ~labyrinth();
        char **getLabOriginal();
        char **getLabCopy();
        int getWidth();
        int getHeight();
        point genCorner();
        point getPointBegin();
        point getPointEnd();

    protected:

    private:
        void fillingDL(char **lab);
        bool isOnCenterDL(char **lab, int x, int y);
        void mapCreate(bool gen);
        static const int width = 10;
        static const int height = 9;
        //char cell[labyrinth::width][labyrinth::height];
        char **cell = new char *[width];
        char **CopyCell = new char *[width];
        char *pCellBegin = nullptr;// "B" on pic
        char *pCellEnd = nullptr;//"E" on pic
        point cellBegin;
        point cellEnd;
};

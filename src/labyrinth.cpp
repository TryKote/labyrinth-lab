#include <iostream>
#include "labyrinth.h"

using std::cout;
using std::endl;
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
labyrinth::labyrinth() {
    //Creating default labyrinth:

    //Creating area of cells
    for (int i = 0; i < width; i++) {
        cell[i] = new char[height];
    }

    //Analogy CopyCell:
    //Creating area of cells
    for (int i = 0; i < width; i++) {
        CopyCell[i] = new char[height];
    }
    //Begin cell
    CopyCell[0][7] = 'B';
    pCellBegin = &CopyCell[0][7];
    cellBegin.x = 0;
    cellBegin.y = 7;
    //End cell
    CopyCell[9][1] = 'E';
    pCellEnd = &CopyCell[9][1];
    cellEnd.x = 9;
    cellEnd.y = 1;

    mapCreate(0);
    fillingDL(CopyCell);

}

void labyrinth::mapCreate(bool gen) {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            cell[j][i] = ' ';

    for (int i = 0; i < height; i++)
        if (i != 7) cell[0][i] = 'X';
    cell[1][0] = 'X';
    cell[1][1] = 'X';
    cell[1][8] = 'X';

    cell[2][1] = 'X';
    cell[2][3] = 'X';
    cell[2][5] = 'X';
    cell[2][7] = 'X';
    cell[2][8] = 'X';

    cell[3][1] = 'X';
    cell[3][2] = 'X';
    cell[3][3] = 'X';
    cell[3][5] = 'X';
    cell[3][7] = 'X';
    cell[3][8] = 'X';

    cell[4][3] = 'X';
    cell[4][8] = 'X';

    cell[5][1] = 'X';
    cell[5][3] = 'X';
    cell[5][4] = 'X';
    cell[5][5] = 'X';
    cell[5][6] = 'X';
    cell[5][8] = 'X';

    cell[6][1] = 'X';
    cell[6][8] = 'X';

    cell[7][1] = 'X';
    cell[7][2] = 'X';
    cell[7][3] = 'X';
    cell[7][4] = 'X';
    cell[7][5] = 'X';
    cell[7][7] = 'X';
    cell[7][8] = 'X';

    cell[8][1] = 'X';
    cell[8][2] = 'X';
    cell[8][3] = 'X';
    cell[8][8] = 'X';

    cell[9][2] = 'X';
    cell[9][3] = 'X';
    cell[9][4] = 'X';
    cell[9][5] = 'X';
    cell[9][6] = 'X';
    cell[9][7] = 'X';
    cell[9][8] = 'X';

    //Begin cell
    cell[0][7] = 'B';
    //End cell
    cell[9][1] = 'E';

    //COPY CREATE

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            CopyCell[j][i] = ' ';

    for (int i = 0; i < height; i++)
        if (i != 7) CopyCell[0][i] = 'X';
    CopyCell[1][0] = 'X';
    CopyCell[1][1] = 'X';
    CopyCell[1][8] = 'X';

    CopyCell[2][1] = 'X';
    CopyCell[2][3] = 'X';
    CopyCell[2][5] = 'X';
    CopyCell[2][7] = 'X';
    CopyCell[2][8] = 'X';

    CopyCell[3][1] = 'X';
    CopyCell[3][2] = 'X';
    CopyCell[3][3] = 'X';
    CopyCell[3][5] = 'X';
    CopyCell[3][7] = 'X';
    CopyCell[3][8] = 'X';

    CopyCell[4][3] = 'X';
    CopyCell[4][8] = 'X';

    CopyCell[5][1] = 'X';
    CopyCell[5][3] = 'X';
    CopyCell[5][4] = 'X';
    CopyCell[5][5] = 'X';
    CopyCell[5][6] = 'X';
    CopyCell[5][8] = 'X';

    CopyCell[6][1] = 'X';
    CopyCell[6][8] = 'X';

    CopyCell[7][1] = 'X';
    CopyCell[7][2] = 'X';
    CopyCell[7][3] = 'X';
    CopyCell[7][4] = 'X';
    CopyCell[7][5] = 'X';
    CopyCell[7][7] = 'X';
    CopyCell[7][8] = 'X';

    CopyCell[8][1] = 'X';
    CopyCell[8][2] = 'X';
    CopyCell[8][3] = 'X';
    CopyCell[8][8] = 'X';

    CopyCell[9][2] = 'X';
    CopyCell[9][3] = 'X';
    CopyCell[9][4] = 'X';
    CopyCell[9][5] = 'X';
    CopyCell[9][6] = 'X';
    CopyCell[9][7] = 'X';
    CopyCell[9][8] = 'X';

    //Begin CopyCell
    CopyCell[0][7] = 'B';
    //End CopyCell
    CopyCell[9][1] = 'E';
}

bool labyrinth::isOnCenterDL(char **lab, int x, int y) {
    if (((((lab[x][y-1]) == 'X') && ((lab[x+1][y]) == 'X') && ((lab[x][y+1]) == 'X')) || (((lab[x-1][y]) == 'X') && ((lab[x+1][y]) == 'X') && ((lab[x][y+1]) == 'X')) || (((lab[x][y-1]) == 'X') && ((lab[x-1][y]) == 'X') && ((lab[x][y+1]) == 'X')) || (((lab[x][y-1]) == 'X') && ((lab[x-1][y]) == 'X') && ((lab[x+1][y]) == 'X'))) && (lab[x][y] != 'X'))
        lab[x][y] = 'X';
    else return 0;
    return 1;
}

void labyrinth::fillingDL(char **lab) {
    for (int limit = 0; limit < width*height; limit++)
        for (int i = 1; i < width-1; i++) {
            for (int j = 1; j < height-1; j++) {
                if ((i != 0) && (i != 0)) {
                    isOnCenterDL(lab, i, j);
                }
            }
        }
    //[X][Y]
    //X:
    // FIXME (kote#1#): Replace all specific values (8 and 9) to (width - 1 and height - 1)
    // FIXED.
    for (int i = 1; i < width; i++) { //X
        //Height 0(left)
        if ((lab[i-1][0] == 'X') && (lab[i][0+1] == 'X')) lab[i][0] = 'X';
    }

    for (int i = 0; i < width-1; i++) { //X
        //Heitht 0(right)
        if ((lab[i+1][0] == 'X') && (lab[i][0+1] == 'X')) lab[i][0] = 'X';
    }

    for (int i = 1; i < width; i++) { //X
        //Height 8(left)
        if ((lab[i-1][width - 1] == 'X') && (lab[i][width - 1-1] == 'X')) lab[i][width - 1] = 'X';
    }

    for (int i = 0; i < width-1; i++) { //X
        //Heitht 8(right)
        if ((lab[i+1][width - 1] == 'X') && (lab[i][width - 1-1] == 'X')) lab[i][width - 1] = 'X';
    }

    //Y:
    for (int i = 1; i < height; i++) { //Y
        //Width 0(top)
        if ((lab[0][i-1] == 'X') && (lab[0+1][i] == 'X')) lab[i][0] = 'X';
    }

    for (int i = 0; i < height-1; i++) { //Y
        //Width 0(bottom)
        if ((lab[0][i+1] == 'X') && (lab[0+1][i] == 'X')) lab[i][0] = 'X';
    }

    for (int i = 1; i < height; i++) { //Y
        //Width 9(top)
        if ((lab[height - 1][i-1] == 'X') && (lab[height - 1-1][i] == 'X')) lab[i][9] = 'X';
    }

    for (int i = 0; i < height-1; i++) { //Y
        //Width 9(bottom)
        if ((lab[height - 1][i+1] == 'X') && (lab[9-1][i] == 'X')) lab[i][height - 1] = 'X';
    }
}

labyrinth::~labyrinth() {
    //dtor
}

int labyrinth::getHeight() {
    return height;
}

int labyrinth::getWidth() {
    return width;
}

char **labyrinth::getLabOriginal() {
    return cell;
}

char **labyrinth::getLabCopy() {
    return CopyCell;
}

point labyrinth::genCorner() {
    point corner;
    corner.x = width-1;
    corner.y = height-1;
    return corner;
}

point labyrinth::getPointBegin() {
    return cellBegin;
}

point labyrinth::getPointEnd() {
    return cellEnd;
}

#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <unistd.h>
#include <vector>
#include <iomanip>

using namespace std;

class State
{
    private:
        
        int XindexOf0 = 3;
        int YindexOf0 = 3;

    public:

        int positions[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
        vector<char> potentialMoves = {'U', 'L'};
        int HammingDist();
        int ManhattanDist();
        bool isSolved();
        void findPotentialMoves();
        void move(char type);
        void shufflePuzzle (int moves);
        void printPuzzle();
};

#endif
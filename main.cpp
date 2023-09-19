#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class State
{
    private:
    
        void findPotentialMoves(int XindexOf0, int YindexOf0, vector<char> &potentialMoves);
        void move(char type, int positions[4][4], int &XindexOf0, int &YindexOf0);
        int HammingDist(int positions[4][4]);
        int ManhattanDist(int positions[4][4]);

    public:

        int positions[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
        vector<char> potentialMoves = {'U', 'L'};
        int XindexOf0 = 3;
        int YindexOf0 = 3;

        void shufflePuzzle (int positions[4][4], int &XindexOf0, int &YindexOf0, int moves);
        void printPuzzle(int positions[4][4]);
        bool isSolved(int positions[4][4]);
};

int main()
{
    srand(time(NULL));

    State shuffled;

    cout << endl;

    shuffled.shufflePuzzle(shuffled.positions, shuffled.XindexOf0, shuffled.YindexOf0, 1000);
    shuffled.printPuzzle(shuffled.positions); 

    return 0;
}

// updates potentialMoves vector to reflect all current legal moves
void State::findPotentialMoves(int XindexOf0, int YindexOf0, vector<char> &potentialMoves)
{
    if (YindexOf0 == 0)
    {
        if (XindexOf0 == 0)
        {
            potentialMoves = {'D', 'R'};
        }

        else if (XindexOf0 == 1 || XindexOf0 == 2)
        {
            potentialMoves = {'D', 'L', 'R'};
        }

        else if (XindexOf0 == 3)
        {
            potentialMoves = {'D', 'L'};
        }
    }

    else if (YindexOf0 == 1 || YindexOf0 == 2)
    {
        if (XindexOf0 == 0)
        {
            potentialMoves = {'U', 'D', 'R'};
        }

        else if (XindexOf0 == 1 || XindexOf0 == 2)
        {
            potentialMoves = {'U', 'D', 'L', 'R'};
        }

        else if (XindexOf0 == 3)
        {
            potentialMoves = {'U', 'D', 'L'};
        }
    }

    else if (YindexOf0 == 3)
    {
        if (XindexOf0 == 0)
        {
            potentialMoves = {'U', 'R'};
        }

        else if (XindexOf0 == 1 || XindexOf0 == 2)
        {
            potentialMoves = {'U', 'L', 'R'};
        }

        else if (XindexOf0 == 3)
        {
            potentialMoves = {'U', 'L'};
        }
    }
}

// swaps the X with an adjacent number
void State::move(char type, int positions[4][4], int &XindexOf0, int &YindexOf0)
{
    int xchange = 0;
    int ychange = 0;
    int *pXchange = &xchange;
    int *pYchange = &ychange;

    switch (type)
    {
        case 'U': *pYchange = -1;
        break;

        case 'D': *pYchange = 1;
        break;

        case 'L': *pXchange = -1;
        break;

        case 'R': *pXchange = 1;
    }

    // updates location of swapped number to where the 0 was
    positions[YindexOf0][XindexOf0] = positions[YindexOf0 + ychange][XindexOf0 + xchange];

    // updates location of the X to where swapped number was
    positions[YindexOf0 + ychange][XindexOf0 + xchange] = 0;

    // updates values for location of 0
    XindexOf0 = XindexOf0 + xchange;
    YindexOf0 = YindexOf0 + ychange;

    // updates legal moves
    findPotentialMoves(XindexOf0, YindexOf0, potentialMoves);
}

// performs 'moves' random moves
void State::shufflePuzzle (int positions[4][4], int &XindexOf0, int &YindexOf0, int moves)
{  
    for (int i = 0; i < moves; i++)
    {
        // chooses a random direction from the potentialMoves vector
        int rng = rand() % size(potentialMoves);
        char choice = potentialMoves[rng];

        // moves in that direction
        move(choice, positions, XindexOf0, YindexOf0);
    }
}

// prints the location of all numbers in a (4x4) grid
void State::printPuzzle(int positions[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        cout << left << setw(4) << positions[i][0] << setw(4) << positions[i][1] << setw(4) << positions[i][2] << positions[i][3] << endl;
    }
    cout << endl;
}

// returns number of incorect values
int State::HammingDist(int positions[4][4])
{
    int heuristic = 0;

    // for each index...
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // increments heuristic if value is not what it should be (unless it is 0)
            if (positions[i][j] != 1 + j + 4 * i && positions[i][j] != 0)
            {
                heuristic += 1;
            }
        }
    }
    return heuristic;
}

// returns sum of all distances from correct value
int State::ManhattanDist(int positions[4][4])
{
    int heuristic = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (positions[i][j] != 0)
            {
                // finds expected x and y values
                int x = (positions[i][j] - 1) % 4;
                int y = (positions[i][j] - 1) / 4;

                // adds difference between expected and actual to heuristic
                heuristic = heuristic + abs(x - j) + abs(y - i);
            }
        }
    }

    return heuristic;
}

bool State::isSolved(int positions[4][4])
{
    for(int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // returns false if any value is not what it should be (unless it is 0)
            if(positions[i][j] != 1 + j + 4 * i && positions[i][j] != 0)
            {
                return false;
            }
        }
    }  
    return true;
}
#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

using namespace std;

class State
{
    private:
    
        void findPotentialMoves(int XindexOfX, int YindexOfX, vector<char> &potentialMoves);
        void move(char type, char positions[3][3], int &XindexOfX, int &YindexOfX);
        int HammingDist(char positions[3][3]);
        int ManhattanDist(char positions[3][3]);

    public:

        char positions[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', 'X'}};
        vector<char> potentialMoves = {'U', 'L'};
        int XindexOfX = 2;
        int YindexOfX = 2;

        void shufflePuzzle (char positions[3][3], int &XindexOfX, int &YindexOfX, int moves);
        void printPuzzle(char positions[3][3]);
        bool isSolved(char positions[3][3]);
};

int main()
{
    srand(time(NULL));

    State shuffled;

    cout << endl;

    shuffled.shufflePuzzle(shuffled.positions, shuffled.XindexOfX, shuffled.YindexOfX, 1000);
    shuffled.printPuzzle(shuffled.positions); 

    return 0;
}

// updates potentialMoves vector to reflect all current legal moves
void State::findPotentialMoves(int XindexOfX, int YindexOfX, vector<char> &potentialMoves)
{
    if (YindexOfX == 0)
    {
        if (XindexOfX == 0)
        {
            potentialMoves = {'D', 'R'};
        }

        else if (XindexOfX == 1)
        {
            potentialMoves = {'D', 'L', 'R'};
        }

        else if (XindexOfX == 2)
        {
            potentialMoves = {'D', 'L'};
        }
    }

    else if (YindexOfX == 1)
    {
        if (XindexOfX == 0)
        {
            potentialMoves = {'U', 'D', 'R'};
        }

        else if (XindexOfX == 1)
        {
            potentialMoves = {'U', 'D', 'L', 'R'};
        }

        else if (XindexOfX == 2)
        {
            potentialMoves = {'U', 'D', 'L'};
        }
    }

    else if (YindexOfX == 2)
    {
        if (XindexOfX == 0)
        {
            potentialMoves = {'U', 'R'};
        }

        else if (XindexOfX == 1)
        {
            potentialMoves = {'U', 'L', 'R'};
        }

        else if (XindexOfX == 2)
        {
            potentialMoves = {'U', 'L'};
        }
    }
}

// swaps the X with an adjacent number
void State::move(char type, char positions[3][3], int &XindexOfX, int &YindexOfX)
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

    // updates location of swapped number to where the X was
    positions[YindexOfX][XindexOfX] = positions[YindexOfX + ychange][XindexOfX + xchange];

    // updates location of the X to where swapped number was
    positions[YindexOfX + ychange][XindexOfX + xchange] = 'X';

    // updates values for location of X
    XindexOfX = XindexOfX + xchange;
    YindexOfX = YindexOfX + ychange;
}

// performs 'moves' random moves
void State::shufflePuzzle (char positions[3][3], int &XindexOfX, int &YindexOfX, int moves)
{  
    for (int i = 0; i < moves; i++)
    {
        findPotentialMoves(XindexOfX, YindexOfX, potentialMoves);

        // chooses a random direction from the potentialMoves vector
        int rng = rand() % size(potentialMoves);
        char choice = potentialMoves[rng];

        // moves in that direction
        move(choice, positions, XindexOfX, YindexOfX);
    }
}

// prints the location of all numbers and the X in a (3x3) grid
void State::printPuzzle(char positions[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        cout << positions[i][0] << " " << positions[i][1] << " " << positions[i][2] << endl;
    }
    cout << endl;
}

// returns number of incorect values
int State::HammingDist(char positions[3][3])
{
    int heuristic = 0;

    // for each index...
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // increments heuristic if value is not what it should be (unless it is X)
            if (positions[i][j] != '1' + j + 3 * i && positions[i][j] != 'X')
            {
                heuristic += 1;
            }
        }
    }
    return heuristic;
}

// returns sum of all distances from correct value
int State::ManhattanDist(char positions[3][3])
{
    int heuristic = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (positions[i][j] != 'X')
            {
                int x = (positions[i][j] - '0' - 1) % 3;
                int y = (positions[i][j] - '0' - 1) / 3;

                heuristic = heuristic + abs(x - j) + abs(y - i);
            }
        }
    }

    return heuristic;
}

// determines if puzzle is solved
bool State::isSolved(char positions[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // returns false if any value is not what it should be (unless it is X)
            if(positions[i][j] != '1' + j + 3 * i && positions[i][j] != 'X')
            {
                return false;
            }
        }
    }  
    return true;
}

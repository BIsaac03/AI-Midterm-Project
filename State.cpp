#include "State.h"

// updates potentialMoves vector to reflect all current legal moves
void State::findPotentialMoves()
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
void State::move(char type)
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
    findPotentialMoves();
}

// performs 'moves' random moves
void State::shufflePuzzle(int moves)
{  
    for (int i = 0; i < moves; i++)
    {
        // chooses a random direction from the potentialMoves vector
        int rng = rand() % size(potentialMoves);
        char choice = potentialMoves[rng];

        // moves in that direction
        move(choice);
    }
}

// prints the location of all numbers in a (4x4) grid
void State::printPuzzle()
{
    for (int i = 0; i < 4; i++)
    {
        cout << left << setw(4) << positions[i][0] << setw(4) << positions[i][1] << setw(4) << positions[i][2] << positions[i][3] << endl;
    }
    cout << endl;
}

// returns number of incorect values
int State::HammingDist()
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
int State::ManhattanDist()
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

// returns boolean value of whether the puzzle is solved
bool State::isSolved()
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

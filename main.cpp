#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>

using namespace std;

class State
{
    private:
    
        char choose (int XindexOfX, int YindexOfX);
        void move(char type, char positions[3][3], int &XindexOfX, int &YindexOfX);

    public:

        char positions[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', 'X'}};
        int XindexOfX = 2;
        int YindexOfX = 2;

        void shufflePuzzle (char positions[3][3], int &XindexOfX, int &YindexOfX, int moves);
        void printPuzzle(char positions[3][3]);
        int HammingDist(char positions[3][3]);
        int ManhattanDist(char positions[3][3]);
};

int main()
{
    srand(time(NULL));

    State initial;
    State shuffled;

    cout << endl;

    initial.printPuzzle(initial.positions);

    cout << "Ham before shuffle: " << initial.HammingDist(initial.positions) << endl;
    cout << "Man before shuffle: " << initial.ManhattanDist(initial.positions) << endl << endl;

    shuffled.shufflePuzzle(shuffled.positions, shuffled.XindexOfX, shuffled.YindexOfX, 1000);
    shuffled.printPuzzle(shuffled.positions); 

    cout << "Ham after shuffle: " << shuffled.HammingDist(shuffled.positions) << endl;
    cout << "Man after shuffle: " << shuffled.ManhattanDist(shuffled.positions) << endl << endl;

    return 0;
}

// chooses a random, valid direction to move
char State::choose (int XindexOfX, int YindexOfX)
{
    if (YindexOfX == 0)
    {
        if (XindexOfX == 0)
        {
            // returns a random direction (down or right)
            int choice = rand()%2;
            if (choice == 0) return 'D';
            else if (choice == 1) return 'R';
        }

        else if (XindexOfX == 1)
        {
            // returns a random direction (down, left, or right)
            int choice = rand()%3;
            if (choice == 0) return 'D';
            else if (choice == 1) return 'L';
            else if (choice == 2) return 'R';
        }

        else if (XindexOfX == 2)
        {
            // returns a random direction (down or left)
            int choice = rand()%2;
            if (choice == 0) return 'D';
            else if (choice == 1) return 'L';
        }
    }

    else if (YindexOfX == 1)
    {
        if (XindexOfX == 0)
        {
            // returns a random direction (up, down, or right)
            int choice = rand()%3;
            if (choice == 0) return 'U';
            else if (choice == 1) return 'D';
            else if (choice == 2) return 'R';
        }

        else if (XindexOfX == 1)
        {
            // returns a random direction (up, down, left, or right)
            int choice = rand()%4;
            if (choice == 0) return 'U';
            else if (choice == 1) return 'D';
            else if (choice == 2) return 'L';
            else if (choice == 3) return 'R';
        }

        else if (XindexOfX == 2)
        {
            // returns a random direction (up, down, or left)
            int choice = rand()%3;
            if (choice == 0) return 'U';
            else if (choice == 1) return 'D';
            else if (choice == 2) return 'L';
        }
    }

    else if (YindexOfX == 2)
    {
        if (XindexOfX == 0)
        {
            // returns a random direction (up or right)
            int choice = rand()%2;
            if (choice == 0) return 'U';
            else if (choice == 1) return 'R';
        }

        else if (XindexOfX == 1)
        {
            // returns a random direction (up, left, or right)
            int choice = rand()%3;
            if (choice == 0) return 'U';
            else if (choice == 1) return 'L';
            else if (choice == 2) return 'R';
        }

        else if (XindexOfX == 2)
        {
            // returns a random direction (up or left)
            int choice = rand()%2;
            if (choice == 0) return 'U';
            else if (choice == 1) return 'L';
        }
    }
    
    return -1;                                                                         // should not return this
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
        move(choose(XindexOfX, YindexOfX), positions, XindexOfX, YindexOfX);
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

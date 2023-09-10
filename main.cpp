#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <algorithm>

using namespace std;

void shufflePuzzle (char positions[], int &indexOfX, int moves);
char choose (int indexOfX);
void printPuzzle(char positions[]);
void move(char type, char positions[], int &indexOfX);
int HammingDist(char positions[]);

int main()
{
    srand(time(NULL));
    char positions[] = {'1', '2', '3', '4', '5', '6', '7', '8', 'X'};
    int indexOfX = 8;
    int moves = 0;

    cout << "Before shuffle: " << HammingDist(positions) << endl;

    shufflePuzzle(positions, indexOfX, 1000);
    printPuzzle(positions);

    cout << "After shuffle: " << HammingDist(positions) << endl;

/*
    cout << "Finding shortest solution..." << endl;

    cout << "Solution found in " << moves << " moves" << endl;


    usleep(500000);

    printPuzzle()

*/
    return 0;
}

// performs 'moves' random moves
void shufflePuzzle (char positions[], int &indexOfX, int moves)
{  
    for (int i = 0; i < moves; i++)
    {
        move(choose(indexOfX), positions, indexOfX);
    }
}

// chooses a random, valid direction to move
char choose (int indexOfX)
{
    if (indexOfX == 0)
    {
        // returns a random direction (down or right)
        int choice = rand()%2;
        if (choice == 0) return 'D';
        else if (choice == 1) return 'R';
    }

    else if (indexOfX == 1)
    {
        // returns a random direction (down, left, or right)
        int choice = rand()%3;
        if (choice == 0) return 'D';
        else if (choice == 1) return 'L';
        else if (choice == 2) return 'R';
    }

    else if (indexOfX == 2)
    {
        // returns a random direction (down or left)
        int choice = rand()%2;
        if (choice == 0) return 'D';
        else if (choice == 1) return 'L';
    }

    else if (indexOfX == 3)
    {
        // returns a random direction (up, down, or right)
        int choice = rand()%3;
        if (choice == 0) return 'U';
        else if (choice == 1) return 'D';
        else if (choice == 2) return 'R';
    }

    else if (indexOfX == 4)
    {
        // returns a random direction (up, down, left, or right)
        int choice = rand()%4;
        if (choice == 0) return 'U';
        else if (choice == 1) return 'D';
        else if (choice == 2) return 'L';
        else if (choice == 3) return 'R';
    }

    else if (indexOfX == 5)
    {
        // returns a random direction (up, down, or left)
        int choice = rand()%3;
        if (choice == 0) return 'U';
        else if (choice == 1) return 'D';
        else if (choice == 2) return 'L';
    }

    else if (indexOfX == 6)
    {
        // returns a random direction (up or right)
        int choice = rand()%2;
        if (choice == 0) return 'U';
        else if (choice == 1) return 'R';
    }

    else if (indexOfX == 7)
    {
        // returns a random direction (up, left, or right)
        int choice = rand()%3;
        if (choice == 0) return 'U';
        else if (choice == 1) return 'L';
        else if (choice == 2) return 'R';
    }

    else if (indexOfX == 8)
    {
        // returns a random direction (up or left)
        int choice = rand()%2;
        if (choice == 0) return 'U';
        else if (choice == 1) return 'L';
    }
    return -1;                                                                  // should not return this
}

// prints the location of all numbers and the X in a (3x3) grid
void printPuzzle(char positions[])
{
    cout << positions[0] << " " << positions[1] << " " << positions[2] << "\n"
    << positions[3] << " " << positions[4] << " " << positions[5] << "\n"
    << positions[6] << " " << positions[7] << " " << positions[8] << "\n" << endl;
}

// swaps the X with an adjacent number
void move(char type, char positions[], int &indexOfX)
{
    int change;
    int *pChange = &change;

    switch (type)
    {
        case 'U': *pChange = -3;
        break;

        case 'D': *pChange = 3;
        break;

        case 'L': *pChange = -1;
        break;

        case 'R': *pChange = 1;
    }

    // updates location of swapped number to where the X was
    positions[indexOfX] = positions[indexOfX + change];

    // updates location of the X to where swapped number was
    positions[indexOfX + change] = 'X';

    // updates indexOfX
    indexOfX = indexOfX + change;
}

int HammingDist(char positions[])
{
    int heuristic = 0;

    for (int i = 0; i < sizeof(&positions); i++)
    {
        if (positions[i] != '1' + i)
        {
            heuristic += 1;
        }
    }
    return heuristic;
}
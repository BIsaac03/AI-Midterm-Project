#include <iostream>
#include <string>
#include <time.h>

using namespace std;

void shufflePuzzle (char positions[], int moves);
void printPuzzle(char positions[]);
void move(char type, char positions[], int &indexOfX);

/*
void moveLeft(char positions[], int &indexOfX);
void moveRight(char positions[], int &indexOfX);
void moveUp(char positions[], int &indexOfX);
void moveDown(char positions[], int &indexOfX);
*/

int main()
{
    char positions[] = {'1', '2', '3', '4', '5', '6', '7', '8', 'X'};

    int indexOfX = 8;

//  shufflePuzzle(positions , 1000);

    printPuzzle(positions);
    move('L', positions, indexOfX);
    printPuzzle(positions);
    move('U', positions, indexOfX);
    printPuzzle(positions);
    move('R', positions, indexOfX);
    printPuzzle(positions);
    move('D', positions, indexOfX);
    printPuzzle(positions);


/*
    printPuzzle(positions);
    moveLeft(positions, indexOfX);
    printPuzzle(positions);
    moveUp(positions, indexOfX);
    printPuzzle(positions);
    moveRight(positions, indexOfX);
    printPuzzle(positions);
    moveDown(positions, indexOfX);
    printPuzzle(positions);
*/


    return 0;
}

void shufflePuzzle (char positions[], int moves)
{
    for (int i = 0; i < moves; i++)
    {
        // random number from 0-3

        // move based on random number
    }
}

// prints the location of all numbers and the X in a (3x3) grid
void printPuzzle(char positions[])
{
    cout << positions[0] << " " << positions[1] << " " << positions[2] << "\n"
    << positions[3] << " " << positions[4] << " " << positions[5] << "\n"
    << positions[6] << " " << positions[7] << " " << positions[8] << "\n" << endl;
}

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

    // updates value for location of the X
    indexOfX = indexOfX + change;

    cout << "X: " << indexOfX << endl;

}

/*

// swaps the X with the number on its left
void moveLeft(char positions[], int &indexOfX)
{
    positions[indexOfX] = positions[indexOfX - 1];
    positions[indexOfX - 1] = 'X';
    // updates location of the X
    indexOfX = indexOfX - 1;
    cout << "X: " << indexOfX << endl;
}

// swaps the X with the number on its right
void moveRight(char positions[], int &indexOfX)
{
    positions[indexOfX] = positions[indexOfX + 1];
    positions[indexOfX + 1] = 'X';
    // updates location of the X
    indexOfX = indexOfX + 1;
    cout << "X: " << indexOfX << endl;
}

// swaps the X with the number above it
void moveUp(char positions[], int &indexOfX)
{
    positions[indexOfX] = positions[indexOfX - 3];
    positions[indexOfX - 3] = 'X';
    // updates location of the X
    indexOfX = indexOfX - 3;
    cout << "X: " << indexOfX << endl;
}

// swaps the X with the number below it
void moveDown(char positions[], int &indexOfX)
{
    positions[indexOfX] = positions[indexOfX + 3];
    positions[indexOfX + 3] = 'X';
    // updates location of the X
    indexOfX = indexOfX + 3;
    cout << "X: " << indexOfX << endl;
}

*/

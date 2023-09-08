#include <iostream>
#include <string>

using namespace std;

void printPuzzle(char positions[]);
void moveLeft(char positions[], int &indexOfX);

int main()
{
    char positions[] = {'1', '2', '3', '4', '5', '6', '7', '8', 'X'};

    int indexOfX = 8;

    cout << "X: " << indexOfX << endl;

    printPuzzle(positions);
    moveLeft(positions, indexOfX);
    printPuzzle(positions);
    moveLeft(positions, indexOfX);
    printPuzzle(positions);
    moveLeft(positions, indexOfX);
    printPuzzle(positions);

    return 0;
}


void printPuzzle(char positions[])
{
    cout << positions[0] << " " << positions[1] << " " << positions[2] << "\n"
    << positions[3] << " " << positions[4] << " " << positions[5] << "\n"
    << positions[6] << " " << positions[7] << " " << positions[8] << "\n" << endl;
}

void moveLeft(char positions[], int &indexOfX)
{
    cout << "X: " << indexOfX << endl;
    char tmp = positions[indexOfX - 1];
    positions[indexOfX - 1] = 'X';
    positions[indexOfX] = tmp;
    indexOfX = indexOfX - 1;
}
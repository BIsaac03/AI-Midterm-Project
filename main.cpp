#include "State.h"

#include <time.h>
#include <stack>
//#include <algorithm>


class Node
{
    public:

        State puzzle;
        int movesFromStart;
        Node *parent;
    
        Node(State puzzle): puzzle(puzzle), movesFromStart(0), parent(NULL) {}
};

vector<Node> childNodes(Node parent, vector<Node> &potentialMoves);
int Search(Node parent, int heuristic, vector<Node> &solution);
int IDAstar(State puzzle, vector<Node> &solution);

int main()
{
    srand(time(NULL));
    vector<Node> solution = {};

    State initial;
    State shuffled;

    cout << endl;

    shuffled.move('L');
    shuffled.move('L');
//    shuffled.move('L');
    //shuffled.shufflePuzzle(5);
    shuffled.printPuzzle(); 

    cout << "Searching for shortest path..." << endl << endl;

    int fewestMoves = IDAstar(shuffled, solution);

   cout << "Solution found in " << fewestMoves << " moves." << endl << endl;  

    // outputs the next state in the solution every 0.5 seconds
    for (int i = 0; i < size(solution); i++)
    {
        solution[i].puzzle.printPuzzle();
        usleep(500000);
    }

    return 0;
}

// uses IDA* search algorithm to find shortest path
int IDAstar(State puzzle, vector<Node> &solution)
{
    int heuristic = puzzle.ManhattanDist();

    Node initial = Node(puzzle);

    while (1)
    {
        int tmp = Search(initial, heuristic, solution);

        if (tmp = 1)
        {
            return solution[0].movesFromStart;
        }

        heuristic = tmp;
    }

/*
    for (int i = 0; i < 10; i++)
    {
        vector<Node> children = childNodes(parent);

        Node child = children[rand() % size(children)];

        child.puzzle.printPuzzle();
        
        parent = child;
    }

    parent.puzzle.printPuzzle();

    parent = *parent.parent;

    parent.puzzle.printPuzzle();
*/
    return 0;
}

// updates vector with all adjacent nodes
vector<Node> childNodes(Node parent)
{
    vector<Node> potentialMoves = {};
    parent.puzzle.findPotentialMoves();
    State beforeMoves = parent.puzzle;

    for (int i = 0; i < size(parent.puzzle.potentialMoves); i++)
    {
        parent.puzzle.move(parent.puzzle.potentialMoves[i]);
        Node child = Node(parent.puzzle);
        child.parent = &parent;
        child.movesFromStart++;
        potentialMoves.push_back(child);
        parent.puzzle = beforeMoves;
    }

    return potentialMoves;
}

// searches for solution
int Search(Node parent, int heuristic, vector<Node> &solution)
{
    int f = parent.movesFromStart + parent.puzzle.ManhattanDist();

    if (f > heuristic)
    {
        return f;
    }

    if (parent.puzzle.isSolved())
    {
        cout << "Solved!" << endl;
        solution.insert(solution.begin(), parent);
        return 1;
    }

    int min = 9999999;

    vector<Node> potentialMoves = childNodes(parent);

    for (int i = 0; i < size(potentialMoves); i++)
    {
        int tmp = Search(potentialMoves[i], heuristic + 1, solution);

        if (tmp == 1)
        {
            return tmp;
        }

        if (tmp < min)
        {
            min = tmp;
        }
    }

    return min;
}
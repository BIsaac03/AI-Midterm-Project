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
    
        Node(State initial): puzzle(initial), movesFromStart(0), parent(nullptr) {}
};

vector<Node> childNodes(Node parent);
int Search(int heuristic, stack<Node> &path);
stack<Node> IDAstar(State puzzle);
void printPath(stack<Node> path);

int main()
{
    srand(time(NULL));

    State shuffled;

    cout << endl;

    shuffled.shufflePuzzle(25);
    shuffled.printPuzzle(); 

    cout << "heuristic of: " << shuffled.ManhattanDist() << endl;

    cout << "Searching for shortest path..." << endl << endl;

    stack<Node> path = IDAstar(shuffled);

    cout << "Solution found in " << size(path) - 1 << " moves." << endl << endl;  

    printPath(path);

    return 0;
}

// uses IDA* search algorithm to find shortest path
stack<Node> IDAstar(State puzzle)
{
    stack<Node> path = {};

    int heuristic = puzzle.ManhattanDist();

    Node initial = Node(puzzle);

    path.push(initial);

    while (1)
    {
        int tmp = Search(heuristic, path);

        if (tmp = 1)
        {
            return path;
        }

        heuristic = tmp;
    }
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
        Node child = parent;
        child.parent = &parent;
        child.movesFromStart++;
        potentialMoves.push_back(child);
        parent.puzzle = beforeMoves;
    }

    return potentialMoves;
}

// searches for solution
int Search(int heuristic, stack<Node> &path)
{
    Node parent = path.top();

    int f = parent.movesFromStart + parent.puzzle.ManhattanDist();

    if (f > heuristic)
    {
        return f;
    }

    if (parent.puzzle.isSolved())
    {
        cout << "Solved!" << endl;
        //path.push(parent);
        return 1;
    }

    int min = 9999999;

    vector<Node> potentialMoves = childNodes(parent);

    for (int i = 0; i < size(potentialMoves); i++)
    {
        for (int i = 0; i < size(potentialMoves); i++)
        {
            cout << "C" << i + 1 << " dfs: " << potentialMoves[i].movesFromStart << " f: " << potentialMoves[i].puzzle.ManhattanDist() << endl;
        }

        path.push(potentialMoves[i]);

        int tmp = Search(heuristic, path);

        if (tmp == 1)
        {
            return tmp;
        }

        if (tmp < min)
        {
            min = tmp;
        }

        path.pop();
    }

    return min;
}

// prints the states in the path in reverse order (i.e. from unsolved to solved)
void printPath(stack<Node> path)
{
    if (path.empty())
    {
        return;
    }

    Node State = path.top();

    path.pop();

    printPath(path);

    usleep(1000000);

    State.puzzle.printPuzzle();
}

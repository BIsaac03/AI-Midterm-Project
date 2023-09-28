#include "State.h"

#include <time.h>
#include <stack>

class Node
{
    public:

        State puzzle;
        int movesFromStart;
        Node *parent;
    
        Node(State initial): puzzle(initial), movesFromStart(0), parent(nullptr) {}
};

vector<Node> childNodes(Node parent);
int Search(int threshold, stack<Node> &path, int heuristic);
stack<Node> IDAstar(State puzzle, int heuristic);
void printPath(stack<Node> path);

int main()
{
    srand(time(NULL));

    State shuffled;

    cout << endl;

    shuffled.shufflePuzzle(500);

    shuffled.printPuzzle(); 

    cout << "With Manhattan heuristic of: " << shuffled.ManhattanDist() << endl;

    cout << "Searching for shortest path..." << endl << endl;

    // pass 0 for Hamming distance heuristic, 1 for Manhattan distance heuristic
    stack<Node> path = IDAstar(shuffled, 1);

    Node goal = path.top();

    cout << "Solution found in " << goal.movesFromStart << " moves." << endl << endl;  

    printPath(path);

/*
    cout << endl << endl << endl;

    cout << "With Hamming- heuristic of: " << shuffled.HammingDist() << endl;

    cout << "Searching for shortest path..." << endl << endl;

    // pass 0 for Hamming distance heuristic, 1 for Manhattan distance heuristic
    path = IDAstar(shuffled, 0);

    cout << "Solution found in " << size(path) - 1 << " moves." << endl << endl;  

    printPath(path);
*/
    return 0;
}

// uses IDA* search algorithm to find shortest path
stack<Node> IDAstar(State puzzle, int heuristic)
{
    stack<Node> path = {};

    int threshold = puzzle.ManhattanDist();

    Node initial = Node(puzzle);

    path.push(initial);

    while (1)
    {
        int tmp = Search(threshold, path, heuristic);

        if (tmp == 1)
        {
            return path;
        }

        threshold = tmp;
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
int Search(int threshold, stack<Node> &path, int heuristic)
{
    Node parent = path.top();

    int minMovestoGoal;
    int *pminMovestoGoal = &minMovestoGoal;

    if (heuristic == 0)
    {
        *pminMovestoGoal = parent.puzzle.HammingDist();
    }

    else if (heuristic == 1)
    {
        *pminMovestoGoal = parent.puzzle.ManhattanDist();
    }
    
    int f = parent.movesFromStart + minMovestoGoal;

    if (f > threshold)
    {
        return f;
    }

    if (parent.puzzle.isSolved())
    {
        cout << "Solved!" << endl;

        return 1;
    }

    int min = 9999999;

    vector<Node> potentialMoves = childNodes(parent);

    for (int i = 0; i < size(potentialMoves); i++)
    {
//        cout << "C" << i + 1 << " dfs: " << potentialMoves[i].movesFromStart << " f: " << potentialMoves[i].puzzle.ManhattanDist() << endl;

        path.push(potentialMoves[i]);

        int tmp = Search(threshold, path, heuristic);

        if (tmp == 1)
        {
            return 1;
        }

        if (tmp < min)
        {
            min = tmp;
//            cout << "min is now: " <<  min << endl;
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

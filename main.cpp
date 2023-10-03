#include "State.h"

#include <time.h>
#include <chrono>
#include <stack>

class Node
{
    public:

        State puzzle;
        int movesFromStart;
    
        Node(State initial): puzzle(initial), movesFromStart(0) {}
};

vector<Node> childNodes(Node parent);
int Search(int threshold, stack<Node> &path, int heuristic);
stack<Node> IDAstar(State puzzle, int heuristic);
void printPath(stack<Node> path);

int main()
{
    srand(time(NULL));

    State shuffled;

    // creates a shuffled state
    int randomMoves;
    cout << "How many random moves should be used to shuffle the 15 puzzle?" << endl;
    cout << "(Runtime increase exponentially as puzzle becomes more complex)" << endl;
    cin >> randomMoves;

    cout << endl << "Shuffled puzzle: " << endl;
    shuffled.shufflePuzzle(randomMoves);
    shuffled.printPuzzle(); 

// run using Hamming heuristic
    cout << "With Hamming heuristic of: " << shuffled.HammingDist() << endl;
    cout << "Searching for shortest path..." << endl << endl;

    auto start = chrono::high_resolution_clock::now();

    // uses IDA* to find soltion in fewest moves
    // pass 0 for Hamming distance heuristic, 1 for Manhattan distance heuristic
    stack<Node> path = IDAstar(shuffled, 0);

    // calculates time to solve
    auto stop = chrono::high_resolution_clock::now();
    auto timeElapsed = chrono::duration_cast<chrono::milliseconds>(stop - start);

    // prints solution stats and States to solution
    Node goal = path.top();
    cout << "Solution found in " << goal.movesFromStart << " moves and " <<  timeElapsed.count() << " milliseconds" << endl << endl;  
    printPath(path);

    cout << endl << endl;

// redo using Manhattan heuristic
    cout << "With Manhattan heuristic of: " << shuffled.ManhattanDist() << endl;
    cout << "Searching for shortest path..." << endl << endl;

    start = chrono::high_resolution_clock::now();

    // pass 0 for Hamming distance heuristic, 1 for Manhattan distance heuristic
    path = IDAstar(shuffled, 1);

    stop = chrono::high_resolution_clock::now();
    timeElapsed = chrono::duration_cast<chrono::milliseconds>(stop - start);

    goal = path.top();

    cout << "Solution found in " << goal.movesFromStart << " moves and " <<  timeElapsed.count() << " milliseconds" << endl << endl;  
    printPath(path);

    return 0;
}

// uses IDA* search algorithm to find shortest path
stack<Node> IDAstar(State puzzle, int heuristic)
{
    stack<Node> path = {};
    int threshold;

    // sets starting threshold to heuristic estimate of distance to goal state from shuffled state
    if (heuristic == 0)
    {
        threshold = puzzle.HammingDist();
    }
    else if (heuristic == 1)
    {
        threshold = puzzle.ManhattanDist();
    }

    // adds node with starting shuffled state to path
    Node initial = Node(puzzle);
    path.push(initial);

    // until solution found...
    while (1)
    {
        int tmp = Search(threshold, path, heuristic);

        // SOLUTION FOUND!
        // returns path of all states leading to solution
        if (tmp == 1)
        {
            return path;
        }

        // updates threshold to lowest unsearched f score and informs user of this change
        threshold = tmp;
        cout << "Threshold is now: " << threshold << endl;
    }
}

// returns vector with all adjacent nodes
vector<Node> childNodes(Node parent)
{
    vector<Node> potentialMoves = {};
    parent.puzzle.findPotentialMoves();

    // for each possible move...
    for (int i = 0; i < size(parent.puzzle.potentialMoves); i++)
    {
        Node child = parent;

        // moves that direction
        child.puzzle.move(parent.puzzle.potentialMoves[i]);

        // increments distance from start
        child.movesFromStart++;

        // adds to vector of adjacent nodes
        potentialMoves.push_back(child);
    }

    return potentialMoves;
}

// searches for solution
int Search(int threshold, stack<Node> &path, int heuristic)
{
    int minMovestoGoal;

    // current node being analyzed is topmost node in path 
    Node parent = path.top();

    // uses heuristic function to find estimated distance from goal state
    if (heuristic == 0)
    {
        minMovestoGoal = parent.puzzle.HammingDist();
    }
    else if (heuristic == 1)
    {
        minMovestoGoal = parent.puzzle.ManhattanDist();
    }
    
    // sets f score of node to distance from start + distance to goal
    int f = parent.movesFromStart + minMovestoGoal;

    // f score exceeds current threshold; will not continue
    if (f > threshold)
    {
        return f;
    }

    // checks if puzzle is solved
    // can also use parent.puzzle.isSolved()
    if (minMovestoGoal == 0)
    {
        cout << "Solved!" << endl;

        return 1;
    }

    int min = INT_MAX;

    // gets vector of all adjacent nodes
    vector<Node> potentialMoves = childNodes(parent);

    // for each adjacent node...
    for (int i = 0; i < size(potentialMoves); i++)
    {
        // adds it to the path
        path.push(potentialMoves[i]);

        // recursively calls Search 
        int tmp = Search(threshold, path, heuristic);

        // SOLUTION FOUND!!
        if (tmp == 1)
        {
            return 1;
        }

        // updates min to lowest f score that exceeds current threshold
        if (tmp < min)
        {
            min = tmp;
        }

        // did not lead to solution; removes it from path
        path.pop();
    }

    return min;
}

// prints the states in the path in reverse order (i.e. from unsolved to solved)
void printPath(stack<Node> path)
{
    // all states have been printed
    if (path.empty())
    {
        return;
    }

    // stores and removes top state from stack
    Node State = path.top();
    path.pop();

    // recursively calls printPath
    printPath(path);

    // prints the next move every half second
    State.puzzle.printPuzzle();
    usleep(500000);
}

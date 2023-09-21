#include "State.h"

#include <time.h>
#include <algorithm>

class Node
{
    public:

        State puzzle;
        int movesFromStart;
        Node *parent;
    
        Node(State puzzle): puzzle(puzzle), movesFromStart(0), parent(NULL) {}
};

int IDAstar(State puzzle, vector<State> &solution);

int main()
{
    srand(time(NULL));
    vector<State> solution = {};

    State initial;
    State shuffled;

    cout << endl;

    shuffled.shufflePuzzle(1000);
    shuffled.printPuzzle(); 

    cout << "Searching for shortest path..." << endl << endl;

    int fewestMoves = IDAstar(shuffled, solution);

    cout << "Solution found in " << fewestMoves << " moves." << endl << endl;

    // outputs the next state in the solution every 0.5 seconds
    for (int i = 0; i < size(solution); i++)
    {
        solution[i].printPuzzle();
        usleep(500000);
    }

    return 0;
}

// uses IDA* search algorithm to find shortest path
int IDAstar(State puzzle, vector<State> &solution)
{
    solution.insert(solution.begin(), puzzle);

    int heuristic = puzzle.ManhattanDist();

//    Node *initial = new Node(puzzle, 0, NULL);

    Node parent = Node(puzzle);
    vector<Node> potentialMoves = {};

    puzzle.findPotentialMoves();
    State beforeMoves = puzzle;

    for (int i = 0; i < size(puzzle.potentialMoves); i++)
    {
        puzzle.move(puzzle.potentialMoves[i]);
        Node child = Node(puzzle);
        child.parent = &parent;
        child.movesFromStart++;
        child.puzzle.printPuzzle();
        cout << "Value: " << child.puzzle.ManhattanDist() << endl << endl;
        potentialMoves.push_back(child);
        puzzle = beforeMoves;
    }
    
    return 0;
}

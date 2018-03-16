#include <iostream>
#include <string.h>
#include "ioinfo.h"
#include "solver.h"
using namespace std;

int defaultpuzzle[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 8, 0},
        {7, 6, 5}
};
int main() {
    int puzzlesize = SIZE * SIZE -1;
    printhead(puzzlesize);

    //get initpuzzle
    int choice;
    cin>>choice;
    bool repeat = true;
    int initpuzzle[SIZE][SIZE];
    while(repeat){
        if(choice == 2){
            getinitpuzzle(initpuzzle);
            repeat = false;
        }
        else if(choice == 1){
            repeat = false;
            memcpy (initpuzzle, defaultpuzzle, sizeof(initpuzzle));
        }else{
            cout<<"please input 1 or 2\n";
            cin>>choice;
        }
    }

    puzzle initNode(initpuzzle);
    //cout<<"initNode:\n";
    //initNode.printBoard();

    solver eSolver;
    //pick the huristic function
    askForHFunction();
    repeat = true;
    cin>>choice;
    /*1. Uniform Cost Search
      2. A* with the Misplaced Tile heuristic.
      3. A* with the Manhattan distance heuristic.*/

    //int dis = 0;
    while(repeat){
        if(choice == 1){
            eSolver.hFunc = cost;
            repeat = false;
        }
        else if(choice == 2){
            repeat = false;
            eSolver.hFunc = misplaced;
        }
        else if(choice ==3){
            repeat = false;
            eSolver.hFunc = manhattan;
        }
        else{
            cout<<"please input 1, 2 or 3\n";
            cin>>choice;
        }
    }
    //init solver:
    eSolver.setinit(initNode);
    eSolver.printInitNode();
    eSolver.printGoalNode();
    //begin the search
    eSolver.search();

    return 0;
}
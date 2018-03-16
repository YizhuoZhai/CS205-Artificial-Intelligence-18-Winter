//
// Created by 翟翼卓 on 2/12/18.
//

#ifndef PUZZLESOLVER_SOLVER_H
#define PUZZLESOLVER_SOLVER_H

#include "puzzle.h"
#include <queue>
#include <set>
enum OP{UP, DOWN, LEFT, RIGHT};
class solver{
    unsigned long long nodesnum;
    unsigned long long queuesize;
public:
    puzzle init;
    puzzle goal;

    priority_queue<puzzle> pq;
    set<puzzle> visited;
    int (*hFunc)(int a[SIZE][SIZE], int b[SIZE][SIZE]);
    void setinit(puzzle);
    solver(){
        int num = 1;
        for(int i = 0; i< SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                //goal.setBoard(i, j, num++);
                goal.board[i][j] = num++;
            }
        }
        goal.setBoard(SIZE - 1, SIZE - 1, 0);
    }
    void printInitNode();
    void printGoalNode();

    void search();
    bool isGoal(puzzle a);

    void expandNode(puzzle, priority_queue <puzzle>&, int op);

};



#endif //PUZZLESOLVER_SOLVER_H

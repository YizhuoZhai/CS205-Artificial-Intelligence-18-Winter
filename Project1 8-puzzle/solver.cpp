//
// Created by 翟翼卓 on 2/12/18.
//
#include "solver.h"
#include <string.h>
#include <iostream>
#define DBG1
#undef DBG1
#define EXPAND
#undef EXPAND
using namespace std;
void findGoal(puzzle currentNode, int nodesnum, int queuesize){
    cout<<"Goal!\n";
    cout<<"To solve this problem the search algorithm expanded a total of "<<nodesnum<<" nodes.\n";
    cout<<"The maximum number of nodes in the queue at any one time was "<<queuesize<<".\n";
    cout<<"The depth of the goal node was "<<currentNode.getdepth()<<endl;
}
bool isEqual(int a[SIZE][SIZE], int b[SIZE][SIZE]){
    for(int i =0; i<SIZE; i++){
        for(int j = 0; j< SIZE; j++){
            if(a[i][j] != b[i][j]){
                return false;
            }
        }
    }
    return true;
}
void solver::setinit(puzzle p){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            init.board[i][j] = p.board[i][j];
        }
    }
    init.setdepth(0);
    init.setg(0);
    init.seth(hFunc(init.board, goal.board));

}
void solver::printInitNode(){
    cout<<"init solver node:\n";
    init.printBoard();
}
void solver::printGoalNode() {
    cout<<"Goal node in solver:\n";
    goal.printBoard();
}

void solver::search() {
    nodesnum = 0;
    pq.push(init);
    queuesize = pq.size();
    if(isGoal(init)){
        cout<<"Goal!\n";
        cout<<"To solve this problem the search algorithm expanded a total of "<<nodesnum<<" nodes.\n";
        cout<<"The maximum number of nodes in the queue at any one time was "<<queuesize<<".\n";
        cout<<"The depth of the goal node was "<<init.getdepth()<<endl;
        return;
    }
    while(1){
        if(pq.empty()){
            cout<<"Failure\n";
            return;
        }
        puzzle currentNode = pq.top();
        visited.insert(currentNode);
        pq.pop();
#ifdef EXPAND
        cout<<"The best state to expand with a g(n) = "<<currentNode.getg();
        cout<<" and h(n) = "<<currentNode.geth()<<" is...\n";
        currentNode.printBoard();
        cout<<"Expanding this node ...\n";

        //puzzle topNode;
#endif
        int x;
        int y;
        puzzle nextNode;
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(currentNode.board[i][j] == 0){
                    x = i;
                    y = j;
                    break;
                }
            }
        }

        if(x != 0){

            bool c = false;
            memcpy(nextNode.board, currentNode.board, sizeof(currentNode.board));

            nextNode.setBoard(x, y, currentNode.board[x-1][y]);
            nextNode.setBoard(x-1, y, 0);
            nextNode.setg(currentNode.getg()+1);
            nextNode.seth(hFunc(nextNode.board, goal.board));
            nextNode.setdepth(currentNode.getdepth() + 1);
            for(auto item:visited){
                if(isEqual(item.board, nextNode.board)){
                    c = true;
                }
            }
            if(!c){
                if(isGoal(nextNode)){
                    findGoal(nextNode,nodesnum,queuesize);
                    return;
                }
                pq.push(nextNode);
                nodesnum++;
#ifdef DBG1
                cout<<"next Node for UP"<<endl;
                nextNode.printBoard();
                cout<<"depth = "<<nextNode.getdepth()<<"\n";

#endif
            }
        }

        if(x != SIZE - 1){
            bool c = false;
            memcpy(nextNode.board, currentNode.board, sizeof(currentNode.board));

            nextNode.setBoard(x, y, currentNode.board[x+1][y]);
            nextNode.setBoard(x+1, y, 0);
            nextNode.setg(currentNode.getg()+1);
            nextNode.seth(hFunc(nextNode.board, goal.board));
            nextNode.setdepth(currentNode.getdepth() + 1);
            for(auto item:visited){
                if(isEqual(item.board, nextNode.board)){
                    c = true;
                }
            }
            if(!c){
                if(isGoal(nextNode)){
                    findGoal(nextNode,nodesnum,queuesize);
                    return;
                }
                pq.push(nextNode);
                nodesnum++;

#ifdef DBG1
                cout<<"next Node for DOWN"<<endl;
                nextNode.printBoard();
                cout<<"depth = "<<nextNode.getdepth()<<"\n";
#endif
            }
        }

        if(y != 0){
            bool c = false;
            memcpy(nextNode.board, currentNode.board, sizeof(currentNode.board));

            nextNode.setBoard(x, y, currentNode.board[x][y-1]);
            nextNode.setBoard(x, y-1, 0);
            nextNode.setg(currentNode.getg()+1);
            nextNode.seth(hFunc(nextNode.board, goal.board));
            nextNode.setdepth(currentNode.getdepth() + 1);
            for(auto item:visited){
                if(isEqual(item.board, nextNode.board)){
                    c = true;
                }
            }
            if(!c){
                if(isGoal(nextNode)){
                    findGoal(nextNode,nodesnum,queuesize);
                    return;
                }
                pq.push(nextNode);
                nodesnum++;
#ifdef DBG1
                cout<<"next Node for left"<<endl;
                nextNode.printBoard();
                cout<<"depth = "<<nextNode.getdepth()<<"\n";

#endif
            }
        }

        if(y != SIZE - 1){
            bool c = false;
            memcpy(nextNode.board, currentNode.board, sizeof(currentNode.board));
            nextNode.setBoard(x, y, currentNode.board[x][y+1]);
            nextNode.setBoard(x, y+1, 0);
            nextNode.setg(currentNode.getg()+1);
            nextNode.seth(hFunc(nextNode.board, goal.board));
            nextNode.setdepth(currentNode.getdepth() + 1);
            for(auto item:visited){
                if(isEqual(item.board, nextNode.board)){
                    c = true;
                }
            }
            if(!c){
                if(isGoal(nextNode)){
                    findGoal(nextNode,nodesnum,queuesize);
                    return;
                }
                pq.push(nextNode);
                nodesnum++;
#ifdef DBG1
                cout<<"next Node for right"<<endl;
                nextNode.printBoard();
                cout<<"depth = "<<nextNode.getdepth()<<"\n";
#endif
            }
        }
        queuesize = pq.size()>queuesize? pq.size():queuesize;
    }
}

bool solver::isGoal(puzzle a){

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(a.board[i][j] != goal.board[i][j]){
                return false;
            }
        }
    }
    return true;
}
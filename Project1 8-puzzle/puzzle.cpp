//
// Created by 翟翼卓 on 2/12/18.
//
#include "puzzle.h"
#include <cmath>
using namespace std;

puzzle::puzzle(int a[SIZE][SIZE]) {
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            board[i][j] = a[i][j];
        }
    }
}
void puzzle::setBoard(int i, int j, int num){
    board[i][j] = num;
}
/*int (*getBoard())[SIZE]{
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            a[i][j] = board[i][j];
        }
    }
}*/
void puzzle::printBoard() {
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int misplaced(int a[SIZE][SIZE], int b[SIZE][SIZE]){
    int ret = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(a[i][j] != b[i][j] && (a[i][j] != 0)){
                ret++;
            }
        }
    }
    return ret;
}
int manhattan(int a[SIZE][SIZE], int b[SIZE][SIZE]){
    int ret = 0;
    //int factor = SIZE - 1;
    int num = SIZE*SIZE -1;

    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            int count = a[i][j];

            int ii = (count - 1)/SIZE;
            int jj = (count - 1)%SIZE;
            if(count == 0){
                //ii = SIZE-1;
                //jj = SIZE-1;
                continue;
            }
            else{
                ret += (abs(ii-i)+abs(jj-j));
            }
        }
    }
    return ret;
}
int cost(int a[SIZE][SIZE], int b[SIZE][SIZE]){
    return 0;
}
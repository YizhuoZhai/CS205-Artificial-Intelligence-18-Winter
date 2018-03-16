//
// Created by 翟翼卓 on 2/12/18.
//

#ifndef PUZZLESOLVER_PUZZLE_H
#define PUZZLESOLVER_PUZZLE_H

#include <iostream>
using namespace std;

#define SIZE 3
class puzzle{
private:
    int g;
    int h;
    int depth;
public:
    int board[SIZE][SIZE];

    puzzle(){}
    puzzle(int a[SIZE][SIZE]);
    void setBoard(int, int, int);

    int (*getBoard())[SIZE]{ return board;}

    void setg(int _g){g = _g;}
    int getg() const{return g;}

    void seth(int _h){h = _h;}
    int geth() const {return h;}


    void setdepth(int _d){depth = _d;}
    int getdepth(){return depth;}

    void printBoard();

    bool operator < (const puzzle &a) const
    {
        return (h+g) > (a.geth()+a.getg());
    }

};

int misplaced(int a[SIZE][SIZE], int b[SIZE][SIZE]);
int manhattan(int a[SIZE][SIZE], int b[SIZE][SIZE]);
int cost(int a[SIZE][SIZE], int b[SIZE][SIZE]);
#endif //PUZZLESOLVER_PUZZLE_H

//
// Created by 翟翼卓 on 2/12/18.
//

#ifndef PUZZLESOLVER_IOINFO_H
#define PUZZLESOLVER_IOINFO_H

#include "puzzle.h"
using namespace std;
void printhead(int puzzlesize){
    cout<<"Welcome to Yizhuo's "<<puzzlesize<<"-puzzle solver.\n";
    cout<<"Type “1” to use a default puzzle, or “2” to enter your own puzzle.\n";
}
void askForHFunction(){
    cout<<"Enter your choice of algorithm\n"
            "1. Uniform Cost Search\n"
            "2. A* with the Misplaced Tile heuristic.\n"
            "3. A* with the Manhattan distance heuristic.";
}
void getinitpuzzle(int (&initpuzzle)[SIZE][SIZE]){
    int i,j,k;
    int num = 0;
    int row = 0;
    cout<<"Enter your puzzle, use a zero to represent the blank\n"
            "Enter the first row, use space or tabs between numbers ";
    for(int count = 0; count <SIZE; count++){
        cin>>num;
        initpuzzle[row][count] = num;
    }
    row++;
    cout<<"Enter the second row, use space or tabs between numbers ";
    for(int count = 0; count <SIZE; count++){
        cin>>num;
        initpuzzle[row][count] = num;
    }
    row++;
    cout<<"Enter the third row, use space or tabs between numbers ";
    for(int count = 0; count <SIZE; count++){
        cin>>num;
        initpuzzle[row][count] = num;
    }
}

#endif //PUZZLESOLVER_IOINFO_H

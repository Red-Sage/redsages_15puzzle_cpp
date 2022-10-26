#include <iostream>
#include "15puzzle.hpp"

int main()
{
    
    PuzzleBoard board = PuzzleBoard();
    board.print();
    cout<<board.isValidBoard()<<endl;
    board.getRandomBoard();
    cout<<board.isValidBoard()<<endl;
    board.print();

    board.moveDirection(0);
    board.print();
    board.moveDirection(0);
    board.print();
    



    return 0;
}
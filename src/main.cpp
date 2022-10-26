#include <iostream>
#include "15puzzle.hpp"

int main()
{
    
    PuzzleBoard board = PuzzleBoard();
    board.print();
    cout<<board.isValidBoard()<<endl;
    board.permutBoard();
    cout<<board.isValidBoard()<<endl;
    board.print();
    

    vector<int> test(3);

    test.push_back(1);
    test.push_back(2);
    test.push_back(3);

    int x = test.at(3);

    return 0;
}
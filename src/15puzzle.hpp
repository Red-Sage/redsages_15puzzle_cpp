#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::unique;
using std::find;

void resetBoard(vector<int>& board, int boardSize);
int find(vector<int>& board, int value);
void swapTiles(vector<int>& board, int idx1, int idx2);

void resetBoard(vector<int>& board, int boardSize)
{
    board.clear();
    
    for(int i=1; i<=boardSize; ++i)
    {
        board.push_back(i);
    }
}

int find(vector<int>& board, int value)
{
    int idx;
    auto it = find(board.begin(), board.end(), value);
    if(it != board.end())
    {
        idx = it-board.begin();
    }
    else
    {
        idx = -1;
    }

    return idx;
}

void swapTiles(vector<int>& board, int idx1, int idx2)
{
    if(idx1 != idx2)
    {
        board.at(idx1) = board.at(idx1) + board.at(idx2);
        board.at(idx2) = board.at(idx1) - board.at(idx2);
        board.at(idx1) = board.at(idx1) - board.at(idx2);
    }

}

class PuzzleBoard
{
    private:
        const int boardSize = 16;
        const int boardRows = 4;
        const int boardCols = 4;
        vector<int> _board;
    public:
        PuzzleBoard();
        void print();
        void getRandomBoard();
        void permuteBoard();
        bool isValidBoard();
        

};

PuzzleBoard::PuzzleBoard()
{
    resetBoard(_board, boardSize);
}

void PuzzleBoard::print()
{
    
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            std::cout<<_board[i*4+j]<<"  ";
        }

        std::cout<<std::endl;
    }
}

void PuzzleBoard::getRandomBoard()
{
    int count=0; //A safty to avoid infinite loop
    do
    {
        if(count > 100)
        {
            //This code should never be reached but it guards aginast infinete loop
            throw std::logic_error("Could not generate random board.");
        }
        resetBoard(_board, boardSize);
        permuteBoard();
        count++;
    }
    while(!isValidBoard());
}

void PuzzleBoard::permuteBoard()
{
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 15);

    vector<int> intList;

    for(int i=0; i<_board.size(); ++i)
    {
        intList.push_back(distribution(generator));
    }

    vector<int>::iterator it;

    int idx, tempValue, swapIdx;

    for(it = intList.begin(); it != intList.end(); ++it)
    {
        idx = it - intList.begin();
        swapIdx = *it;
        swapTiles(_board, idx, swapIdx);

        cout<<*it<<" "; // For testing only
    }

    cout<<endl;  // For testing only
}

bool PuzzleBoard::isValidBoard()
{
    //First a simple test for unique elements
    vector<int>::iterator it;
    it = unique(_board.begin(), _board.end());

    if(it != _board.end())
    {
        return false;
    }

    //Test to see if the permuteation is odd (i.e. board is invalid)
    vector<int> v = _board;
    int blankLocation = find(_board, boardSize);
    int row = blankLocation/boardRows;
    int col = blankLocation - 4*row;
    int moves = (boardRows-1)-row + (boardCols-1)-col;
    
    int idx = 0;
    int num_transpositions = 0;

    for(int i=1; i <= boardSize; ++i) //i is the tile value, i-1 is the correct location
    {
        idx = find(v, i); // Where the number actually is
        

        if(idx+1 != i)
        {
            swapTiles(v, idx, i-1);
            num_transpositions++;
        }
       
       
    }

    if(num_transpositions % 2 != moves % 2)
    {
        return false;
    } 

    return true;
}
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::unique;

void resetBoard(vector<int>& board, int boardSize);

class PuzzleBoard
{
    private:
        const int boardSize = 16;
        vector<int> _board;
    public:
        PuzzleBoard();
        void print();
        void getRandomBoard();
        void permutBoard();
        bool isValidBoard();
        

};

PuzzleBoard::PuzzleBoard()
{
    resetBoard(_board, boardSize);
}

void resetBoard(vector<int>& board, int boardSize)
{
    board.clear();
    
    for(int i=1; i<=boardSize; ++i)
    {
        board.push_back(i);
    }
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

//void PuzzleBoard::getRandomBoard()
//{

//}

void PuzzleBoard::permutBoard()
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
        tempValue = _board.at(idx);
        _board.at(idx) = _board.at(swapIdx);
        _board.at(swapIdx) = tempValue;

        cout<<*it<<" "; // For testing only
    }

    cout<<endl;  // For testing only
}

bool PuzzleBoard::isValidBoard()
{
    bool isValid = false;

    //First a simple test for unique elements
    vector<int>::iterator it;
    it = unique(_board.begin(), _board.end());

    if(it != _board.end())
    {
        return isValid;
    }
    return true;
}
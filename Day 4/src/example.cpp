#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

constexpr std::array<int, 27> input_numbers{7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1};

struct BoardNumber
{
    constexpr BoardNumber(int number_) : number(number_) {}

    const int number{0}; 
    bool hasBeenFound{false};
};

constexpr auto board_width = 5;
using Board = std::array<std::array<BoardNumber, board_width>, board_width>;
constexpr std::array<Board, 3> input_boards{
    Board {{{22,13,17,11,0}, {8,2,23,4,24}, {21,9,14,16,7}, {6,10,3,18,5}, {1,12,20,15,19}}},
    Board {{{3,15,0,2,22}, {9,18,13,17,5}, {19,8,7,25,23}, {20,11,10,24,4}, {14,21,16,12,6}}},
    Board {{{14,21,17,24,4}, {10,16,15,9,19}, {18,8,23,26,20}, {22,11,13,6,5}, {2,0,12,3,7}}}
};

static_assert(input_boards[0].size() == 5);
static_assert(input_boards[1].size() == 5);
static_assert(input_boards[2].size() == 5);

void updateBoard(Board& board, int choosenNumber)
{
    for(auto& row : board)
    {
        for(auto& boardNumber: row)
        {
            if(boardNumber.number == choosenNumber)
            {
                boardNumber.hasBeenFound = true;
            }
        }
    }
}

bool isAWinningBoard(const Board& board)
{
    for(auto i=0; i<board_width; ++i)
    {
        if(std::all_of(std::begin(board[i]), std::end(board[i]), [](const auto& boardNumber){ return boardNumber.hasBeenFound; }))
        {
            return true;
        }
        if(board[0][i].hasBeenFound and board[1][i].hasBeenFound and board[2][i].hasBeenFound and board[3][i].hasBeenFound and board[4][i].hasBeenFound)
        {
            return true;
        }
    }
    return false;
}

void firstPart()
{
    auto unmarkedNumbersSum{0}, lastNumberCalled{0};
    auto playingBoards = input_boards;

    for(size_t index{0}; index < input_numbers.size(); ++index)
    {
        lastNumberCalled = input_numbers[index];
        for(auto& board : playingBoards)
        {
            updateBoard(board, lastNumberCalled);
        }
        if(std::any_of(std::begin(playingBoards), std::end(playingBoards), [](const auto& board){ return isAWinningBoard(board); }))
        {
            break;
        }
    }

    auto winningBoardIterator = std::find_if(std::begin(playingBoards), std::end(playingBoards), [](const auto& board){ return isAWinningBoard(board); });

    for(auto& row : *winningBoardIterator)
    {
        for(auto& boardNumber: row)
        {
            if(not boardNumber.hasBeenFound)
            {
                unmarkedNumbersSum += boardNumber.number;
            }
        }
    }

    std::cout << "The solution is: " << (lastNumberCalled * unmarkedNumbersSum) << std::endl;
}

int main()
{
    firstPart();
    return 0;
}

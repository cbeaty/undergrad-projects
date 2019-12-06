#include <iostream>
#include "TicTacToeTree.h"

using namespace std;

int main()
{
	TicTacToeTree tree;

    string boardString = "-X-------";
    tree.depthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::X_WIN);
    tree.depthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::O_WIN);
    tree.depthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::DRAW);
    tree.breadthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::X_WIN);
    tree.breadthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::O_WIN);
    tree.breadthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::DRAW);

    boardString = "X---O----";
    tree.depthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::X_WIN);
    tree.depthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::O_WIN);
    tree.depthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::DRAW);
    tree.breadthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::X_WIN);
    tree.breadthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::O_WIN);
    tree.breadthFirstSearchForOutcome(boardString, TicTacToeBoard::BOARD_STATE::DRAW);

    return 0;
}
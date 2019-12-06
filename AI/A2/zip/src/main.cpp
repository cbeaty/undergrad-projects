#include <iostream>
#include "TicTacToeTree.h"

using namespace std;

int main()
{
	TicTacToeTree tree;

    cout << "This is the empty board state that shows that the depthFirstCountOutcomes works." << endl;

    string boardString = "---------";
    TicTacToeTree::WinDrawStats stats = tree.depthFirstCountOutcomes(boardString);
    TicTacToeTree::TicTacToePlay move = tree.nextMoveHeuristic(boardString);
    
    int completeGames = stats.numOWins + stats.numXWins + stats.numDraws;

    cout << "Number of X wins: " << stats.numXWins << endl;

    cout << "Number of O wins: " << stats.numOWins << endl;

    cout << "Number of draws: " << stats.numDraws << endl;

    cout << "Total complete games: " << completeGames << endl;
    
    cout << endl << endl << "This next board shows that the nextMoveHeuristic will go for the win." << endl;

    boardString = "XX-OO----";
    stats = tree.depthFirstCountOutcomes(boardString);
    move = tree.nextMoveHeuristic(boardString);
    
    completeGames = stats.numOWins + stats.numXWins + stats.numDraws;

    cout << "Number of X wins: " << stats.numXWins << endl;

    cout << "Number of O wins: " << stats.numOWins << endl;

    cout << "Number of draws: " << stats.numDraws << endl;

    cout << "Total complete games: " << completeGames << endl;

    cout << endl << endl << "This shows that the nextMoveHeuristic will block a loss." << endl;

    boardString = "X-O-X----";
    stats = tree.depthFirstCountOutcomes(boardString);
    move = tree.nextMoveHeuristic(boardString);
    
    completeGames = stats.numOWins + stats.numXWins + stats.numDraws;

    cout << "Number of X wins: " << stats.numXWins << endl;

    cout << "Number of O wins: " << stats.numOWins << endl;

    cout << "Number of draws: " << stats.numDraws << endl;

    cout << "Total complete games: " << completeGames << endl;

    cout << endl << endl << "This is game that goes for a few moves, "; 
    cout << "showing that the AI won't beat itself." << endl;

    boardString = "---XXOO--";
    move = tree.nextMoveHeuristic(boardString);
    boardString = "-X-XXOO--";
    move = tree.nextMoveHeuristic(boardString);
    boardString = "-X-XXOOO-";
    move = tree.nextMoveHeuristic(boardString);
    boardString = "-X-XXOOOX";
    move = tree.nextMoveHeuristic(boardString);
    boardString = "OX-XXOOOX";
    move = tree.nextMoveHeuristic(boardString);

    cout << endl << endl << "This is a rigged state where O is destined to lose, but puts up a fight." << endl;
    boardString = "-X---XOOX";
    move = tree.nextMoveHeuristic(boardString);
    boardString = "-XO--XOOX";
    move = tree.nextMoveHeuristic(boardString);
    boardString = "-XO-XXOOX";
    move = tree.nextMoveHeuristic(boardString);
    boardString = "OXO-XXOOX";
    move = tree.nextMoveHeuristic(boardString);

/*
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
*/
    return 0;
}
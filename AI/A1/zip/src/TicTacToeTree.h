#pragma once
#include "TicTacToeBoard.h"
#include <string>
#include <vector>
#include <deque>

using namespace std;

class TicTacToeTree
{
public:
	struct WinDrawStats
	{
	int numXWins;
	int numOWins;
	int numDraws;
	};

	struct TicTacToePlay
	{
		int row;
		int col;
		TicTacToeBoard::PLAYER_TURN xOrO;
	};

	void breadthFirstSearchForOutcome(string boardString, TicTacToeBoard::BOARD_STATE requestedState);
	void depthFirstSearchForOutcome(string boardString, TicTacToeBoard::BOARD_STATE requestedState);
	void depthFirstCountOutcomes(string boardString);
	TicTacToePlay nextMoveHeuristic(string boardString);

private:
	struct Node
	{
		TicTacToeBoard* board;
		vector < Node* > children;
		Node* parent;
	};

	void destructorHelper(Node* aNode);
	void makeChildren(Node* &currentNode, deque<Node*> &frontier, int &numOfBoards);
	
};
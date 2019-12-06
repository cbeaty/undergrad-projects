#pragma once
#include <string>

using namespace std;

class TicTacToeBoard
{
public:
    enum SQUARE_OCCUPANT {
		X,
		O,
		EMPTY
	};

    enum PLAYER_TURN
	{
		X_TURN,
		O_TURN
	};

    enum BOARD_STATE
	{
		X_WIN,
		O_WIN,
		DRAW,
		INCOMPLETE_GAME
	};

    TicTacToeBoard();
	TicTacToeBoard(int bd);
	TicTacToeBoard(string initBoardState);

    string getBoardString();
	int getBoardDimension();
    
    void setSquare(int row, int col, SQUARE_OCCUPANT xOrO);
	SQUARE_OCCUPANT getSquare(int row, int col);

    PLAYER_TURN getPlayerTurn();

    BOARD_STATE getBoardState();

    void printBoard();

private:
    int boardDimension;
	string boardString;

    bool isValidBoardString(string potentialBoardState);

    BOARD_STATE checkRows();
	BOARD_STATE checkCols();
	BOARD_STATE checkDiagonals();
	BOARD_STATE checkDiagonal1();
	BOARD_STATE checkDiagonal2();
	BOARD_STATE checkDraw();
};
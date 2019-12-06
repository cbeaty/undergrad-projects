#include "TicTacToeBoard.h"
#include <iostream>
#include <cmath>

using namespace std;

TicTacToeBoard::TicTacToeBoard()
	: TicTacToeBoard(3)
{
	//call the other constructor
}
//--
TicTacToeBoard::TicTacToeBoard(int bd)
{
    if(bd > 0)
    {
        boardDimension = bd;
        boardString = "";

        for (int i = 0; i < boardDimension * boardDimension; i++)
        {
            boardString += "-";
        }
    }
    else
	{
		throw "~~ Invalid Board Dimension Exception ~~";
	}
}
//--
TicTacToeBoard::TicTacToeBoard(string initBoardString)
{
    if (isValidBoardString(initBoardString))
	{
		boardDimension = sqrt(initBoardString.size());
		boardString = initBoardString;
	}
	else
	{
		throw "~~ Invalid Board String Exception ~~";
	}
}
//--
bool TicTacToeBoard::isValidBoardString(string potentialBoardString)
{
	bool retVal = false;

	if (potentialBoardString.size() > 0)
	{
		int initBoardDimension = sqrt(potentialBoardString.size());

		if ((initBoardDimension * initBoardDimension) == potentialBoardString.size())
		{
			retVal = true;

			for (int i = 0; i < potentialBoardString.size(); i++)
			{
				if (potentialBoardString[i] != 'X' &&
					potentialBoardString[i] != 'O' &&
					potentialBoardString[i] != '-')
				{
					retVal = false;
					break;
				}
			}
		}
	}

	return retVal;
}
//--
string TicTacToeBoard::getBoardString()
{
	return boardString;
}
//--
int TicTacToeBoard::getBoardDimension()
{
	return boardDimension;
}
//--
void TicTacToeBoard::setSquare(int row, int col, SQUARE_OCCUPANT xOrO)
{
	if (row < 0 || row >= boardDimension ||
		col < 0 || col >= boardDimension)
	{
		throw "Invalid dimension in setSquare()";
	}

	if (xOrO == EMPTY)
	{
		throw "Cannot set a square to empty";
	}

	char playerCharacter;
	if (xOrO == X)
	{
		playerCharacter = 'X';
	}
	else
	{
		playerCharacter = 'O';
	}

	boardString[(row * boardDimension) + col] = playerCharacter;
}
//--
TicTacToeBoard::SQUARE_OCCUPANT TicTacToeBoard::getSquare(int row, int col)
{
	SQUARE_OCCUPANT retVal = EMPTY;

	if (row < 0 || row >= boardDimension ||
		col < 0 || col >= boardDimension)
	{
		throw "Invalid dimension in getSquare()";
	}

	char squareState = boardString[(row * boardDimension) + col];

	if (squareState == 'X')
	{
		retVal = SQUARE_OCCUPANT::X;
	}
	else if (squareState == 'O')
	{
		retVal = SQUARE_OCCUPANT::O;
	}

	return retVal;
}
//--
TicTacToeBoard::PLAYER_TURN TicTacToeBoard::getPlayerTurn()
{
	PLAYER_TURN retVal;

	int numXAndOs = 0;

	for (int i = 0; i < boardString.size(); i++)
	{
		if (boardString[i] == 'X' || boardString[i] == 'O')
		{
			numXAndOs++;
		}
	}

	if (numXAndOs % 2 == 1)
	{
		retVal = PLAYER_TURN::O_TURN;
	}
    else
    {
        retVal = PLAYER_TURN::X_TURN;
    }

	return retVal;
}
//--
TicTacToeBoard::BOARD_STATE TicTacToeBoard::getBoardState()
{
	BOARD_STATE retVal = checkRows();

	if (retVal == BOARD_STATE::INCOMPLETE_GAME)
	{
		retVal = checkCols();

		if (retVal == BOARD_STATE::INCOMPLETE_GAME)
		{
			retVal = checkDiagonals();

			if (retVal == BOARD_STATE::INCOMPLETE_GAME)
			{
				retVal = checkDraw();
			}
		}
	}

	return retVal;
}
//--
TicTacToeBoard::BOARD_STATE TicTacToeBoard::checkRows()
{
	BOARD_STATE retVal = BOARD_STATE::INCOMPLETE_GAME;

	for (int row = 0; row < boardDimension; row++)
	{
		int numXs = 0;
		int numOs = 0;

		for (int col = 0; col < boardDimension; col++)
		{
			char currentSquare = getSquare(row, col);

			if (currentSquare == SQUARE_OCCUPANT::X)
			{
				numXs++;
			}
			else if (currentSquare == SQUARE_OCCUPANT::O)
			{
				numOs++;
			}
		}

		if (numXs == boardDimension)
		{
			retVal = BOARD_STATE::X_WIN;
			break;
		}
		else if (numOs == boardDimension)
		{
			retVal = BOARD_STATE::O_WIN;
			break;
		}
	}

	return retVal;
}
//--
TicTacToeBoard::BOARD_STATE TicTacToeBoard::checkCols()
{
	BOARD_STATE retVal = BOARD_STATE::INCOMPLETE_GAME;

	for (int col = 0; col < boardDimension; col++)
	{
		int numXs = 0;
		int numOs = 0;

		for (int row = 0; row < boardDimension; row++)
		{
			char currentSquare = getSquare(row, col);

			if (currentSquare == SQUARE_OCCUPANT::X)
			{
				numXs++;
			}
			else if (currentSquare == SQUARE_OCCUPANT::O)
			{
				numOs++;
			}
		}

		if (numXs == boardDimension)
		{
			retVal = BOARD_STATE::X_WIN;
			break;
		}
		else if (numOs == boardDimension)
		{
			retVal = BOARD_STATE::O_WIN;
			break;
		}
	}

	return retVal;
}
//--
TicTacToeBoard::BOARD_STATE TicTacToeBoard::checkDiagonals()
{
	BOARD_STATE retVal = checkDiagonal1();

	if (retVal == BOARD_STATE::INCOMPLETE_GAME)
	{
		retVal = checkDiagonal2();
	}
	return retVal;
}
//--
TicTacToeBoard::BOARD_STATE TicTacToeBoard::checkDiagonal1()
{
	BOARD_STATE retVal = BOARD_STATE::INCOMPLETE_GAME;

	int numXs = 0;
	int numOs = 0;

	int col = 0;

	for (int row = 0; row < boardDimension; row++)
	{	
		char currentSquare = getSquare(row, col);

		if (currentSquare == SQUARE_OCCUPANT::X)
		{
			numXs++;
		}
		else if (currentSquare == SQUARE_OCCUPANT::O)
		{
			numOs++;
		}

		col++;
	}

	if (numXs == boardDimension)
	{
		retVal = BOARD_STATE::X_WIN;
	}
	else if (numOs == boardDimension)
	{
		retVal = BOARD_STATE::O_WIN;
	}

	return retVal;
}
//--
TicTacToeBoard::BOARD_STATE TicTacToeBoard::checkDiagonal2()
{
	BOARD_STATE retVal = BOARD_STATE::INCOMPLETE_GAME;

	int numXs = 0;
	int numOs = 0;

	int col = boardDimension - 1;

	for (int row = 0; row < boardDimension; row++)
	{		
		char currentSquare = getSquare(row, col);

		if (currentSquare == SQUARE_OCCUPANT::X)
		{
			numXs++;
		}
		else if (currentSquare == SQUARE_OCCUPANT::O)
		{
			numOs++;
		}

		col--;
	}

	if (numXs == boardDimension)
	{
		retVal = BOARD_STATE::X_WIN;
	}
	else if (numOs == boardDimension)
	{
		retVal = BOARD_STATE::O_WIN;
	}

	return retVal;
}
//--
TicTacToeBoard::BOARD_STATE TicTacToeBoard::checkDraw()
{
	BOARD_STATE retVal = BOARD_STATE::DRAW;

	for (int i = 0; i < boardString.size(); i++)
	{
		if (boardString[i] == '-')
		{
			retVal = BOARD_STATE::INCOMPLETE_GAME;
			break;
		}
	}
	return retVal;
}
//--
void TicTacToeBoard::printBoard()
{
	for (int row = 0; row < boardDimension; row++)
	{
		for (int col = 0; col < boardDimension; col++)
		{
			char currentSquare = getSquare(row, col);

			if (currentSquare == SQUARE_OCCUPANT::X)
			{
				cout << " X ";
			}
			else if (currentSquare == SQUARE_OCCUPANT::O)
			{
				cout << " O ";
			}
			else //empty
			{
				cout << "   ";
			}

			if (col < (boardDimension - 1))
			{
				cout << "|";
			}
		}
		cout << endl;

		if (row < (boardDimension - 1))
		{
			for (int i = 0; i < boardDimension - 1; i++)
			{
				cout << "---+";
			}
			cout << "---\n";
		}
	}
}
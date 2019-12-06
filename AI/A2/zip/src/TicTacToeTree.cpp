#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include "TicTacToeTree.h"

using namespace std;

void TicTacToeTree::breadthFirstSearchForOutcome(string boardString, TicTacToeBoard::BOARD_STATE requestedState)
{
    TicTacToeBoard* board = new TicTacToeBoard(boardString); //Create the initial game board
    Node* root = new Node; //Create the root node
    root->board = board; //Have the root's board be the initial board
    root->parent = nullptr; //The root node doesn't have a parent
    deque<Node*> frontier; //Create the queue of Node*
    frontier.push_back(root); //Add the root node

    int numOfBoards = 1; //Will be incremented everytime a new board is made, count starts at one for the root
    bool isFound = false; //Used to print if no goal state is found

    while (!frontier.empty()) {
        Node* currentNode = frontier.front(); //Get the current most node (front for breadth)
        frontier.pop_front();
        //If the board is a goal state
        if (currentNode->board->getBoardState() == requestedState) {
            isFound = true; //We found a goal state
            deque<Node*> finalSteps; //This queue is used to trace back from the goal state to the root node
            while(currentNode != nullptr) {
                finalSteps.push_back(currentNode); //Get the path to the root node
                currentNode = currentNode->parent;
            }
            if (requestedState == TicTacToeBoard::BOARD_STATE::X_WIN) {
                cout << "BFS X win." << endl;
            }
            else if (requestedState == TicTacToeBoard::BOARD_STATE::O_WIN) {
                cout << "BFS O win." << endl;
            }
            else {
                cout << "BFS draw." << endl;
            }
            //Printing all the steps to get to the goal state
            int i = 1;
            while (!finalSteps.empty()) {
                Node* current = finalSteps.back();
                cout << i << "." << endl;
                current->board->printBoard();
                cout << endl;
                finalSteps.pop_back();
                i++;
            }
            cout << "There were " << numOfBoards << " boards created." << endl;
            cout << endl;
            break;
        }
        //If we didn't find a goal state, we need to create the next possible moves from the current state
        //and then add those children to the frontier queue to be checked
        else {
            makeChildren(currentNode, frontier, numOfBoards);
        }
    }
    if (isFound == false) {
        cout << "There were no solutions found." << endl;
    }
    destructorHelper(root);
}

void TicTacToeTree::depthFirstSearchForOutcome(string boardString, TicTacToeBoard::BOARD_STATE requestedState)
{
	TicTacToeBoard* board = new TicTacToeBoard(boardString); //Create the initial game board
    Node* root = new Node; //Create the root node
    root->board = board; //Have the root's board be the initial board
    root->parent = nullptr; //The root node doesn't have a parent
    deque<Node*> frontier; //Create the queue of Node*
    frontier.push_back(root); //Add the root node

    int numOfBoards = 1; //Will be incremented everytime a new board is made, count starts at one for the root
    bool isFound = false; //Used to print if no goal state is found

    while (!frontier.empty()) {
        Node* currentNode = frontier.back(); //Get the current most node (back for depth)
        frontier.pop_back();
        //If the board is a goal state
        if (currentNode->board->getBoardState() == requestedState) {
            isFound = true;
            deque<Node*> finalSteps;
            while(currentNode != nullptr) {
                finalSteps.push_back(currentNode);
                currentNode = currentNode->parent;
            }
            if (requestedState == TicTacToeBoard::BOARD_STATE::X_WIN) {
                cout << "DFS X win." << endl;
            }
            else if (requestedState == TicTacToeBoard::BOARD_STATE::O_WIN) {
                cout << "DFS O win." << endl;
            }
            else {
                cout << "DFS draw." << endl;
            }
            int i = 1;
            while (!finalSteps.empty()) {
                Node* current = finalSteps.back();
                cout << i << "." << endl;
                current->board->printBoard();
                cout << endl;
                finalSteps.pop_back();
                i++;
            }
            cout << "There were " << numOfBoards << " boards created." << endl;
            cout << endl;
            break;
        }
        else {
            makeChildren(currentNode, frontier, numOfBoards);
        }
    }
    if (isFound == false) {
        cout << "There were no solutions found." << endl;
    }
    destructorHelper(root);
}

TicTacToeTree::WinDrawStats TicTacToeTree::depthFirstCountOutcomes(string boardString) {
    TicTacToeBoard* board = new TicTacToeBoard(boardString); //Create the initial game board
    Node* root = new Node; //Create the root node
    root->board = board; //Have the root's board be the initial board
    root->parent = nullptr; //The root node doesn't have a parent
    deque<Node*> frontier; //Create the queue of Node*
    frontier.push_back(root); //Add the root node

    TicTacToeBoard::BOARD_STATE xWin = TicTacToeBoard::BOARD_STATE::X_WIN;
    TicTacToeBoard::BOARD_STATE oWin = TicTacToeBoard::BOARD_STATE::O_WIN;
    TicTacToeBoard::BOARD_STATE draw = TicTacToeBoard::BOARD_STATE::DRAW;
    TicTacToeTree::WinDrawStats WinDrawStats = {0,0,0};
    int numOfBoards = 1; //Will be incremented everytime a new board is made, count starts at one for the root

    while (!frontier.empty()) {
        Node* currentNode = frontier.back(); //Get the current most node (back for depth)
        frontier.pop_back();
        //If the board is a winning state increment the WinDrawStats
        if (currentNode->board->getBoardState() == xWin) {
            WinDrawStats.numXWins++;
        }
        else if (currentNode->board->getBoardState() == oWin) {
            WinDrawStats.numOWins++;
        }
        else if (currentNode->board->getBoardState() == draw) {
            WinDrawStats.numDraws++;
        }
        else {
            makeChildren(currentNode, frontier, numOfBoards);
        }
    }
    destructorHelper(root);
    return WinDrawStats;
}

int TicTacToeTree::getBoardScore(TicTacToeBoard* board, int depth, TicTacToeBoard::PLAYER_TURN maximizer) {
    int retVal = 0;
    //if the board is in a terminal state (win or loss), return +10 if the player won 
    //and -10 if they lost. The modifier of depth helps the AI fight, even when they 
    //will lose no matter what.
    if (board->getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
        if (board->getPlayerTurn() != maximizer) {
            retVal = 10 - depth;
        }
        else {
            retVal = depth - 10;
        }
    }
    //Will return zero on a draw, or an incomplete board
    return retVal;
}
//This function looks at the rest of the ways the game could go, and returns the value of the board
int TicTacToeTree::findBestMove(TicTacToeBoard* board, int depth, bool isMax, TicTacToeBoard::PLAYER_TURN maximizer) {
    int retVal = getBoardScore(board, depth, maximizer);
    //If the game is in a completed state, return the value of the board
    if (board->getBoardState() != TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME) {
        return retVal;
    }
    //If this is the maximizer's turn, then we need to find the maximum board state
    if (isMax) {
        int best = INT8_MIN;

        for (int row = 0; row < board->getBoardDimension(); row++)
        {
            for (int col = 0; col < board->getBoardDimension(); col++)
            {
                if (board->getSquare(row, col) == TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)
                {   
                    TicTacToeBoard* newBoard = new TicTacToeBoard(board->getBoardString());
                    if (newBoard->getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN)
                    {
                        newBoard->setSquare(row, col, TicTacToeBoard::X);
                    }
                    else
                    {
                        newBoard->setSquare(row, col, TicTacToeBoard::O);
                    }

                    best = max(best, findBestMove(newBoard,depth+1,!isMax,maximizer));

                    delete newBoard;
                }
            }
        }
        return best;
    }
    //Otherwise we need to find the lowest state (the one the opponent will likely choose if playing optimally)
    else {
        int best = INT8_MAX;

        for (int row = 0; row < board->getBoardDimension(); row++)
        {
            for (int col = 0; col < board->getBoardDimension(); col++)
            {
                if (board->getSquare(row, col) == TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)
                {   
                    TicTacToeBoard* newBoard = new TicTacToeBoard(board->getBoardString());
                    if (newBoard->getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN)
                    {
                        newBoard->setSquare(row, col, TicTacToeBoard::X);
                    }
                    else
                    {
                        newBoard->setSquare(row, col, TicTacToeBoard::O);
                    }

                    best = min(best, findBestMove(newBoard,depth+1,!isMax,maximizer));

                    delete newBoard;
                }
            }
        }
        return best;
    }
}

TicTacToeTree::TicTacToePlay TicTacToeTree::nextMoveHeuristic(string boardString) {
    TicTacToeBoard* board = new TicTacToeBoard(boardString);
    TicTacToeBoard::PLAYER_TURN maximizer = board->getPlayerTurn();
    TicTacToeTree::TicTacToePlay retVal = {-1,-1,maximizer};
    int best = INT8_MIN;
    for (int row = 0; row < board->getBoardDimension(); row++)
    {
        for (int col = 0; col < board->getBoardDimension(); col++)
        {
            if (board->getSquare(row, col) == TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)
            {   
                TicTacToeBoard* newBoard = new TicTacToeBoard(board->getBoardString());
                if (newBoard->getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN)
                {
                    newBoard->setSquare(row, col, TicTacToeBoard::X);
                }
                else
                {
                    newBoard->setSquare(row, col, TicTacToeBoard::O);
                }

                int move = findBestMove(newBoard, 0, false, maximizer);

                delete newBoard;

                if (move > best) 
                { 
                    retVal.row = row; 
                    retVal.col = col; 
                    best = move; 
                } 
            }
        }
    }
    cout << "Board Before: " << endl;
    board->printBoard();
    printPlayer(retVal);
    cout << "Board After: " << endl;
    if (retVal.xOrO == TicTacToeBoard::PLAYER_TURN::X_TURN) {
        board->setSquare(retVal.row,retVal.col,TicTacToeBoard::X);
    }
    else {
        board->setSquare(retVal.row,retVal.col,TicTacToeBoard::O);
    }
    
    board->printBoard();
    delete board;
    return retVal;
}

void TicTacToeTree::destructorHelper(Node* aNode)
{
    if (aNode->children.size() > 0)
    {
        for (size_t i = 0; i < aNode->children.size(); i++)
        {
            destructorHelper(aNode->children[i]);
            delete aNode->children[i];                
        }
    }
    delete aNode->board;
}

void TicTacToeTree::makeChildren(Node* &currentNode, deque<Node*> &frontier, int &numOfBoards) {
    if (currentNode->board->getBoardState() == TicTacToeBoard::BOARD_STATE::INCOMPLETE_GAME)
    {
        for (int row = 0; row < currentNode->board->getBoardDimension(); row++)
        {
            for (int col = 0; col < currentNode->board->getBoardDimension(); col++)
            {
                if (currentNode->board->getSquare(row, col) == TicTacToeBoard::SQUARE_OCCUPANT::EMPTY)
                {   
                    TicTacToeBoard* newBoard = new TicTacToeBoard(currentNode->board->getBoardString());
                    numOfBoards++;

                    if (newBoard->getPlayerTurn() == TicTacToeBoard::PLAYER_TURN::X_TURN)
                    {
                        newBoard->setSquare(row, col, TicTacToeBoard::X);
                    }
                    else
                    {
                        newBoard->setSquare(row, col, TicTacToeBoard::O);
                    }

                    Node* newNode = new Node;
                    newNode->board = newBoard;
                    newNode->parent = currentNode;

                    currentNode->children.push_back(newNode);

                    frontier.push_back(newNode);
                }
            }
        }
    }
}

void TicTacToeTree::printPlayer(TicTacToeTree::TicTacToePlay move) {
    char player = '-';
    if (move.xOrO == TicTacToeBoard::PLAYER_TURN::X_TURN) {
        player = 'X';
    }
    else {
        player = 'O';
    }
    cout << "The next best move for " << player << " is:" << endl;
    cout << "Row: " << move.row << " Col: " << move.col << endl; 
}
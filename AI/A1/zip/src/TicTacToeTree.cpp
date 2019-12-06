#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "TicTacToeTree.h"

using namespace std;

void TicTacToeTree::breadthFirstSearchForOutcome(string boardString, TicTacToeBoard::BOARD_STATE requestedState)
{
    TicTacToeBoard* board = new TicTacToeBoard(boardString); //Create the initial game board
    vector<Node*> explored; 
    Node* root = new Node; //Create the root node
    root->board = board; //Have the root's board be the initial board
    root->parent = nullptr; //The root node doesn't have a parent
    deque<Node*> frontier; //Create the queue of Node*
    frontier.push_back(root); //Add the root node
    explored.push_back(root);

    int numOfBoards = 1; //Will be incremented everytime a new board is made, count starts at one for the root
    bool isFound = false; //Used to print if no goal state is found

    while (!frontier.empty()) {
        Node* currentNode = frontier.front(); //Get the current most node (front for breadth)
        explored.push_back(currentNode);
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
    vector<Node*> explored; 
    Node* root = new Node; //Create the root node
    root->board = board; //Have the root's board be the initial board
    root->parent = nullptr; //The root node doesn't have a parent
    deque<Node*> frontier; //Create the queue of Node*
    frontier.push_back(root); //Add the root node
    explored.push_back(root);

    int numOfBoards = 1; //Will be incremented everytime a new board is made, count starts at one for the root
    bool isFound = false; //Used to print if no goal state is found

    while (!frontier.empty()) {
        Node* currentNode = frontier.back(); //Get the current most node (back for depth)
        explored.push_back(currentNode);
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

void TicTacToeTree::destructorHelper(Node* aNode)
{
    if (aNode->children.size() > 0)
    {
        for (int i = 0; i < aNode->children.size(); i++)
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
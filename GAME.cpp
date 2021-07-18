#include<iostream>
#include<vector>
#include "GAME.h"
using namespace std;

void Connect4Game::setBoard()
{
    for(int r = 0; r < MAX_ROW; r++)
    {
        for(int c = 0; c <MAX_COL; c++)
        {
            board[r][c] = 0;
        }
    }
}

//Function to Print the Board
void Connect4Game::printBoard(vector<vector<int>> &b)
{
    for (int i = 0; i < MAX_COL; i++)
    {
        cout << " " << i;
    }
    cout << endl << "---------------" << endl;
    for (int r = 0; r < MAX_ROW; r++)
    {
        for (int c = 0; c < MAX_COL; c++)
        {
            cout << "|";
            switch (b[MAX_ROW - r - 1][c])
            {
            case 0:
                cout << " ";
                break;
            case 1:
                cout << "O";
                break;
            case 2:
                cout << "X";
                break;
            }
            if (c + 1 == MAX_COL)
            {
                cout << "|";
            }
        }
        cout << endl;
    }
    cout << "---------------" << endl;
    cout << endl;
}

void Connect4Game::playGame(int choice)
{
    bool gameOver = false;
    int bestCol, turn = 0, currentPlayer = 0;
    Connect4Play player1Turn, player2Turn;
    printBoard(board);
    while(gameOver == false)
    {
        turn += 1;
        if((turn % 2) == 0)
        {
            currentPlayer = 2;
        }
        else
        {
            currentPlayer = 1;
        }
        if (currentPlayer == 1)
        {
            bestCol = player1Turn.getColumn(board, 1, choice);
            cout<< "Player "<<currentPlayer <<" places token at columnn "<< bestCol<<endl;
            move(board, bestCol, 1);
            gameOver = player1Turn.winningMove(board, currentPlayer);
        }
        else if (currentPlayer == 2)
        {
            bestCol = player2Turn.getColumn(board, 2, choice);
            cout<< "Player "<<currentPlayer <<" places token at columnn "<< bestCol<<endl;
            move(board, bestCol, 2);
            gameOver = player2Turn.winningMove(board, currentPlayer);
        }
        else if (turn = (6*7))
        {
            gameOver = true;
            cout<< "The game is a DRAW!!!\n\n";
        }
        cout<< endl;
        printBoard(board);
    }
    cout<< "Player "<<currentPlayer<< " wins the game!\n\n";
}

void Connect4Game::move(vector<vector<int> >& b, int column, int player)
{
    for(int row = 0; row < MAX_ROW; row++)
    {
        if(b[row][column] == 0)
        {
            b[row][column] = player;
            break;
        }
    }

}


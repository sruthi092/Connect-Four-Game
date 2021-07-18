#include<iostream>
#include<limits.h>
#include <vector>
#include "PLAY.h"
using namespace std;

unsigned int MAX_ROW = 6;
unsigned int MAX_COL = 7;

//Function to get the column player wants to play
int Connect4Play:: getColumn(vector<vector<int> >& b, int player, int choice)
{
    bestMove playerTurn;
    boardTree* newnode = NULL;
    newnode = new boardTree();
    newnode->boardval = b;
    int use_threshold, pass_threshold, depth = 0;
    use_threshold = INT_MAX;//10000000;
    pass_threshold = INT_MIN;//10000000 * (-1);
    if (choice == 1|| choice == 2 || choice == 3)
    {
        if (player == 1)
        {

            playerTurn = minMax(newnode, depth, player, use_threshold, pass_threshold, choice);
        }
        else
        {
            playerTurn = alphaBeta(newnode,  depth, INT_MIN, INT_MAX, player, choice);

        }
    }
    if (choice == 4|| choice == 5 || choice == 6)
    {
        if (player == 1)
        {
            playerTurn = minMax(newnode, depth, player, use_threshold, pass_threshold, choice);
        }
        else
        {
            playerTurn = minMax(newnode, depth, player, use_threshold, pass_threshold, choice);
        }
    }
    if (choice == 7|| choice == 8 || choice == 9)
    {
        if (player == 1)
        {
            playerTurn = alphaBeta(newnode, depth, INT_MIN, INT_MAX, player, choice);
        }
        else
        {
            playerTurn = alphaBeta(newnode,  depth, INT_MAX, INT_MIN, player, choice);
        }
    }

    cout<< "Nodes expanded on calling minmaxAB - "<<nodes_expanded_minmaxAB<<endl;
    cout<< "Nodes generated on calling minmaxAB - "<<nodes_generated_minmaxAB<<endl;
    cout<< "Nodes generated on calling AlphaBetaSearch - "<<nodes_generated_AlphaBetaSearch<<endl;
    cout<< "Nodes expanded on calling AlphaBetaSearch - "<<nodes_expanded_AlphaBetaSearch<<endl;
    nodesGenerated = nodes_generated_minmaxAB + nodes_generated_AlphaBetaSearch;
    cout<< "Total number of nodes generated: " << nodesGenerated << endl;
    cout << "Memory need for 1 node is: 1236 bytes." << endl;
    int x = 1236 * nodesGenerated;
    cout << "Total memory needed for the algorithm is : " << x << "bytes = " << x / (1024) << "kb" << endl;
    return playerTurn.bestColumn;
}


bool Connect4Play:: deepEnough(boardTree* &board, int depth, int player)
{
    if((depth >= 2) || (winningMove(board->boardval, player) == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

 //Function to find the score of a set of 4 spots and return the score of the row/column
int Connect4Play:: getScore(vector<int> compSet, int player)
{
    int positive = 0, negative = 0, empty =0, score = 0;
    for(int i = 0; i < compSet.size(); i++)
    {
        positive += (compSet[i] == player) ? 1 : 0;
        negative += (compSet[i] != 0) ? 1 : 0;
        empty += (compSet[i] == 0) ? 1 : 0;
    }
    negative -= positive;
    if (positive == 4)
    {
        score = 100001;
    }
    else if (positive == 3 && empty == 1)
    {
        score += 1000;
    }
    else if (positive == 2 && empty == 2)
    {
        score += 100;
    }
    else if (negative == 2 && empty == 2)
    {
        score -= 101;
    }
    else if(negative == 3 && empty == 1)
    {
        score -= 1001;
    }
    else if(negative == 4)
    {
        score -= 100000;
    }
    return score;
}


//Evaluation Function1
int Connect4Play::evaluationFunction1(boardTree* &board, int player)
{
    int score = 0;
    vector<int> rowset(7);
    vector<int> colset(6);
    vector<int> set(4);

    // horizontal checks, we're looking for sequences of 4
    //containing any combination of AI, PLAYER, and empty pieces

    for(int r = 0; r < MAX_ROW; r++)
    {
        for(int c = 0; c < MAX_COL; c++)
        {
            rowset[c] = board->boardval[r][c];
        }
        for(int c = 0; c < MAX_COL; c++)
        {
            for(int i = 0; i < 4; i++)
            {
                set[i] = rowset[c+i];
            }
            score += getScore(set, player);
        }
    }

    //vertical
    for(int c = 0; c < MAX_COL; c++)
    {
        for(int r = 0; r < MAX_ROW; r++)
        {
            colset[r] = board->boardval[r][c];
        }
        for(int r = 0; r < 3; r++)
        {
            for(int i = 0; i < 4; i++)
            {
                set[i] = colset[r + i];
            }
            score += getScore(set, player);
        }
    }

    //diagonals right up
    for(int r = 0; r < MAX_ROW-3; r++)
    {
        for(int c = 0; c < MAX_COL; c++)
        {
            rowset[c] = board->boardval[r][c];
        }
        for(int c = 0; c < MAX_COL-3; c++)
        {
            for(int i = 0; i < 4; i++)
            {
                set[i] = board->boardval[r+i][c+i];
            }
            score += getScore(set, player);
        }
    }

    //diagonals left
    for(int r = 0; r < MAX_ROW-3; r++)
    {
        for(int c = 0; c < MAX_COL; c++)
        {
            rowset[c] = board->boardval[r][c];
        }
        for(int c = 0; c < MAX_COL-3; c++)
        {
            for(int i = 0; i < 4; i++)
            {
                set[i] = board->boardval[r+3-i][c+i];
            }
            score += getScore(set, player);
        }
    }
    return score;
}

//Evaluation Function2
int Connect4Play::evaluationFunction2(boardTree* &board, int player)
{
    int utility = 138;//128;
    int sum = 0;
    int evaluationTable[6][7] = {{3, 4, 5, 7, 5, 4, 3},{4, 6, 8, 10, 8, 6, 4},
        {5, 8, 11, 13, 11, 8, 5}, {5, 8, 11, 13, 11, 8, 5},
        {4, 6, 8, 10, 8, 6, 4},{3, 4, 5, 7, 5, 4, 3}
    };
    for (int r = 0; r < MAX_ROW; r++)
    {
        for (int c = 0; c <MAX_COL; c++)
        {
            if (board->boardval[r][c] == 1)
            {
                sum += evaluationTable[r][c];
            }
            else if (board->boardval[r][c] == 2)
            {
                sum -= evaluationTable[r][c];
            }
        }
    }
    return (utility + sum);
}

//Evaluation Function3
int Connect4Play::evaluationFunction3(boardTree* &board, int player)
{
    int rpossibleWins = 0,dppossibleWins = 0, cpossibleWins = 0,nppossibleWins = 0, checkRow, rscore = 0, cscore = 0, dpscore = 0, npscore = 0, possibleWins = 0;
    int rpoossibleWins = 0,dpopossibleWins = 0, cpoossibleWins = 0,npopossibleWins = 0, roscore = 0, coscore = 0, dposcore = 0, nposcore = 0, opossibleWins = 0;
    int centercol = 3;
    int fpscore = 0, foscore = 0;
    bool flag = false;
    int oplayer = opposite(player);
    for(int r = 0; r < MAX_ROW-4; r++)
    {
        if(board->boardval[r][centercol] == player)
        {
            possibleWins = 15;
        }
        else if (board->boardval[r][centercol] == oplayer)
        {
            opossibleWins = -16;
        }
    }
    for(int r = 0; r < MAX_ROW; r++)
    {
        for(int c = 0; c < MAX_COL-3; c++)
        {
            flag = true;
            if(board->boardval[r][c] == player && flag == true)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(board->boardval[r][c+i] != oplayer)
                    {
                        if ((r > 0 && board->boardval[r-1][c+i] != 0) || r == 0)
                        {
                            rpossibleWins += 1;
                        }
                    }
                }
                if (rscore < rpossibleWins)
                {
                    rscore = rpossibleWins;
                }
                flag = false;
            }
        }
    }

    for (int c = 0; c < MAX_COL; c++)
    {
        for(int r = 0; r < MAX_ROW-3; r++)
        {
            flag = true;
            if(board->boardval[r][c] == player && flag == true)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(board->boardval[r+i][c] != oplayer)
                    {
                        cpossibleWins += 1;
                    }
                }
                if (cscore < cpossibleWins)
                {
                    cscore = cpossibleWins;
                }
                flag = false;
            }
            else
            {
                coscore += 2;
            }
        }
    }

    for(int c = 0; c < MAX_COL-3; c++)
    {
        for(int r = 0; r < MAX_ROW-3; r++)
        {
            flag = true;
            if(board->boardval[r][c] == player && flag == true)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(board->boardval[r+i][c+i] != oplayer)
                    {
                        if ((r > 0 && board->boardval[r+i-1][c+i] != 0) || r == 0)
                        {
                            dppossibleWins += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                if (dpscore < dppossibleWins)
                {
                    dpscore = dppossibleWins;
                }
                flag = false;
            }
            else
            {
                dpscore += 2;
            }
        }
    }

    for(int c = 0; c < MAX_COL-3; c++)
    {
        for(int r = 3; r < MAX_ROW; r++)
        {
            flag = true;
            if(board->boardval[r][c] == player && flag == true)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(board->boardval[r-i][c+i] != oplayer)
                    {
                        int x = r-i-1;
                        if (x < 0 || (board->boardval[x][c+i] != 0))
                        {
                            nppossibleWins += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                if (npscore < nppossibleWins)
                {
                    npscore = nppossibleWins;
                }
                flag = false;
            }
            else
            {
                npscore += 2;
            }
        }
    }

    for(int r = 0; r < MAX_ROW; r++)
    {
        for(int c = 0; c < MAX_COL-3; c++)
        {
            flag = true;
            if(board->boardval[r][c] == oplayer && flag == true)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(board->boardval[r][c+i] != player)
                    {
                        if ((r > 0 && board->boardval[r-1][c+i] != 0) || r == 0)
                        {
                            rpoossibleWins += 1;
                        }
                    }
                }
                if (roscore < rpoossibleWins)
                {
                    roscore = rpoossibleWins;
                }
                flag = false;
            }
        }
    }

    for (int c = 0; c < MAX_COL; c++)
    {
        for(int r = 0; r < MAX_ROW-3; r++)
        {
            flag = true;
            if(board->boardval[r][c] == oplayer && flag == true)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(board->boardval[r+i][c] != player)
                    {
                        cpoossibleWins += 1;
                    }
                }
                if (coscore < cpoossibleWins)
                {
                    coscore = cpoossibleWins;
                }
                flag = false;
            }
            else
            {
                coscore += 2;
            }
        }
    }

    for(int c = 0; c < MAX_COL-3; c++)
    {
        for(int r = 0; r < MAX_ROW-3; r++)
        {
            flag = true;
            if(board->boardval[r][c] == oplayer && flag == true)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(board->boardval[r+i][c+i] != player)
                    {
                        if ((r > 0 && board->boardval[r+i-1][c+i] != 0) || r == 0)
                        {
                            dpopossibleWins += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                if (dposcore < dpopossibleWins)
                {
                    dposcore = dpopossibleWins;
                }
                flag = false;
            }
            else
            {
                dposcore += 2;
            }
        }
    }

    for(int c = 0; c < MAX_COL-3; c++)
    {
        for(int r = 3; r < MAX_ROW; r++)
        {
            flag = true;
            if(board->boardval[r][c] == oplayer && flag == true)
            {
                for(int i = 0; i < 4; i++)
                {
                    if(board->boardval[r-i][c+i] != player)
                    {
                        int x = r-i-1;
                        if (x < 0 || (board->boardval[x][c+i] != 0))
                        {
                            npopossibleWins += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                if (nposcore < npopossibleWins)
                {
                    nposcore = npopossibleWins;
                }
                flag = false;
            }
            else
            {
                nposcore += 2;
            }
        }
    }
    fpscore = rscore + cscore + dpscore + npscore;
    foscore = roscore + coscore + dposcore + nposcore;
    return (fpscore - foscore);
}



int Connect4Play:: getRow(boardTree* board, int col)
{
    for(int iter = 0; iter < MAX_ROW; iter++)
    {
        if(board->boardval[iter][col] == 0)
        {
            return iter;
        }
    }
}

//Function to copy board to another 2D vector, to make a duplicate board
vector<vector<int> > Connect4Play :: copy(vector<vector<int> > b)
{
    vector<vector<int>> newBoard(6, vector<int>(7));
    for (int r = 0; r < MAX_ROW; r++)
    {
        for (int c = 0; c < MAX_COL; c++)
        {
            newBoard[r][c] = b[r][c];
        }
    }
    return newBoard;
}

//Function that makes the move for the player
vector<vector<int> > Connect4Play :: drop_piece(vector<vector<int> > b, int r, int c, int p)
{
    for(int r = 0; r < MAX_ROW; r++)
    {
        if(b[r][c] == 0)   //first spot available
        {

            b[r][c] = p;  //set piece
            break;
        }
    }
    return b;

}


//Function to check if the player is opponent or not
int Connect4Play:: opposite(int player)
{
    if(player == 1)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

//Function to implement MinMaxAB algorithm
Connect4Play::bestMove Connect4Play::minMax(boardTree* &board, int depth, int player, int use_threshold, int pass_threshold, int choice)
{
    bestMove pTurn, resultSucc;
    int negValue;
    boardTree* successor[7] = {NULL};
    for(int i = 0; i < 7; i++)
    {
        successor[i] = new boardTree();
    }
    vector<vector<int> >tempBoard;
    if(deepEnough(board, depth, player))
    {
        pTurn.bestColumn = 1*(-1);
        if (choice == 1)
        {
            pTurn.bestScore = evaluationFunction3(board, player);
            if(player == 2)
            {
                pTurn.bestScore = pTurn.bestScore * (-1);
            }
        }
        else if (choice == 2)
        {
            pTurn.bestScore = evaluationFunction2(board, player);//update to EV2
        }
        else if (choice == 3)
        {
            pTurn.bestScore = evaluationFunction3(board, player);//update to EV3
        }
        else if (choice == 4)
        {
            if (player == 1)
            {
                pTurn.bestScore = evaluationFunction1(board, player);
            }
            else
            {
                pTurn.bestScore = evaluationFunction2(board, player);//update to EV2
            }
        }
        else if (choice == 5)
        {
            if (player == 1)
            {
                pTurn.bestScore = evaluationFunction1(board, player);
            }
            else
            {
                pTurn.bestScore = evaluationFunction3(board, player);//update to EV3
            }
        }
        else if (choice == 6)
        {
            if (player == 1)
            {
                pTurn.bestScore = evaluationFunction2(board, player);//update to EV2
            }
            else
            {
                pTurn.bestScore = evaluationFunction3(board, player);//update to EV3
            }
        }

        return pTurn;
    }
    else
    {
        for(int succ = 0; succ < 7; succ++)
        {
            if(board->boardval[5][succ] == 0)
            {
                int possibleRow = getRow(board, succ);
                tempBoard = copy(board->boardval);
                tempBoard = drop_piece(tempBoard, possibleRow, succ, player);
                successor[succ]->boardval = tempBoard;
                nodes_generated_minmaxAB += 1;
                //				int opplayer = opposite(player);
                resultSucc = minMax(successor[succ], depth+1, opposite(player), -pass_threshold, -use_threshold, choice);
                negValue = (-1)*(resultSucc.bestScore);
                if(negValue > pass_threshold)
                {
                    pass_threshold = negValue;
                    pTurn.bestScore = pass_threshold; //* (-1);//resultSucc.bestScore;
                    pTurn.bestColumn = succ;
                    //    					pTurn.bestColumn = succ;
                }
                if (pass_threshold >= use_threshold)
                {
                    pTurn.bestScore = pass_threshold;//*(-1);//resultSucc.bestScore;
                    pTurn.bestColumn = succ;
                    return pTurn;
                }
            }
        }

        nodes_expanded_minmaxAB += 1;
        return pTurn;
    }
}



//Function to determine if a winning move is made and return whether that
//player can have a winning move
bool Connect4Play:: winningMove(vector<vector<int> >& b, int p)
{
    int win = 0;
    for(int c = 0; c < MAX_COL-3; c++)
    {
        for(int r = 0; r < MAX_ROW; r++)
        {
            for(int i = 0; i < 4; i++)
            {
                if(b[r][c+i] == p)
                {
                    win++;
                }
                if(win == 4)
                {
                    return true;
                }
            }
            win = 0;
        }
    }
    for(int c = 0; c < MAX_COL; c++)
    {
        for(int r = 0; r < MAX_ROW-3; r++)
        {
            for(int i = 0; i < 4; i++)
            {
                if(b[r+i][c] == p)
                {
                    win++;
                }
                if (win == 4)
                {
                    return true;
                }
            }
            win = 0;
        }
    }
    for(int c = 0; c < MAX_COL-3; c++)
    {
        for(int r = 3; r < MAX_ROW; r++)
        {
            for(int i = 0; i < 4; i++)
            {
                if(b[r-i][c+i] == p)
                {
                    win++;
                }
                if(win == 4)
                {
                    return true;
                }
            }
            win = 0;
        }
    }
    for (int c = 0; c < MAX_COL-3; c++)
    {
        for(int r = 0; r < MAX_ROW-3; r++)
        {
            for(int i = 0; i < 4; i++)
            {
                if(b[r+i][c+i] == p)
                {
                    win++;
                }
                if(win == 4)
                {
                    return true;
                }
            }
            win = 0;
        }
    }
    return false;
}


//Function to calculate maximum values
int Connect4Play:: max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
        return b;
}

//Function to calculate minimum values
int Connect4Play::min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
        return b;
}

//Function to evaluate the maxValue function for alpha beta search
Connect4Play::bestMove Connect4Play:: maxValue(boardTree* &board, int depth, int alpha, int beta, int player, int choice)
{
    bestMove pTurn;
    bestMove v, resultSucc;
    int value;
    boardTree* successor[7] = {NULL};

    for(int i = 0; i < MAX_COL; i++)
    {
        successor[i] = new boardTree();
    }
    vector<vector<int> >tempBoard;
    if(deepEnough(board, depth, player))
    {
        pTurn.bestColumn = -1;
        if (choice == 7)
        {
            pTurn.bestScore = evaluationFunction1(board, player);
        }
        if (choice == 8)
        {
            pTurn.bestScore = evaluationFunction1(board, player);
        }
        if (choice == 9)
        {
            pTurn.bestScore = evaluationFunction2(board, player);//ev2
        }

        return pTurn;
    }
    else
    {
        v.bestScore = INT_MIN;
        for(int succ = 0; succ < 7; succ++)
        {
            if(board->boardval[5][succ] == 0)
            {
                int possibleRow = getRow(board, succ);
                tempBoard = copy(board->boardval);
                tempBoard = drop_piece(tempBoard, possibleRow, succ, player);
                successor[succ]->boardval = tempBoard;
                nodes_generated_AlphaBetaSearch += 1;
                value = v.bestScore;
                resultSucc = minValue(successor[succ], depth+1, alpha, beta, player, choice);

                v.bestScore = max(value, resultSucc.bestScore);
                if(v.bestScore == resultSucc.bestScore)
                {
                    v.bestColumn = succ;
                }
                if(v.bestScore >= beta)
                {
                    return v;
                }
                alpha = max(alpha, v.bestScore);
            }

        }
        nodes_expanded_AlphaBetaSearch += 1;
        return v;
    }
}

//Function to evaluate the minValue function for alpha beta search
Connect4Play::bestMove Connect4Play::minValue(boardTree* &board, int depth, int alpha, int beta, int player, int choice)
{
    bestMove pTurn;
    bestMove v, resultSucc;
    int value;
    boardTree* successor[7] = {NULL};
    for(int i = 0; i < MAX_COL; i++)
    {
        successor[i] = new boardTree();
    }
    vector<vector<int> >tempBoard;
    if(deepEnough(board, depth, player))
    {
        pTurn.bestColumn = -1;
        if (choice == 1)
        {
            pTurn.bestScore = evaluationFunction1(board, player);
        }
        else if (choice == 2 || choice == 7)
        {
            pTurn.bestScore = evaluationFunction2(board, player);//ev2
        }
        else if (choice == 3||choice == 8 || choice == 9)
        {
            pTurn.bestScore = evaluationFunction3(board, player);//ev3
        }

        return pTurn;
    }
    else
    {
        v.bestScore = INT_MAX;
        for(int succ = 0; succ < MAX_COL; succ++)
        {
            if(board->boardval[5][succ] == 0)
            {
                int possibleRow = getRow(board, succ);
                tempBoard = copy(board->boardval);
                tempBoard = drop_piece(tempBoard, possibleRow, succ, player);
                successor[succ]->boardval = tempBoard;
                nodes_generated_AlphaBetaSearch += 1;
                value = v.bestScore;
                resultSucc = maxValue(successor[succ], depth+1, alpha, beta, player, choice);

                v.bestScore = min(value, resultSucc.bestScore);
                if(v.bestScore == resultSucc.bestScore)
                {
                    v.bestColumn = succ;

                }
                if(v.bestScore <= alpha)
                {
                    nodes_expanded_AlphaBetaSearch += 1;
                    v.bestColumn = succ;
                    return v;
                }
                beta = min(beta, v.bestScore);
            }
        }
        nodes_expanded_AlphaBetaSearch += 1;
        return v;
        //	return pTurn;

    }
}

//Function to implement Alpha Beta Search Algorithm
Connect4Play::bestMove Connect4Play::alphaBeta(boardTree* &board, int depth, int alpha, int beta, int player, int choice)
{
    bestMove pTurn, resultSucc;
    int negValue;
    int v =0;
    if (choice == 1||choice == 2||choice == 3)
    {
        pTurn = minValue(board, depth, alpha, beta, player, choice);
    }
    else if ((choice == 7 || choice == 8 || choice == 9))
    {
        if (player == 1)
        {
            pTurn = maxValue(board, depth, alpha, beta, player, choice);
        }
        else
        {
            pTurn = minValue(board, depth, alpha, beta, player, choice);
        }
    }
    return pTurn;

}
Connect4Play::~Connect4Play()
{
}



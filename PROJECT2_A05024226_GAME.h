#ifndef PROJECT2_A05024226_GAME_H
#define PROJECT2_A05024226_GAME_H

#include<iostream>
#include<vector>
#include "PROJECT2_A05024226_PLAY.h"

using namespace std;

class Connect4Game{
	public:
	vector<vector<int>> board{6, vector<int>(7)};
	int MAX_ROW = 6;
	int MAX_COL = 7;

	void setBoard();
	void printBoard(vector<vector<int>> &);
	void playGame(int);
	void move(vector<vector<int> >&, int, int);
};
#endif

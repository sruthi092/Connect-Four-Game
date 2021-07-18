#ifndef PROJECT2_A05024226_PLAY_H
#define PROJECT2_A05024226_PLAY_H

#include<iostream>
#include<limits.h>
#include <vector>

using namespace std;


class Connect4Play
{
	public:
	int nodes_generated_minmaxAB = 0;
	int nodes_generated_AlphaBetaSearch = 0;
	int nodes_expanded_minmaxAB = 0;
	int nodes_expanded_AlphaBetaSearch = 0;
	int nodesGenerated = 0;
	struct boardTree
	{
		vector<vector <int> > boardval{6, vector<int>(7)};
		vector<boardTree*> successor{7};
	};
	boardTree* head;
	struct bestMove
	{
		int bestScore;
		int bestColumn;
	};

	int getColumn(vector<vector<int> >&, int, int);
	bool deepEnough(boardTree* &, int , int );
	int getScore(vector<int>, int);
	int evaluationFunction1(boardTree* &, int);
	int evaluationFunction2(boardTree* &, int);
	int evaluationFunction3(boardTree* &, int);
	int getRow(boardTree*, int);
	vector<vector<int> > copy(vector<vector<int> > );
	vector<vector<int> > drop_piece(vector<vector<int> > , int , int , int );
	int opposite(int);
	bestMove minMax(boardTree* &, int , int , int , int , int );
	bool winningMove(vector<vector<int> >& , int);
	int max(int , int );
	int min(int , int );
	bestMove maxValue(boardTree* &, int , int , int , int , int );
	bestMove minValue(boardTree* &, int , int , int , int , int );
	bestMove alphaBeta(boardTree* &, int , int , int , int , int );
	~Connect4Play();
};
#endif

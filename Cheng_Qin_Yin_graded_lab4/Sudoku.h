#ifndef SUDOKU_H
#define SUDOKU_H

#include "GameBase.h"
#include <iostream>
#include <vector>
#include <set>

using namespace std;



class Sudoku : public GameBase {

	friend ostream & operator << (ostream &, const Sudoku &);

public:


	//constructors
	Sudoku();

	//virtual functions
	virtual void print();
	virtual bool done();
	virtual int turn();
	//virtual int moveCount();
	virtual bool draw();


	//helper function
	bool checkRow(int, int);
	bool checkColumn(int, int);
	bool checkSquare(int, int, int);
	bool checkUnique(int, int, int);

	bool checkRowSum(int);
	bool checkColumnSum(int);
	bool checkSquareSum();


	bool checkBoard();
	//int keep_turning(unsigned int, unsigned int, unsigned int, unsigned int, string);


};

ostream & operator << (ostream &, const Sudoku &);


#endif
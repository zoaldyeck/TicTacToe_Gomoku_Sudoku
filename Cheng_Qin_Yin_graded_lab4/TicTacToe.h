//TicTacToe.h -- TicTacToe game class interface
//
//wustl key: jinjinqin  chengzhen t.yin
//
//Define and declare TicTacToe game class and functions
//
//2016.3.29

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include "stdafx.h"
#include "status.h"
#include "GameBase.h"
#include <iostream>
#include <string>

using namespace std;

class TicTacToe : public GameBase
{

public:
	TicTacToe();                       //default constructor

	//virtual functions
	virtual void print();

	virtual bool done();              //return true if 3-Xs or Os is in a vertical, horizontal or diagnoal line.

	virtual bool draw();              //return false: there are moves remaining or done() is true
	//return true: no moves remaining and done() is false.

	virtual int turn();              //indicate whose turn 

	friend ostream & operator<<(ostream & os, const TicTacToe & tttgame);   //overload operator <<
};

#endif
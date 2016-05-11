//GoMoKu.h -- TicTacToe game class interface
//
//wustl key: jinjinqin  chengzhen t.yin
//
//Define and declare GoMoKu game class and functions
//
//2016.3.29

#ifndef GOMOKU_H_
#define GOMOKU_H_

#include "stdafx.h"
#include "status.h"
#include "GameBase.h"
#include <iostream>
#include <string>

using namespace std;

class GoMoKu : public GameBase
{

public:
	GoMoKu();          //default constructor

	//virtual functions
	virtual void print();

	virtual bool done();              //return true if 5-Ws or Bs is in a vertical, horizontal or diagnoal line.

	virtual bool draw();              //return false: there are moves remaining or done() is true
	//return true: no moves remaining and done() is false.

	virtual int turn();              //indicate whose turn 

	friend ostream & operator<<(ostream & os, const GoMoKu & gmkgame);   //overload operator <<
};

#endif
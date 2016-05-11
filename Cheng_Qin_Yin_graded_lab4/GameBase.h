//GameBase.h -- GameBase class interface
//
//wustl key: jinjinqin  chengzhen t.yin
//
//Define and declare GameBase class and functions
//
//2016.3.29

#ifndef GAMEBASE_H_
#define GAMEBASE_H_

#include "stdafx.h"
#include "status.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
//gameboard[i].letter = None, O, X, B, W,S
enum piece_letter { None, O, X, B, W,S };
//gamename=TTT or GMK or SDK
enum gametype { TTT, GMK,SDK };
//check if the x and y are in the right range
enum valid_cord { TTT_Lower_Bound = 1, TTT_Upper_Bound = 3, GMK_Lower_Bound = 1, GMK_Upper_Bound = 19,SDK_Lower_Bound=1,SDK_Upper_Bound=9 };
//board size for TicTacToe or Gomoku game
enum valid_size { TTT_size = 5, GMK_size = 21, SDK_size=11};
enum saveornot{ noSave = 10, yeah = 11, pokerball = 12, again = 13 };

int usage_message(char * name);

struct game_piece{
	piece_letter letter;  //None O X B W
	string display;  //" ", "O", "X", "B", "W","some number"
	int position;

	game_piece();
	game_piece(piece_letter letter, string display, int position);
};


class GameBase{

protected:
	gametype game_name;                //TTT or GMK
	int dimension;                     //5 or 21 board

	vector <game_piece> gameboard;

	bool who_turn;                         //who's turn
	char winner;                       //winner
	int turns;                         //how many turns
	unsigned int longest_length;       //longest length
	static shared_ptr<GameBase> sharedPointer;
	int save();
	int saidYes();
	int saidNo();


public:
	void setLongestLength();
	int prompt(unsigned & x, unsigned & y); //prompt the user to enter quit(throw an exception) or a string of cordinates
	virtual void prompt(unsigned int &, unsigned int &, unsigned int &);//prompt for sudoku
	int play();
	static void argCheck(int argNum, char* argName[]); //static method
	bool validcommand(string & command, gametype gamename);  //check if the command from user is valid
	static shared_ptr<GameBase> instance();

	//vritual functions
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;

};

#endif
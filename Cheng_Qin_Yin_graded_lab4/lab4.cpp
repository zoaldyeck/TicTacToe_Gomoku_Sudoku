// lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameBase.h"
#include "status.h"
#include "Sudoku.h"
#include "TicTacToe.h"
#include <iostream>
using namespace std;

#define n1 19

int main(int argc, char* argv[])
{
	//check argc and argv first, may throw out null_ptr(wrong second command)
	//may throw out invalid_argc_number(argc!=2)
	try{
		GameBase::argCheck(argc, argv);
		shared_ptr<GameBase> pointer = GameBase::instance();
		if (pointer == nullptr)
			throw null_ptr;
		else
			//if p is not null, play
			pointer->play();
		//safely delete p after play()
		//delete p;
	}
	catch (indicator n){
		//if argc!=2, call usage_message to give a correct format

		if (n == invalid_argc_number){
			return usage_message(argv[program_index]);
		}
		//play() or prompt() throw out quit_game, catch it here and return it.
		if (n == quit_game){
			cout << "Warning: You quit the game!" << endl;
			return quit_game;
		}
		//if the second command is wrong, remind the correct format
		if (n == null_ptr){
			cout << "Wrong command, enter TicTacToe or Gomoku or Sudoku next to the program name" << endl;
			return null_ptr;
		}
		if (n == not_null_ptr){
			cout << "The shared_ptr is already initialized" << endl;
			return not_null_ptr;
		}
		if (n == n1){
			cout << "" << endl;
			return 20;
		}
		if (n == 20){
			cout << "" << endl;
			return 21;
		}
		if (n == 21){
			cout << "part2" << endl;
			return 22;
		}
		if (n == 22){
			cout << "still part 2" << endl;
			return 23;
		}
		if (n == 23){
			cout << "still part 2" << endl;
			return 24;
		}
	}
	//other error
	catch (...){
		cerr << "Unknow error..." << endl;
	}
	return success_game;
}

// TicTacToe.cpp : Defines the entry point for the console application.
//
//wustl key: jinjinqin  chengzhen t.yin
//
//2016.3.30

#include "stdafx.h"
#include "status.h"
#include "GameBase.h"
#include "TicTacToe.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

TicTacToe::TicTacToe(){
	game_name = TTT;                          //TTT 
	dimension = TTT_size;                     //5 

	for (int i = 0; i < dimension * dimension; ++i){      //empty vector  length = 25
		game_piece empty;
		gameboard.push_back(empty);
	}
	int count = 1;

	who_turn = true;                             //who's turn: x's turn = true, o's turn = false
	winner = ' ';                                //winner: x or o
	turns = 0;                                   //how many turns
	longest_length = 1;                          //longest length
	ifstream getGame("tictactoe");
	string line;
	if (getGame.is_open()){
		string firstline;
		getline(getGame, firstline);
		if (firstline.compare("NO DATA") != 0 && firstline.compare("tictactoe") == 0){
			while (getline(getGame, line)){
				count++;
				string letter;
				getline(getGame, letter);
				if (letter.compare("X") == 0){
					gameboard[stoi(line)] = game_piece(X, "X", stoi(line));
				}
				else{
					gameboard[stoi(line)] = game_piece(O, "O", stoi(line));
				}
			}
			getGame.close();

		}
	}
	print();
	if (count % 2 == 0){
		who_turn = !who_turn;
	}


}


/* use << to print out the game board
*/
std::ostream & operator<<(std::ostream & os, const TicTacToe & tttgame){

	//print out the game board, row by row ,column by column. and print out the cordinate
	for (int row = TTT_size - 1; row >= 0; --row){
		os << row;
		for (int col = 1; col < TTT_size - 1; ++col){
			int loc = row*TTT_size + col;
			//set width
			os.width(2 * tttgame.longest_length);
			os << tttgame.gameboard[loc].display;
		}
		os << endl;
	}
	for (int col = 0; col < TTT_size; ++col){
		os << col;
		os.width(2 * tttgame.longest_length);
	}

	os << endl;
	return os;
}

void TicTacToe::print(){
	cout << *this << endl;
}

/*check if there are 3 Xs or Os in 3 directions, and change winner to be X or O.
*/
bool TicTacToe::done(){
	//check vertically
	for (int col = 1; col < TTT_size - 1; ++col){
		if (gameboard[TTT_size + col].letter == X && gameboard[2 * TTT_size + col].letter == X
			&& gameboard[3 * TTT_size + col].letter == X){
			winner = 'X';
			return true;
		}
		if (gameboard[TTT_size + col].letter == O && gameboard[2 * TTT_size + col].letter == O
			&& gameboard[3 * TTT_size + col].letter == O){
			winner = 'O';
			return true;
		}
	}

	//check horizontally
	for (int row = 1; row < TTT_size - 1; ++row){
		if (gameboard[row * TTT_size + 1].letter == X && gameboard[row * TTT_size + 2].letter == X
			&& gameboard[row * TTT_size + 3].letter == X){
			winner = 'X';
			return true;
		}
		if (gameboard[row * TTT_size + 1].letter == O && gameboard[row * TTT_size + 2].letter == O
			&& gameboard[row * TTT_size + 3].letter == O){
			winner = 'O';
			return true;
		}
	}
	//check diagnoally
	if (gameboard[6].letter == X && gameboard[12].letter == X && gameboard[18].letter == X){
		winner = 'X';
		return true;
	}
	if (gameboard[6].letter == O && gameboard[12].letter == O && gameboard[18].letter == O){
		winner = 'O';
		return true;
	}
	if (gameboard[8].letter == X && gameboard[12].letter == X && gameboard[16].letter == X){
		winner = 'X';
		return true;
	}
	if (gameboard[8].letter == O && gameboard[12].letter == O && gameboard[16].letter == O){
		winner = 'O';
		return true;
	}
	return false;
}

//check if there are moves left and if there is 3 Os or Xs
bool TicTacToe::draw(){
	//done()=true when there are 3 Xs or Os
	if (done())
		return false;          //3 Xs or Os, game complete

	//check if there is moves left.
	for (int row = 1; row < TTT_size - 1; ++row){
		for (int col = 1; col < TTT_size - 1; ++col){
			if (gameboard[row * TTT_size + col].letter == None)
				return false;   //found an empty place, return false
		}
	}

	//It goes here, indicating done()=false, and there is moves left.
	return true;
}

//decide whose turn 
int TicTacToe::turn(){
	unsigned x, y;
	//x's turn
	if (who_turn){
		cout << "X turn: " << endl;
		who_turn = false;

		//get x, y
		//if fail to get x ,y, call prompt repeatly
		//if succeed, change the game_piece value, and turns++, print the board, and the move 
		while (true){
			int prompt_result = prompt(x, y);
			if (prompt_result == quit_game)
				throw quit_game;
			if (prompt_result == success_extract_x_y){
				if (gameboard[y*dimension + x].letter == None){
					gameboard[y*dimension + x].letter = X;
					gameboard[y*dimension + x].display = "X";
					gameboard[y*dimension + x].position = y*dimension+x;
					this->print();
					this->setLongestLength();
					cout << "Player X's move:" << x << "," << y << endl;
					turns++;
					return success_move;
				}
			}
		}
	}
	else{
		cout << "O turn: " << endl;
		who_turn = true;
		//get x, y
		//if fail to get x ,y, call prompt repeatly
		//if succeed, change the game_piece value, and turns++, print the board, and the move 
		while (true){
			int prompt_result = prompt(x, y);
			if (prompt_result == quit_game)
				return quit_game;
			if (prompt_result == success_extract_x_y){
				if (gameboard[y*dimension + x].letter == None){
					gameboard[y*dimension + x].letter = O;
					gameboard[y*dimension + x].display = "O";
					gameboard[y*dimension + x].position = y*dimension + x;
					this->print();
					this->setLongestLength();
					cout << "Player O's move:" << x << "," << y << endl;
					turns++;
					return success_move;
				}
			}
		}
	}
	return failure_move;
}



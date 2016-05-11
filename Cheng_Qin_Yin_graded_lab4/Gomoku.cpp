// GoMoKu.cpp : Defines the entry point for the console application.
//
//wustl key: jinjinqin  chengzhen t.yin
//
//2016.3.30

#include "stdafx.h"
#include "status.h"
#include "GameBase.h"
#include "GoMoKu.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


GoMoKu::GoMoKu(){
	game_name = GMK;                          //GMK
	dimension = GMK_size;                     //21

	for (int i = 0; i < dimension * dimension; ++i){      //empty vector  length = 441
		game_piece empty;
		gameboard.push_back(empty);
	}

	who_turn = false;                             //who's turn: B's turn = true, W's turn = false
	winner = ' ';                                //winner: B or W
	turns = 0;  //how many turns
	int count = 1;
	longest_length = 2; //longest length
	ifstream getGame("gomoku");
	string line;
	if (getGame.is_open()){
		string firstline;
		getline(getGame, firstline);
		if (firstline.compare("NO DATA") != 0 && firstline.compare("GoMoku") == 0){
			while (getline(getGame, line)){
				count++;
				string letter;
				getline(getGame, letter);
				if (letter.compare("B") == 0){
					gameboard[stoi(line)] = game_piece(B, "B", stoi(line));
				}
				else{
					gameboard[stoi(line)] = game_piece(W, "W", stoi(line));
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
std::ostream & operator<<(std::ostream & os, const GoMoKu & gmkgame){

	//print out the game board, row by row ,column by column. and print out the cordinate
	for (int row = GMK_size - 2; row >= 1; --row){
		os << row;
		for (int col = 1; col < GMK_size - 1; ++col){
			int loc = row * GMK_size + col;
			os.width(2 * gmkgame.longest_length);
			os << gmkgame.gameboard[loc].display;
		}
		os << endl;
	}
	os << 'X';
	os.width(2 * gmkgame.longest_length);
	for (int col = 1; col < GMK_size - 1; ++col){
		os << col;
		os.width(2 * gmkgame.longest_length);
	}

	os << endl;
	return os;
}

void GoMoKu::print(){
	cout << *this << endl;
}

/*check if there are 5 Ws or Bs in 3 directions, and change winner to be W or B.
*/
bool GoMoKu::done(){
	//check vertically
	for (int col = 1; col < GMK_size - 1; ++col){
		if (gameboard[GMK_size + col].letter == B && gameboard[two * GMK_size + col].letter == B
			&& gameboard[three * GMK_size + col].letter == B && gameboard[four * GMK_size + col].letter == B
			&& gameboard[five * GMK_size + col].letter == B){
			winner = 'B';
			return true;
		}
		if (gameboard[GMK_size + col].letter == W && gameboard[two * GMK_size + col].letter == W
			&& gameboard[three * GMK_size + col].letter == W && gameboard[four * GMK_size + col].letter == W
			&& gameboard[five * GMK_size + col].letter == W){
			winner = 'W';
			return true;
		}
	}

	//check horizontally
	for (int row = 1; row < GMK_size - 1; ++row){
		if (gameboard[row * GMK_size + one].letter == B && gameboard[row * GMK_size + two].letter == B
			&& gameboard[row * GMK_size + three].letter == B && gameboard[row * GMK_size + four].letter == B
			&& gameboard[row * GMK_size + five].letter == B){
			winner = 'B';
			return true;
		}
		if (gameboard[row * GMK_size + one].letter == W && gameboard[row * GMK_size + two].letter == W
			&& gameboard[row * GMK_size + three].letter == W && gameboard[row * GMK_size + four].letter == W
			&& gameboard[row * GMK_size + five].letter == W){
			winner = 'W';
			return true;
		}
	}
	//check diagnoally
	for (int i = 1; i < GMK_size - 5; ++i){
		int loc1 = i * GMK_size + i;
		if (gameboard[loc1].letter == W){
			int loc2 = (i + one)*(GMK_size + one);
			if (gameboard[loc2].letter == W){
				int loc3 = (i + two)*(GMK_size + one);
				if (gameboard[loc3].letter == W){
					int loc4 = (i + three)*(GMK_size + one);
					if (gameboard[loc4].letter == W){
						int loc5 = (i + four)*(GMK_size + one);
						if (gameboard[loc5].letter == W){
							winner = 'W';
							return true;
						}
					}
				}
			}
		}
		if (gameboard[loc1].letter == B){
			int loc2 = (i + one)*(GMK_size + one);
			if (gameboard[loc2].letter == B){
				int loc3 = (i + two)*(GMK_size + one);
				if (gameboard[loc3].letter == B){
					int loc4 = (i + three)*(GMK_size + one);
					if (gameboard[loc4].letter == B){
						int loc5 = (i + four)*(GMK_size + one);
						if (gameboard[loc5].letter == B){
							winner = 'B';
							return true;
						}
					}
				}
			}
		}

	}
	return false;
}

//check if there are moves left and if there is 5 Ws or Bs
bool GoMoKu::draw(){
	//done()=true when there are 5 Ws or Bs
	if (done())
		return false;          //5 Ws or Bs, game complete

	//check if there is moves left.
	for (int row = 1; row < GMK_size - 1; ++row){
		for (int col = 1; col < GMK_size - 1; ++col){
			if (gameboard[row * GMK_size + col].letter == None)
				return false;   //found an empty place, return false
		}
	}

	//It goes here, indicating done()=false, and there is moves left.
	return true;
}

//decide whose turn
int GoMoKu::turn(){
	unsigned x, y;
	//W's turn
	if (who_turn){
		cout << "W turn: " << endl;
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
					gameboard[y*dimension + x].letter = W;
					gameboard[y*dimension + x].display = "W";
					gameboard[y*dimension + x].position = y*dimension + x;
					this->print();
					this->setLongestLength();
					cout << "Player W's move:" << x << "," << y << endl;
					turns++;
					return success_move;
				}
			}
		}
	}
	else{
		cout << "B turn: " << endl;
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
					gameboard[y*dimension + x].letter = B;
					gameboard[y*dimension + x].display = "B";
					gameboard[y*dimension + x].position = y*dimension + x;
					this->print();
					this->setLongestLength();
					cout << "Player B's move:" << x << "," << y << endl;
					turns++;
					return success_move;
				}
			}
		}
	}
	return failure_move;
}


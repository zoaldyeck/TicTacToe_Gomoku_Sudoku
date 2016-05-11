#include "stdafx.h"

#include <vector>
#include "GameBase.h"
#include "status.h"
#include "Sudoku.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;
Sudoku::Sudoku(){
	game_name = SDK;
	dimension = SDK_size;
	for (int i = 0; i < dimension * dimension; ++i){      //empty vector  length = 441
		game_piece empty;
		gameboard.push_back(empty);
	}

	//who_turn = true;                             //who's turn: B's turn = true, W's turn = false
	//winner = ' ';                                //winner: B or W
	turns = 0;  //how many turns

	for (int i = 0; i < dimension * dimension; ++i){      //empty vector  length = 441
		game_piece empty;
		gameboard.push_back(empty);
	}

	ifstream getGame("sudoku");
	string line;

	if (getGame.is_open()) {
		string firstline;
		getline(getGame, firstline);

		//saved game exists, so load that data
		if (firstline.compare("NO DATA") != 0 && firstline.compare("sudoku") == 0) {
			string location;
			while (getline(getGame, location)) {
				string number;
				getline(getGame, number);
				gameboard[stoi(location)].display = number;
			}
		}
		else {
			ifstream getDefault("sudoku0");
			string location;
			while (getline(getDefault, location)) {
				string number;
				getline(getDefault, number);
				gameboard[stoi(location)].display = number;
			}
		}
	}
	else {
		ifstream getDefault("sudoku0");
		string location;
		while (getline(getDefault, location)) {
			string number;
			getline(getDefault, number);
			gameboard[stoi(location)].display = number;
		}
	}
	print();



}


ostream & operator << (ostream & o, const Sudoku &ggg){
	for (int row = SDK_size - 2; row >= 1; --row){
		o << (row - 1);
		for (int col = 1; col < SDK_size - 1; ++col){
			string temp;
			if (col % 3 == 1)
				temp = "||";
			else
				temp = "|";

			int loc = row * SDK_size + col;
			temp += ggg.gameboard[loc].display;
			o << temp;
		}
		o << "||" << endl;
		if (row != 1)
			o << "-||-|-|-||-|-|-||-|-|-||" << endl;
		else
			o << "=||=|=|=||=|=|=||=|=|=||" << endl;
	}
	o << '#';
	for (int col = 0; col < SDK_size - 2; ++col){
		string temp;
		if (col % 3 == 0)
			temp = "||";
		else
			temp = "|";
		temp += to_string(col);
		o << temp;
	}
	o << "||" << endl;
	return o;

}

void Sudoku::print() {
	cout << *this << endl;
}

bool Sudoku::checkColumn(int vert, int input){
	//checks to see if input value already exists in the column
	for (int i = 1; i < SDK_size - 1; i++) {
		int loc = (SDK_size)*vert + i;

		if (stoi(gameboard[loc].display) == input) {
			return false;
		}
	}
	return true;
}

bool Sudoku::checkRow(int horiz, int input){
	//checks to see if input value already exists in the row
	for (int i = 1; i < SDK_size - 1; i++) {
		int loc = (SDK_size)*i + horiz;

		if (stoi(gameboard[loc].display) == input) {
			return false;
		}
	}
	return true;
}


bool Sudoku::checkSquare(int horiz, int vert, int input){
	//checks to see if input value already exists in the 3 x 3 square
	int vertPos = vert - (vert - 1) % 3;
	int horPos = horiz - (horiz - 1) % 3;

	for (int i = vertPos; i < vertPos + 3; i++) {
		for (int j = horPos; j < horPos + 3; j++) {
			int location = (SDK_size)*i + j;
			if (stoi(gameboard[location].display) == input) {
				return false;
			}
		}
	}
	return true;
}

bool Sudoku::checkUnique(int horiz, int vert, int input) {

	//overall checker to check that value is unique in set of square, row, and col

	//everything must return true
	if (checkColumn(vert, input) && checkRow(horiz, input) && checkSquare(horiz, vert, input)){
		return true;
	}

	return false;

}

bool Sudoku::checkColumnSum(int horiz){
	//set must be lenght 9 since it only holds unique values
	bool ans = true;
	string c = " ";

	for (int i = 1; i < SDK_size - 1; i++) {

		int startLocation = SDK_size*i + horiz;
		if (gameboard[startLocation].display.compare(c) == 0){
			ans = false;
		}
	}

	return ans;
}

bool Sudoku::checkRowSum(int vert){
	//same as checkColumnSum but for rows
	bool ans = true;
	string c = " ";

	for (int i = 1; i < SDK_size - 1; i++) {

		int startLocation = SDK_size*vert + i;
		if (gameboard[startLocation].display.compare(c) == 0){
			ans = false;
		}
	}


	return ans;

}

bool Sudoku::checkSquareSum(){
	//checks surrounding 3 x 3 square
	for (int a = one; a < four; a++){
		for (int b = one; b < four; b++){


			for (int i = one; i < four; i++) {
				for (int j = one; j < four; j++) {
					int startLocation = (SDK_size)*(i + three * a) + (j + three * b);

					if (gameboard[startLocation].display.compare(" ") == 0) {
						return false;
					}


					return true;
				}
			}
		}
	}

	return false;

}

bool Sudoku::done() {
	//checks to see if you've won
	for (int i = 1; i < SDK_size - 1; i++) {
		if (!Sudoku::checkRowSum(i)){
			return false;
		}
	}

	for (int j = 1; j < SDK_size - 1; j++) {
		if (!Sudoku::checkColumnSum(j)){
			return false;
		}
	}

	if (!Sudoku::checkSquareSum()){
		return false;
	}

	//if all of the above conditions do not return true, then you've won
	return true;
}

int Sudoku::turn(){
	unsigned int x, y, num;
	while (true){
		try{
			prompt(x, y, num);
		}
		catch (indicator a){
			if (a == quit_game){
				throw quit_game;
			}
			else if (a == wronginput){
				try{
					prompt(x, y, num);
				}
				catch (indicator b){
					if (b == wronginput){
						return turn();
					}
					else if (b == promptComplete){
						string str = to_string(num);
						if (gameboard[y*dimension + x].letter == None){
							gameboard[y*dimension + x].display = str;
							gameboard[y*dimension + x].position = y*dimension + x;
							this->print();
							turns++;
							return success_move;
							continue;
						}
					}
				}
			}
			else if (a == promptComplete){
				string str = to_string(num);
				if (gameboard[y*dimension + x].letter == None){
					gameboard[y*dimension + x].display = str;
					gameboard[y*dimension + x].position = y*dimension + x;
					this->print();
					turns++;
					return success_move;
					continue;
				}

			}
			else{
				continue;
			}

		}
		catch (...){
			cout << "something wrong happened, please quit and start a new game" << endl;
		}
	}
}

bool Sudoku::draw(){
	return false;
}
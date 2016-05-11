Grader: Lyn Han (lynhan@wustl.edu)

Grade: 97/100

-3 not documenting how work was split


Great job! :)





========================================================================

                  lab3   jinjinqin  chengzhen  t.yin

========================================================================



GameBase.h & GameBase.cpp: GameBase

TicTacToe.h & TicTacToe.cpp: TicTacToe derived from GameBase

GoMoKu.h & GoMoKu.cpp: GoMoKu derived from GameBase



main function:

1. check argc and argv with argCheck:

  1) throw invlid_argc_number, if argc !=2, catch it and call usage_message to give a usage remind

  2) throw null_ptr, if 2nd command is not TicTacToe nor Gomoku, catch it and give a usage remind.

  3) instantiate a TicTacToe or Gomoku game and return the address if command is right.



2. use the address returned to call play().



Play() function:

1. call turn().

   turn function:

     1) use game_name to tell who's turn it is.

     2) call prompt() to get x and y.

        prompt function:

          1) command->string->istringstream->replace "," with " ", extract x and y, check if x and y are 

             in the correct range for different games.

          2) if command is not correct, repeatly to ask the user to enter new command

          3) if "quit" is entered, throw quit_game, catch it in play, cout a remind message, throw quit_game,

             catch it in main function

          4) if command is correct, extract x and y, if failed, return different failure, if succeed, return success_extract

     3) turn get correct x and y or quit_game from prompt.

     4) if it's empty, update it, and print out the gameboard, and update longest_length

     5) cout the player's current move, turns++

2. check if the game is done()/ someone wins(check in 3 dimensions for both games).

3. cout the right winner and return success game

4. check if the game is draw(), cout how many turns and it's a draw game



for gomoku and tictactoe game, the difference is they use different done(), draw(), turn() function,

and they share play(), prompt(), argCheck, setLongestLength().



throw and catch:

1) throw quit_game in prompt, and catch it in play

2) throw quit_game in play if it catches  quit_game, and catch it in main, cout a remind message

and return quit_game

3) throw invalid_argc_number in argcheck, if argc !=2, catch it in main, call usage_message 

to remind a correct format

4) throw null_ptr in argCheck, if the second command is not TicTacToe nor Gomoku, catch it in main

and remind a correct format



tried to change the length of display strings of game_piece:

1.change "X" to "XX" or "XXX"

2.when cout the gameboard, the space width between game_piece changed too

3.for TTT and GMK game, the initial longest_length is 1 and 2, they are different because

the cordinates of GMK game goes to 10 to 19, so it need more space between game_piece.


Sudoku part has different test function with the other two games, also, the content of the game board’s display is not the same.

Also, we used sudoku0 as a test file to test the done function.




copy constructor:

We initialize all the gamepiece in the gameboard with a created default empty gamepiece. 

move constructor:

we didn't use move constructor

copy-assignment operator

We use = to assgin a object to another object of the same class

move-assignment operator

We didn't use that

destructor

There is a default destructor in our previous labs, but we use delete the pointer in the main function to delete all the 

object safely.

*******************************************************************************************************

error:

1. wrong argc number:

>lab3.exe

result: 

Usage:lab3.exe TicTacToe or lab3.exe Gomoku



2. wrong second command

>lab3.exe gomo

result:

Wrong command, enter TicTacToe or Gomoku next to the program name



3. quit_game:

W turn:

Enter the cordinate: <x,y> or <quit>

>quit

The user quits the game

 2 turns were played.

Warning: You quit the game!



4. wrong input command:

O turn:

Enter the cordinate: <x,y> or <quit>

>1,2.0

result:

O turn:

Enter the cordinate: <x,y> or <quit>



5. wrong using getline to get the file content

I changed it using cin to solve this problem







*********************************************************************************************************






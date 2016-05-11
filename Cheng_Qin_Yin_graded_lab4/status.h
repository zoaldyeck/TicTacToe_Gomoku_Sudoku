#ifndef STATUS_H
#define STATUS_H
#include "stdafx.h"
//all the status
enum indicator{
	success_game, invalid_argc_number, quit_game, extract_x_failure, extract_y_failure, success_extract_x_y,
	success_move, failure_move, draw_game, unexpected_failure, second_input_wrong, null_ptr, promptComplete, wronginput, unknown_failure, not_null_ptr
};
enum number {
	one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, eleven = 11, twelve = 12, thirteen = 13,
	fourteen = 14, fifteen = 15, sixteen = 16, seventeen = 17, eighteen = 18
};
enum index{ program_index, game_index };
enum argc_num { valid_argc = 2 };



#endif
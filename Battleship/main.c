/*******************************************************************************************

* Programmer: Frederick Chen                                                                        

* Class: Cpt S 121, Spring 2011; Lab Section 1                                              

* Programming Assignment: PA 6                                                        

* Date: April 4, 2011             

*Due Date: April 4, 2011 

*TA: Paul Wettin

* Description: This program is a game called battleship where two players have two boards and
				have ships to place on the board then keep shooting each other until all the 
				ships are sunk.


*******************************************************************************************/

#include "functions.h"

int main (void)
{
	char game_board1[NUM_ROWS][NUM_COLS], game_board2[NUM_ROWS][NUM_COLS], ship_char[5] = {'c', 'b', 's', 'r', 'd'};

	int ship_length[5] = {5,4,3,3,2};

	Stats player1_stats = {0, 0, 0, 0.0}, player2_stats = {0, 0, 0, 0.0};

	FILE *outfile = NULL;
	
	srand (time(NULL));
	
	outfile = fopen("battleship.log", "w");

	print_menu (game_board1, game_board2, ship_length, ship_char, outfile, &player1_stats, &player2_stats);

	output_stats (outfile, &player1_stats, &player2_stats);

	return 0;
}
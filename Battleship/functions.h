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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 10
#define NUM_COLS 10

typedef struct stats
{
	int num_misses;
	int num_hits;
	int total_num_shots;
	double hits_miss_ratio; 
} Stats;

void print_menu (char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS], int ship_length[5], char ship_symbol[5], FILE *outfile, Stats *player1_stats, Stats *player2_stats);

void print_rules(void);

void initialize_boards (char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS]);

void print_boards (char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS]);

void manually_place_ships_on_board(char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS], int ship_length[5], char ship_symbol[5]);

void randomly_place_ships_on_board(char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS], int ship_length[5], char ship_symbol[5]);

void check_shot(char game_board[NUM_ROWS][NUM_COLS], int *row, int *col);

int generate_direc (void);

void generate_starting_pt (int *row, int *col, int directions, int ship_length);

void place_ship(char game_board[NUM_ROWS][NUM_COLS], int row, int col, int ship_length, char ship_symbol, int direction);

int check_collisions (char board[NUM_ROWS][NUM_COLS], int row, int col, int ship_length[5], int direction);

void player_shoot(char game_board[NUM_ROWS][NUM_COLS], int *row, int *col);

void easy_ai(char board[NUM_ROWS][NUM_COLS], int *row, int *col);

void output_current_move(FILE *outfile, int *row, int *col, int player, char game_board[NUM_ROWS][NUM_COLS], Stats *player_stats);

void check_if_sunk_ship(char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS], int *statc1, int *statb1, int *stats1, int *statr1, int *statd1, int *statc2, int *statb2, int *stats2, int *statr2, int *statd2, FILE *outfile, int *sunk, int *miss1, int *miss2, int *miss3, int *miss4, int *initial, Stats *player_stats, int *count_up, int *count_down, int *count_left, int *count_right);

int is_winner(int *statc1, int *statb1, int *stats1, int *statr1, int *statd1, int *statc2, int *statb2, int *stats2, int *statr2, int *statd2);

int select_who_starts_first(void);

void output_stats (FILE *outfile, Stats *player1_stats, Stats *player2_stats);

void impossible_ai(char game_board[NUM_ROWS][NUM_COLS], int *row, int *col);

void moderate_ai (char game_board[NUM_ROWS][NUM_COLS], int *row, int *col, Stats *player_stats, int *sunk, int *miss1, int *miss2, int *miss3, int *miss4, int *count_up, int *count_down, int *count_left, int *count_right, int *initial);

void hard_ai (char game_board[NUM_ROWS][NUM_COLS], int *row, int *col, Stats *player_stats, int *sunk, int *miss1, int *miss2, int *miss3, int *miss4, int *count_up, int *count_down, int *count_left, int *count_right, int *initial, int *camouflage);

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

/*************************************************************
 * Function: print_menu()                                    *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Print the menu screen of the game Battleship *
 * Input parameters: none                                    *
 * Returns: none                                             *
 * Preconditions: program must be executed			         *
 * Postconditions: diplays the menu screen                   *
 *************************************************************/
void print_menu (char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS], int ship_length[5], char ship_symbol[5], FILE *outfile, Stats *player1_stats, Stats *player2_stats)
{
	int menu = 0, option = 0, order = 0;
	int c1 = 0, b1 = 0, s1 = 0, r1 = 0, d1 = 0;
	int c2 = 0, b2 = 0, s2 = 0, r2 = 0, d2 = 0;
	int row = 0, col = 0, winner = 0, difficulty = 0, sunk = 0, row2 = 0, col2 = 0;
	int miss1 = 0, miss2 = 0, miss3 = 0, miss4 = 0;
	int count_up = 0, count_down = 0, count_left = 0, count_right = 0;
	int initial = 0, camouflage = 0;

	camouflage = rand() % 2;

	do
	{
	system("cls");

	printf("*****Battleship*****\n\n");

	printf("1. Read Battleship Rules\n2. Play Battleship\n3. Exit Game\n\n");

	printf("Please enter the game option you want to choose = ");

	scanf("%d", &menu);

	switch (menu)
	{	
	
		case 1: 
	
		print_rules();

			break;

		case 2: 
			//I would have created a battleship function to contain all this but there wasn't enough time
			initialize_boards (board1, board2);

			do
			{
			system("cls");

			printf("****Ship Placements****\n\n");

			printf("1. Manually Place Ship on Board.\n2. Randomly Place Ships on Board\n");

			printf("Please enter the game option you want to choose = ");

			scanf("%d", &option);

			switch (option)
			{
			case 1: 
				manually_place_ships_on_board(board1, board2, ship_length, ship_symbol);

				break;
			case 2:	
				randomly_place_ships_on_board(board1, board2, ship_length, ship_symbol);

					break;

			default: printf("Invalid Operation");

					 system("pause");
				break;
			}
			}while((option != 1) && (option != 2));

			system("cls");

			printf("****Difficulty Level****\n\n");

			printf("1. Easy.\n2. Moderate\n3. Hard\n4. Impossible\n");

			printf("Please enter the game difficulty you want to choose = ");

			scanf("%d", &difficulty);

			order = select_who_starts_first();
		
			print_boards (board1, board2);

			if(order == 0)
			{
				printf("Player 1 has been randomly selected to go first.\n");

				system("pause");

			do
			{
			player_shoot(board2, &row, &col);

			check_shot(board2, &row, &col);

			output_current_move(outfile, &row, &col, 1, board2, player1_stats);

			check_if_sunk_ship(board1, board2, &c1, &b1, &s1, &r1, &d1, &c2, &b2, &s2, &r2, &d2, outfile, &sunk, &miss1, &miss2, &miss3, &miss4, &initial, player2_stats, &count_up, &count_down, &count_left, &count_right);

			system("pause");

			system("cls");

			print_boards (board1, board2);

			system("pause");

			if(difficulty == 1)
			{
				easy_ai(board1, &row2, &col2);
			}
			if(difficulty == 2)
			{
				moderate_ai(board1, &row2, &col2, player2_stats, &sunk, &miss1, &miss2, &miss3, &miss4, &count_up, &count_down, &count_left, &count_right, &initial);
			}
			if(difficulty == 3)
			{
				hard_ai(board1, &row2, &col2, player2_stats, &sunk, &miss1, &miss2, &miss3, &miss4, &count_up, &count_down, &count_left, &count_right, &initial, &camouflage);
			}
			if(difficulty == 4)
			{
				impossible_ai(board1, &row2, &col2);
			}

			check_shot(board1, &row2, &col2);

			output_current_move(outfile, &row2, &col2, 2, board1, player2_stats);

			check_if_sunk_ship(board1, board2, &c1, &b1, &s1, &r1, &d1, &c2, &b2, &s2, &r2, &d2, outfile, &sunk, &miss1, &miss2, &miss3, &miss4, &initial, player2_stats, &count_up, &count_down, &count_left, &count_right);

			system("pause");

			system("cls");

			print_boards (board1, board2);
			
			system("pause");

			winner = is_winner(&c1, &b1, &s1, &r1, &d1, &c2, &b2, &s2, &r2, &d2);

			}while (!winner);
			}
			if(order == 1)
			{
				printf("Player 2 has been randomly selected to go first.\n");

			do
			{
			system("pause");

			if(difficulty == 1)
			{
				easy_ai(board1, &row2, &col2);
			}
			if(difficulty == 2)
			{
				moderate_ai(board1, &row2, &col2, player2_stats, &sunk, &miss1, &miss2, &miss3, &miss4, &count_up, &count_down, &count_left, &count_right, &initial);
			}
			if(difficulty == 3)
			{
				hard_ai(board1, &row2, &col2, player2_stats, &sunk, &miss1, &miss2, &miss3, &miss4, &count_up, &count_down, &count_left, &count_right, &initial, &camouflage);
			}
			if(difficulty == 4)
			{
				impossible_ai(board1, &row2, &col2);
			}

			check_shot(board1, &row2, &col2);

			output_current_move(outfile, &row2, &col2, 2, board1, player2_stats);

			check_if_sunk_ship(board1, board2, &c1, &b1, &s1, &r1, &d1, &c2, &b2, &s2, &r2, &d2, outfile, &sunk, &miss1, &miss2, &miss3, &miss4, &initial, player2_stats, &count_up, &count_down, &count_left, &count_right);

			system("pause");

			system("cls");

			print_boards (board1, board2);

			player_shoot(board2, &row, &col);

			check_shot(board2, &row, &col);

			output_current_move(outfile, &row, &col, 1, board2, player1_stats);

			check_if_sunk_ship(board1, board2, &c1, &b1, &s1, &r1, &d1, &c2, &b2, &s2, &r2, &d2, outfile, &sunk, &miss1, &miss2, &miss3, &miss4, &initial, player2_stats, &count_up, &count_down, &count_left, &count_right);

			system("pause");

			system("cls");

			print_boards (board1, board2);

			system("pause");
		
			winner = is_winner(&c1, &b1, &s1, &r1, &d1, &c2, &b2, &s2, &r2, &d2);

			}while (!winner);
			}
				
			system("cls");

			printf("The winner is ...\n");

			system("pause");

			if(winner == 1)
			{
				printf("Player 1!!!");

				system("pause");
			}

			if(winner == 2)
			{
				printf("Player 2!!!");

				system("pause");
			}

	break;

		case 3: 
			
			system("cls");

			printf("Goodbye!\n");

			break;

		default:

			system("cls");

			printf("Please enter a valid operation\n");
			
			system("pause");

			break;
	}

	}while (menu != 3);

}

/*************************************************************
 * Function: print_rules()                                   *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Displays the rules of the game Battleship	 *
 * Input parameters: none                                    *
 * Returns: none                                             *
 * Preconditions: program must be executed			         *
 * Postconditions: diplays the rule screen                   *
 *************************************************************/

void print_rules(void)
{
	printf("Rules of the Game:\n1. This is a two player game.\n2. Player1 is you and Player2 is the computer.\n(one shot in a turn)\n\nSET UP THE FLEET\nI. Two players sit FACING EACH OTHER, each with his kit on the fable in front of him. They open their BARRIER LIDS so they cannot see the OCEAN GRID of their \nopponents kit. The lids are kept open all during the playing of the game.\n2. Each player SECRETLY places his fleet of 5 ships on his OCEAN GRID. The \nBOTTOM of each ship has two anchoring pegs which must be pushed THROUGH the holes in the OCEAN GRID for placing them, Ships may be placed in ANY HORIZONTAL (back and forth) or VERTICAL (up and down) position - but NOT DIAGONALLY. The ships anchoring pegs will NOT fit in the grid holes if placed diagonally. All holes on the TOP of the SHIPS must be lined up over holes on the OCEAN GRID. DO NOT place a ship so that a part of it is overhanging the grid holes or over letters and numbers.\n3. When both players have placed their 5 ships as desired, they announce READY. From then on, during the game, they MAY NOT change the position of any ship. To do so would be cheating!\n\nCALL OUT THE SHOTS\nIn this BASIC Game, the players call out ONE shot each turn to try to hit an opponents ship.\nI. The player with the RED kit fakes the first shot. Players then alternate, taking one shot at a time (red, blue, red, etc.).\n2. A shot is made by calling a LETTER and a NUMBER to locate which hole in the opponents OCEAN GRID that shot is to be placed. That hole is located by going straight across, horizontally, from the called LETTER (printed on the side) and down, vertically, from the called NUMBER (printed across the top). The diagrams below show examples of how shots are located. The black dot shows where the shot is placed.");

	printf("\n3. When a shot is called, the opponent immediately tells, the player whether it s a hit or miss. If is a hit if the called hole on his OCEANGRID is covered by a ship; and a miss if no ship occupies that hole. If the shot is a hit, the opponent fells the player what KIND of SHIP was hit (cruiser, carrier, etc.)\n\nMARK SHOTS WITH PEGS\n1.After a player has called his shot and found out whether it s a hit or miss, he places a marker peg in his TARGET GRID (the one in the lid) -a WHITE peg for a miss and a RED peg for a hit, to mark the location of that shot. This will guide him in placing future shots and prevent him from calling the same holes more than once.\n2. A player does not have to mark his opponents misses with white pegs, but, he MUST MARK any hits that the opponent makes on his ships with a RED peg. When a hit has been made on a players ship, he places a RED peg in the SHIP at that location on his OCEAN GRID.\n\nSINK THE FLEET\n1. Players continue taking turns, Calling shots and marking them.\n2. Whenever a ship has received enough hits to fill all of ifs holes with RED PEGS, if is SUNK and is removed from the OCEAN GRID. The player whose ship is sunk must announce if to his opponent.\n3. The number of hits each ship must receive to be SUNK is as follows: Carrier - 5 hits, Battleship - 4 hits, Cruiser - 3 hits, Submarine - 3 hits, Destroyer - 2 hits.\n4. It is expected that players will be HONEST in announcing hits when they are made. Occasionally players may make a mistake in calling a hole they didn't mean or in locating the correct hole called. If a player feels an error has been made, he may call a TRUCE - and stop the game temporarily to review shots he has made in past turns. He can easily do this by calling out the location of the pegs he has placed on his TARGET GRID and asking the opponent to verify the hits and misses he has marked.");

	printf("\n\nWIN THE GAME\nThe first player to sink all 5 of his opponent's ships is the WINNER.\n");

	system("pause");
}

/*************************************************************
 * Function: initialize_boards()                             *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Initialize the game boards					 *
 * Input parameters: char board1 & 2                         *
 * Returns: none                                             *
 * Preconditions: Board1 & 2 must be a 2D array		         *
 * Postconditions: '~' is replaced for all cells             *
 *************************************************************/

void initialize_boards (char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS])
{
	int row_index1 = 0, col_index1 = 0;
	int row_index2 = 0, col_index2 = 0;

	for (row_index1 = 0; row_index1 < NUM_ROWS; row_index1++)
	{
		for (col_index1 = 0; col_index1 < NUM_COLS; col_index1++)
		{
			board1[row_index1][col_index1] = '~';
		}
	}

	for (row_index2 = 0; row_index2 < NUM_ROWS; row_index2++)
	{
		for (col_index2 = 0; col_index2 < NUM_COLS; col_index2++)
		{
			board2[row_index2][col_index2] = '~';
		}
	}
}

/*************************************************************
 * Function: print_boards()                                  *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Print the game boards of the game Battleship *
 * Input parameters: char board1 & 2                         *
 * Returns: none                                             *
 * Preconditions: Board1 & 2 must be a 2D array			     *
 * Postconditions: diplays the game boards                   *
 *************************************************************/

void print_boards (char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS])
{
	int row_index1 = 0, col_index1 = 0;
	int row_index2 = 0, col_index2 = 0;
	int count;

	system("cls");

	printf ("****player 1 board****\n%3d", 0);

	for (count = 1; count < NUM_ROWS; count++)
	{
		printf("%2d", count);
	}

		putchar ('\n');

	for (row_index1 = 0; row_index1 < NUM_ROWS; row_index1++)
	{
		printf ("%d ", row_index1);

		for (col_index1 = 0; col_index1 < NUM_COLS; col_index1++)
		{
			printf ("%c ", board1[row_index1][col_index1]);
		}
		putchar('\n');
	}

	printf ("****player 2 board****\n%3d", 0);

	for (count = 1; count < NUM_ROWS; count++)
	{
		printf("%2d", count);
	}

		putchar ('\n');

	for (row_index2 = 0; row_index2 < NUM_ROWS; row_index2++)
	{
		printf ("%d ", row_index2);
		for (col_index2 = 0; col_index2 < NUM_COLS; col_index2++)
		{
			
			if (board2[row_index2][col_index2] == 'o' || board2[row_index2][col_index2] == '*')
			{
			
			printf ("%c ", board2[row_index2][col_index2]);
		
			}

			else
			{
				printf("~ ");
			}
		}
		putchar ('\n');
	}
}

/*************************************************************
 * Function: manually_place_ships_on_board()                 *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Prompts the user to manually place ships on  *
 *				the game board.								 *
 * Input parameters: char board1 & 2 & ship symbol           *
 *					 int ship_length						 *
 * Returns: none                                             *
 * Preconditions: ship length and ship symbols are available *
 * Postconditions: Ship symbols should replace the cells     *
 *************************************************************/

void manually_place_ships_on_board(char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS], int ship_length[5], char ship_symbol[5])
{
int direction, row, col, index = 0, status = 0, off_board = 0;

do
{
do
{
	off_board = 0;

	status = 0;

	system("cls");

	print_boards (board1, board2);

if (index == 0)
{
	printf("\nCarrier Placement\n");
}
if (index == 1)
{
	printf("Battleship Placement\n");
}
if (index == 2)
{
	printf("Submarine Placement\n");
}
if (index == 3)
{
	printf("Cruiser Placement\n");
}
if (index == 4)
{
	printf("Destroyer Placement\n");
}

printf("0. Horizontal\n1. Vertical\nPlease enter the direction you want: ");

scanf("%d", &direction);

printf("\nNOTE: Please enter the starting point only, the ships will go from left to right if you picked horizontal and from up top to bottom if you picked vertical\n\n");

printf("Please enter the row and column of the starting point: ");

scanf("%d %d", &row, &col);

if (direction == 0)
{
	if((ship_length[index] + col) > 10)
	{
	off_board = 1;

	printf("\nInvalid Placement");

	system("pause");
	}
}
if (direction == 1)
{
	if((ship_length[index] + row) > 10)
	{
	off_board = 1;

	printf("\nInvalid Placement");

	system("pause");
	}
}
status = check_collisions(board1, row, col, ship_length[index], direction);

}while ((status == 1) || (off_board == 1));

place_ship(board1, row, col, ship_length[index], ship_symbol[index], direction);

index++;

}while (index < 5);

index = 0;

do
{
do
{
direction = generate_direc();
 
generate_starting_pt (&row, &col, direction, ship_length[index]);

status = check_collisions(board2, row, col, ship_length[index], direction);

}while (status == 1);

place_ship(board2, row, col, ship_length[index], ship_symbol[index], direction);

index++;

}while (index < 5);

system("pause");

}

/*************************************************************
 * Function: randomly_place_ships_on_board()                 *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Randomly place ships on the game board.		 *
 * Input parameters: char board1 & 2 & ship symbol           *
 *					 int ship_length						 *
 * Returns: none                                             *
 * Preconditions: ship length and ship symbols are available *
 * Postconditions: Ship symbols should replace the cells     *
 *************************************************************/

void randomly_place_ships_on_board(char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS], int ship_length[5], char ship_symbol[5])
{
int direction, row, col, index = 0, status = 0;
do
{
do
{
direction = generate_direc();

generate_starting_pt (&row, &col, direction, ship_length[index]);

status = check_collisions(board1, row, col, ship_length[index], direction);

}while (status == 1);

place_ship(board1, row, col, ship_length[index], ship_symbol[index], direction);

index++;

}while (index < 5);

index = 0;

do
{
do
{
direction = generate_direc();

generate_starting_pt (&row, &col, direction, ship_length[index]);

status = check_collisions(board2, row, col, ship_length[index], direction);

}while (status == 1);

place_ship(board2, row, col, ship_length[index], ship_symbol[index], direction);

index++;

}while (index < 5);

}

/*************************************************************
 * Function: generate_direc()				                 *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Randomly generates a direction				 *
 * Input parameters: none									 *
 * Returns: none                                             *
 * Preconditions: Rand() must be available					 *
 * Postconditions: A valid starting point should be generated*
 *************************************************************/

int generate_direc (void)
{
	int direction = 0;

	direction = rand () % 2;

	return direction;
}

/*************************************************************
 * Function: generate_starting_pt()			                 *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Randomly generates a starting point			 *
 * Input parameters: int *row, *col, direction, ship length  *
 * Returns: none                                             *
 * Preconditions:Direction and ship length must be available *
 * Postconditions: A valid starting point should be generated*
 *************************************************************/

void generate_starting_pt (int *row, int *col, int directions, int ship_length)
{
	if (directions == 0 )
		// horizontal
	{
		*row = rand () % 10;
		*col = rand () % ((10 - ship_length) + 1);
	}
	else
		// vertical
	{
		*row = rand () % ((10 - ship_length) + 1);
		*col = rand () % 10;
	}
}

/*************************************************************
 * Function: place_ship()					                 *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Places ships on the game board				 *
 * Input parameters: int row, col, direction, ship length    *
 *					 char game board, ship symbol			 *
 * Returns: none                                             *
 * Preconditions:Row, col, game board, and all parameters    *
 *				 must be available							 *
 * Postconditions: The ship symbol should replace the cell	 *
 *************************************************************/

void place_ship(char game_board[NUM_ROWS][NUM_COLS], int row, int col, int ship_length, char ship_symbol, int direction)
{
	int index = 0;
	
	if (direction == 0)
	{
		for (index = 0; index < ship_length; index++)
		{
			game_board[row][col + index] = ship_symbol;
		}
	}

	else
	{
		for (index = 0; index < ship_length; index++)
		{
			game_board[row + index][col] = ship_symbol;
		}
	}

}

/*************************************************************
 * Function: check_collisions()				                 *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Checks if ships collide with each other		 *
 * Input parameters: char board, int row, col, ship length   *
 *					 , and direction						 *
 * Returns: none                                             *
 * Preconditions: The board must have ships on it and have   *
 *				  coordinates of the ships that's going to be*
 *				  placed									 *
 * Postconditions: No collisions should happen				 *
 *************************************************************/

int check_collisions (char board[NUM_ROWS][NUM_COLS], int row, int col, int ship_length, int direction)
{
	int index = 0, status = 0;

	for (index = 0; index < ship_length; index++)
	{
		if (direction == 0)
		{
			if (board[row][col + index] != '~')
			{
				status = 1;
			}
		}
		else 
		{
			if (board[row + index][col] != '~')
			{
				status = 1;
			}
		}
	}

	return status;
}

/*************************************************************
 * Function: select_who_starts_first()		                 *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Places ships on the game board				 *
 * Input parameters: int row, col, direction, ship length    *
 *					 char game board, ship symbol			 *
 * Returns: none                                             *
 * Preconditions:Row, col, game board, and all parameters    *
 *				 must be available							 *
 * Postconditions: A valid starting point should be generated*
 *************************************************************/

//This function is not really necessary because this can be done within the original function

int select_who_starts_first(void)
{
int decision;

decision = rand() % 2;

//if 0 player 1 starts

//if 1 player 2 starts

return decision;
}

/*************************************************************
 * Function: player_shoot()					                 *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Prompts the player to pick a coordinate to   *
 *				shoot at									 *
 * Input parameters: int row, col, char game_board		     *
 * Returns: none                                             *
 * Preconditions:Row, col, game board must be available		 *
 * Postconditions: The coordinate chosen should display is it*
 *					was a hit or miss						 *
 *************************************************************/

void player_shoot(char game_board[NUM_ROWS][NUM_COLS], int *row, int *col)
{
	int shot_row = 0, shot_col = 0;

	do
	{
		printf("Player 1's turn\n");

	printf("Please enter the coordinate you want to shoot (Row then Column): ");

	scanf("%d %d", &shot_row, &shot_col);

	if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '*' || shot_row >= 10 || shot_col >= 10)
	{
		printf("Invalid Point\n");
	}
	
	}while (game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '*' || shot_row >= 10 || shot_col >= 10);
	
	*row = shot_row;

	*col = shot_col;
}

/*************************************************************
 * Function: rand_computer_shoot()				             *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Randomly pick a coordinate to shoot at		 *
 * Input parameters: int row, col, char game_board		     *
 * Returns: none                                             *
 * Preconditions: Row, col, game board must be available	 *
 * Postconditions: The coordinate chosen should display is it*
 *					was a hit or miss						 *
 *************************************************************/

void easy_ai(char game_board[NUM_ROWS][NUM_COLS], int *row, int *col)
{
	int shot_row = 0, shot_col = 0;
	
	do
	{
		shot_row = rand() % 10;
		shot_col = rand() % 10;

	}while (game_board[shot_row][shot_col] == '*' || game_board[shot_row][shot_col] == 'o');
	
	printf("\nComputer's Shoot: %d, %d", shot_row, shot_col);

	*row = shot_row;

	*col = shot_col;
}

/*************************************************************
 * Function: check_if_sunk_ship()				             *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Checks if ship was sunk by a shot			 *
 * Input parameters: char board1 & 2, int *statc1, *statb1,  *
 *					 *stats1, *statr1, *statd1, *statc2,	 *
 *					 *statb2, *stats2, *statr2, *statd2,	 *
 *					 FILE *outfile						     *
 * Returns: none                                             *
 * Preconditions: Everything has to be available			 *
 * Postconditions: Displays if a ship was sunk or not		 *
 *************************************************************/

void check_if_sunk_ship(char board1[NUM_ROWS][NUM_COLS], char board2[NUM_ROWS][NUM_COLS], int *statc1, int *statb1, int *stats1, int *statr1, int *statd1, int *statc2, int *statb2, int *stats2, int *statr2, int *statd2, FILE *outfile, int *sunk, int *miss1, int *miss2, int *miss3, int *miss4, int *initial, Stats *player_stats, int *count_up, int *count_down, int *count_left, int *count_right)
{
	int c1 = 0, b1 = 0, s1 = 0, r1 = 0, d1 = 0;
	int c2 = 0, b2 = 0, s2 = 0, r2 = 0, d2 = 0;
	int row_index = 0, col_index = 0;

	for (row_index = 0; row_index < NUM_ROWS; row_index++)
	{
		for (col_index = 0; col_index < NUM_COLS; col_index++)
		{
			if(board1[row_index][col_index] == 'c')
			{
				c1 = 1;
			}
			if(board1[row_index][col_index] == 'b')
			{
				b1 = 1;
			}
			if(board1[row_index][col_index] == 's')
			{
				s1 = 1;
			}
			if(board1[row_index][col_index] == 'r')
			{
				r1 = 1;
			}
			if(board1[row_index][col_index] == 'd')
			{
				d1 = 1;
			}
			if(board2[row_index][col_index] == 'c')
			{
				c2 = 1;
			}
			if(board2[row_index][col_index] == 'b')
			{
				b2 = 1;
			}
			if(board2[row_index][col_index] == 's')
			{
				s2 = 1;
			}
			if(board2[row_index][col_index] == 'r')
			{
				r2 = 1;
			}
			if(board2[row_index][col_index] == 'd')
			{
				d2 = 1;
			}

			
		}
	}
			
			if(c1 != 1 && *statc1 == 0)
			{
				printf("\nPlayer 1's Carrier was sunk!!");

				fprintf(outfile, "\nPlayer 1's Carrier was sunk.\n\n");

				*statc1 = 1;

				*sunk = 1;

				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;

				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;

				*initial = player_stats->num_hits;
			}
			if(b1 != 1 && *statb1 == 0)
			{
				printf("\nPlayer 1's Battleship was sunk!!");

				fprintf(outfile, "\nPlayer 1's Battleship was sunk.\n\n");

				*statb1 = 1;

				*sunk = 1;

				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;
				
				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;

				*initial = player_stats->num_hits;
			}
			if(s1 != 1 && *stats1 == 0)
			{
				printf("\nPlayer 1's Submarine was sunk!!");

				fprintf(outfile, "\nPlayer 1's Submarine was sunk.\n\n");

				*stats1 = 1;

				*sunk = 1;

				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;

				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;

				*initial = player_stats->num_hits;
			}
			if(r1 != 1 && *statr1 == 0)
			{
				printf("\nPlayer 1's Cruiser was sunk!!");

				fprintf(outfile, "\nPlayer 1's Cruiser was sunk.\n\n");

				*statr1 = 1;

				*sunk = 1;

				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;

				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;

				*initial = player_stats->num_hits;
			}
			if(d1 != 1 && *statd1 == 0)
			{
				printf("\nPlayer 1's Destroyer was sunk!!");

				fprintf(outfile, "\nPlayer 1's Destroyer was sunk.\n\n");

				*statd1 = 1;

				*sunk = 1;

				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;

				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;

				*initial = player_stats->num_hits;
			}
			if(c2 != 1 && *statc2 == 0)
			{
				printf("\nPlayer 2's Carrier was sunk!!");

				fprintf(outfile, "\nPlayer 2's Carrier was sunk.\n\n");

				*statc2 = 1;
			}
			if(b2 != 1 && *statb2 == 0)
			{
				printf("\nPlayer 2's Battleship was sunk!!");

				fprintf(outfile, "\nPlayer 2's Battleship was sunk.\n\n");

				*statb2 = 1;
			}
			if(s2 != 1 && *stats2 == 0)
			{
				printf("\nPlayer 2's Submarine was sunk!!");

				fprintf(outfile, "\nPlayer 2's Submarine was sunk.\n\n");

				*stats2 = 1;
			}
			if(r2 != 1 && *statr2 == 0)
			{
				printf("\nPlayer 2's Cruiser was sunk!!");

				fprintf(outfile, "\nPlayer 2's Cruiser was sunk.\n\n");

				*statr2 = 1;
			}
			if(d2 != 1 && *statd2 == 0)
			{
				printf("\nPlayer 2's Destroyer was sunk!!");

				fprintf(outfile, "\nPlayer 2's Destroyer was sunk.\n\n");

				*statd2 = 1;
			}
}

/*************************************************************
 * Function: is_winner()						             *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: determines the winner				 		 *
 * Input parameters: int *statc1, *statb1, *statr2, *statd2, *
 *					 *stats1, *statr1, *statd1, *statc2,	 *
 *					 *statb2, *stats2 						 *
 * Returns: int winner                                       *
 * Preconditions: The conditions of the ships must be present*
 * Postconditions: The winner will be chosen				 *
 *************************************************************/

int is_winner(int *statc1, int *statb1, int *stats1, int *statr1, int *statd1, int *statc2, int *statb2, int *stats2, int *statr2, int *statd2)
{
	int winner = 0;

	if(*statc1 == 1 && *statb1 == 1 && *stats1 == 1 && *statr1 == 1 && *statd1 == 1)
	{
		winner = 2;
	}

	if(*statc2 == 1 && *statb2 == 1 && *stats2 == 1 && *statr2 == 1 && *statd2 == 1)
	{
		winner = 1;
	}

	return winner;
}

/*************************************************************
 * Function: output_current_move()				             *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Prints the coordinates of the shot into		 *
 *				battleship.log								 *
 * Input parameters: int row, col, player, char game_board   *
 *					 FILE *outfile, Stats *player_stats		 *
 * Returns: none                                             *
 * Preconditions: battleship.log must be opened for writing	 *
 * Postconditions: The coordinate chosen should be written in*
 *				   battleship.log							 *
 *************************************************************/

void output_current_move(FILE *outfile, int *row, int *col, int player, char game_board[NUM_ROWS][NUM_COLS], Stats *player_stats)
{
	fprintf(outfile, "Player %d's Move: (%d, %d)", player, *row, *col);

	if (game_board[*row][*col] == '*')
	{
		fprintf(outfile,"\nHit\n");

		(*player_stats).num_hits++;
	}
	if (game_board[*row][*col] == 'o')
	{
		fprintf(outfile,"\nMiss\n");

		(*player_stats).num_misses++;
	}

	(*player_stats).total_num_shots++;

	player_stats->hits_miss_ratio = (player_stats->num_hits) / ((double)player_stats->num_misses);
}

/*************************************************************
 * Function: outputs_stats()					             *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: Prints the statistics of both players  		 *
 * Input parameters: FILE *outfile, Stats player1 & 2		 *
 * Returns: none                                             *
 * Preconditions: battleship.log must be opened for writing	 *
 * Postconditions: The statistics of the two players should  *
 *				   be written in battleship.log				 *
 *************************************************************/

void output_stats (FILE *outfile, Stats *player1_stats, Stats *player2_stats)
{
	fprintf(outfile, "\nPlayer 1 Statistics:\nNumber of Hits: %d\nNumber of Misses: %d\nTotal Shots: %d\nHit/Miss Ratio: %lf\n", player1_stats->num_hits, player1_stats->num_misses, player1_stats ->total_num_shots, player1_stats->hits_miss_ratio);

	fprintf(outfile, "\nPlayer 2 Statistics:\nNumber of Hits: %d\nNumber of Misses: %d\nTotal Shots: %d\nHit/Miss Ratio: %lf\n", player2_stats->num_hits, player2_stats->num_misses, player2_stats ->total_num_shots, player2_stats->hits_miss_ratio);
}

/*************************************************************
 * Function: cheat_computer_shoot()				             *
 * Date Created: April 3, 2011	                             *
 * Date Last Modified: April 3, 2011	                     *
 * Description: An impossible ai to beat unless you cheat too*
 * Input parameters: char game_board, int *row, *col		 *
 * Returns: none                                             *
 * Preconditions: Game board must be available				 *
 * Postconditions: The coordinate chosen should display it   *
 *					was a hit								 *
 *************************************************************/

void impossible_ai(char game_board[NUM_ROWS][NUM_COLS], int *row, int *col)
{
	int shot_row = 0, shot_col = 0, row_index = 0, col_index = 0;

	for (row_index = 0; row_index < NUM_ROWS; row_index++)
	{
		for (col_index = 0; col_index < NUM_COLS; col_index++)
		{
			if(game_board[row_index][col_index] == 'c' || game_board[row_index][col_index] == 'b' || game_board[row_index][col_index] == 's' || game_board[row_index][col_index] == 'r' || game_board[row_index][col_index] == 'd')
			{
				shot_row = row_index;

				shot_col = col_index;
			}
		}
	}

	printf("\nComputer's Shoot: %d, %d", shot_row, shot_col);

	*row = shot_row;

	*col = shot_col;
}

void moderate_ai (char game_board[NUM_ROWS][NUM_COLS], int *row, int *col, Stats *player_stats, int *sunk, int *miss1, int *miss2, int *miss3, int *miss4, int *count_up, int *count_down, int *count_left, int *count_right, int *initial)
{
	int shot_row = 0, shot_col = 0;

	int num_downs = 0, num_rights = 0;

		if (player_stats->num_hits > *initial && *miss1 == 0 && *sunk != 1)
		{
			shot_row = (*row - 1);
			shot_col = *col;

			*count_up = *count_up + 1;
		
			if(game_board[shot_row][shot_col] == 'o' || shot_row < 0 || game_board[shot_row][shot_col] == '~')
			{
				*miss1 = 1;
			}
			if(game_board[shot_row][shot_col] == '*')
			{
				do
				{
				shot_row--;

				*count_up = *count_up + 1;

				}while (game_board[shot_row][shot_col] == '*' && shot_row >= 0);

				if(game_board[shot_row][shot_col] == '~' || game_board[shot_row][shot_col] == 'o' || shot_row < 0)
				{
					*miss1 = 1;
				}
					
				if (shot_row < 0 || game_board[shot_row][shot_col] =='o')
				{
						do
						{
							shot_row++;

							num_downs++;
						}while(num_downs < 10 && (shot_row < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss2 = 1;
					}
					else if (game_board[shot_row][shot_col] != 'o' && game_board[shot_row][shot_col] != '~' && game_board[shot_row][shot_col] != '*')
					{
						*count_up = 0;

						*count_down = *count_down + 1;
					}

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						shot_row = shot_row - num_downs + *count_up;
						shot_col = shot_col - 1;
						
						*count_left = *count_left + 1;
					}

							if(game_board[shot_row][shot_col] == '*')
							{
								do
								{
									shot_col--;

									*count_left = *count_left + 1;

								}while (game_board[shot_row][shot_col] == '*' && shot_col >= 0);							

								if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '~' || shot_col < 0)
								{
									*miss3 = 1;
								}
								
								if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
								{
									do
									{
									shot_col++;

									num_rights++;

									}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

									if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
									{
										*miss4 = 1;
									}

									if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
									{
										*miss1 = 0;
										*miss2 = 0;
										*miss3 = 0;
										*miss4 = 0;

										*count_up = 0;
										*count_down = 0;
										*count_left = 0;
										*count_right = 0;

										*initial = player_stats->num_hits;
									}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
								}
							}
				}
			}				
					
			if (shot_row < 0 || game_board[shot_row][shot_col] =='o')
			{
					do
					{
						shot_row++;

						num_downs++;

					}while(num_downs < 10 && (shot_row < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss2 = 1;
					}
					else if (game_board[shot_row][shot_col] != 'o' && game_board[shot_row][shot_col] != '~' && game_board[shot_row][shot_col] != '*')
					{
						*count_up = 0;
					}


					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						shot_row = shot_row - num_downs + *count_up;
						shot_col = shot_col - 1;
						
						*count_left = *count_left + 1;
					}

							if(game_board[shot_row][shot_col] == '*')
							{
								do
								{
									shot_col--;

									*count_left = *count_left + 1;

								}while (game_board[shot_row][shot_col] == '*' && shot_col >= 0);							

								if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '~' || shot_col < 0)
								{
									*miss3 = 1;
								}
								
								if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
								{
									do
									{
									shot_col++;

									num_rights++;

									}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

									if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
									{
										*miss4 = 1;
									}

									if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
									{
										*miss1 = 0;
										*miss2 = 0;
										*miss3 = 0;
										*miss4 = 0;

										*count_up = 0;
										*count_down = 0;
										*count_left = 0;
										*count_right = 0;

										*initial = player_stats->num_hits;
									}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
								}
							}
			}
			}
	
		else if(player_stats->num_hits > *initial && *miss2 == 0 && *sunk != 1)
		{
			
			if(*count_down == 0)
			{
				shot_row = (*row + 1 + *count_up);
				shot_col = *col;
			}
			else 
			{
				shot_row = *row + 1;
				shot_col = *col;
			}

			*count_down = *count_down + 1;
			
			if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
			{
				*miss2 = 1;
			}

			if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
			{
				shot_row = shot_row - 2;
				shot_col = shot_col - 1;
						
				*count_left = *count_left + 1;
			}

			if(game_board[shot_row][shot_col] == '*')
			{
				do
				{
					shot_row++;

					num_downs++;

					*count_down = *count_down + 1;

				}while(num_downs < 10 && (shot_row < 0 || game_board[shot_row][shot_col] == '*'));

				if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
				{
					*miss2 = 1;
				}

				if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
				{
					shot_row = shot_row - *count_down;
					shot_col = shot_col - 1;
						
					*count_left = *count_left + 1;
				}

				if(game_board[shot_row][shot_col] == '*')
				{
				do
				{
					shot_col--;

					*count_left = *count_left + 1;

				}while (game_board[shot_row][shot_col] == '*' && shot_col >= 0);							

				if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '~' || shot_col < 0)
				{
					*miss3 = 1;
				}
				else if (game_board[shot_row][shot_col] != 'o' && game_board[shot_row][shot_col] != '~' && game_board[shot_row][shot_col] != '*')
				{
					*count_down = 0;
				}

								
				if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
				{
					do
					{
						shot_col++;
					
						num_rights++;

					}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss4 = 1;
					}

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						*miss1 = 0;
						*miss2 = 0;
						*miss3 = 0;
						*miss4 = 0;

						*count_up = 0;
						*count_down = 0;
						*count_left = 0;
						*count_right = 0;

						*initial = player_stats->num_hits;
					}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
				}
				}
			}
			}
		
		else if(player_stats->num_hits > *initial && *miss3 == 0 && *sunk != 1)
		{

			if(*count_left == 0)
			{
				shot_row = (*row - *count_down);
				shot_col = *col - 1;
			}
			else 
			{
				shot_row = *row;
				shot_col = *col - 1;
			}

			*count_left = *count_left + 1;
			
			if(game_board[shot_row][shot_col] == 'o' || shot_col < 0 || game_board[shot_row][shot_col] == '~' || game_board[shot_row][shot_col] == '*')
			{
				*miss3 = 1;
			}

			if(game_board[shot_row][shot_col] == '*')
				{
				do
				{
					shot_col--;

					*count_left = *count_left + 1;

				}while (game_board[shot_row][shot_col] == '*' && shot_col >= 0);							

				if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '~' || shot_col < 0)
				{
					*miss3 = 1;
				}
				else if (game_board[shot_row][shot_col] != 'o' && game_board[shot_row][shot_col] != '~' && game_board[shot_row][shot_col] != '*')
				{
					*count_down = 0;
				}

								
				if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
				{
					do
					{
						shot_col++;
					
						num_rights++;

					}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss4 = 1;
					}

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						*miss1 = 0;
						*miss2 = 0;
						*miss3 = 0;
						*miss4 = 0;

						*count_up = 0;
						*count_down = 0;
						*count_left = 0;
						*count_right = 0;

						*initial = player_stats->num_hits;
					}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
				}
				if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
				{
					do
					{
						shot_col++;
					
						num_rights++;

					}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss4 = 1;
					}

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						*miss1 = 0;
						*miss2 = 0;
						*miss3 = 0;
						*miss4 = 0;

						*count_up = 0;
						*count_down = 0;
						*count_left = 0;
						*count_right = 0;

						*initial = player_stats->num_hits;
					}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
				}
			}
		}

		else if(player_stats->num_hits > *initial && *miss4 == 0 && *sunk != 1)
		{
			if(*count_right == 0)
			{
				shot_row = *row;
				shot_col = *col + 1 + *count_left;
			}
			else 
			{
				shot_row = *row;
				shot_col = *col + 1;
			}

			*count_right = *count_right + 1;
			
			if(game_board[shot_row][shot_col] == 'o' || shot_col > 9 || game_board[shot_row][shot_col] == '~' || game_board[shot_row][shot_col] == '*')
			{
				*miss4 = 1;
			}

			if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
			{
				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;

				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;

				*initial = player_stats->num_hits;
			}

			if(game_board[shot_row][shot_col] == '*')
			{
				shot_col++;

				if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
				{
					*miss1 = 0;
					*miss2 = 0;
					*miss3 = 0;
					*miss4 = 0;

					*count_up = 0;
					*count_down = 0;
					*count_left = 0;
					*count_right = 0;

					*initial = player_stats->num_hits;
				}
			}
		}

		else
		{
			do
			{
				shot_row = rand() % 10;
				shot_col = rand() % 10;

				*sunk = 0;

				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;

				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;
			}while (game_board[shot_row][shot_col] == '*' || game_board[shot_row][shot_col] == 'o');
		}


printf("\nComputer's Shoot: %d, %d\n", shot_row, shot_col);

*row = shot_row;
*col = shot_col;

}


void check_shot(char game_board[NUM_ROWS][NUM_COLS], int *row, int *col)
{
	if (game_board[*row][*col] == 'c')
	{
		game_board[*row][*col]='*';

		printf("\nCarrier was hit\n");
	}
	if (game_board[*row][*col] == 'b')
	{
		game_board[*row][*col]='*';

		printf("\nBattleship was hit\n");
	}
	if (game_board[*row][*col] == 'r')
	{
		game_board[*row][*col]='*';

		printf("\nCruiser was hit\n");
	}
	if (game_board[*row][*col] == 's')
	{
		game_board[*row][*col]='*';

		printf("\nSubmarine was hit\n");
	}
	if (game_board[*row][*col] == 'd')
	{
		game_board[*row][*col]='*';

		printf("\nDestroyer was hit\n");
	}
	if (game_board[*row][*col] == '~')
	{
		printf("\nMiss!!\n");
		
		game_board[*row][*col] = 'o';
	}
}


void hard_ai (char game_board[NUM_ROWS][NUM_COLS], int *row, int *col, Stats *player_stats, int *sunk, int *miss1, int *miss2, int *miss3, int *miss4, int *count_up, int *count_down, int *count_left, int *count_right, int *initial, int *camouflage)
{
	int shot_row = 0, shot_col = 0, decision = 0;

	int num_downs = 0, num_rights = 0;

		if (player_stats->num_hits > *initial && *miss1 == 0 && *sunk != 1)
		{
			shot_row = (*row - 1);
			shot_col = *col;

			*count_up = *count_up + 1;
		
			if(game_board[shot_row][shot_col] == 'o' || shot_row < 0 || game_board[shot_row][shot_col] == '~')
			{
				*miss1 = 1;
			}
			if(game_board[shot_row][shot_col] == '*')
			{
				do
				{
				shot_row--;

				*count_up = *count_up + 1;

				}while (game_board[shot_row][shot_col] == '*' && shot_row >= 0);

				if(game_board[shot_row][shot_col] == '~' || game_board[shot_row][shot_col] == 'o' || shot_row < 0)
				{
					*miss1 = 1;
				}
					
				if (shot_row < 0 || game_board[shot_row][shot_col] =='o')
				{
						do
						{
							shot_row++;

							num_downs++;
						}while(num_downs < 10 && (shot_row < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss2 = 1;
					}
					else if (game_board[shot_row][shot_col] != 'o' && game_board[shot_row][shot_col] != '~' && game_board[shot_row][shot_col] != '*')
					{
						*count_up = 0;

						*count_down = *count_down + 1;
					}

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						shot_row = shot_row - num_downs + *count_up;
						shot_col = shot_col - 1;
						
						*count_left = *count_left + 1;
					}

							if(game_board[shot_row][shot_col] == '*')
							{
								do
								{
									shot_col--;

									*count_left = *count_left + 1;

								}while (game_board[shot_row][shot_col] == '*' && shot_col >= 0);							

								if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '~' || shot_col < 0)
								{
									*miss3 = 1;
								}
								
								if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
								{
									do
									{
									shot_col++;

									num_rights++;

									}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

									if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
									{
										*miss4 = 1;
									}

									if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
									{
										*miss1 = 0;
										*miss2 = 0;
										*miss3 = 0;
										*miss4 = 0;

										*count_up = 0;
										*count_down = 0;
										*count_left = 0;
										*count_right = 0;

										*initial = player_stats->num_hits;
									}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
								}
							}
				}
			}				
					
			if (shot_row < 0 || game_board[shot_row][shot_col] =='o')
			{
					do
					{
						shot_row++;

						num_downs++;

					}while(num_downs < 10 && (shot_row < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss2 = 1;
					}
					else if (game_board[shot_row][shot_col] != 'o' && game_board[shot_row][shot_col] != '~' && game_board[shot_row][shot_col] != '*')
					{
						*count_up = 0;
					}


					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						shot_row = shot_row - num_downs + *count_up;
						shot_col = shot_col - 1;
						
						*count_left = *count_left + 1;
					}

							if(game_board[shot_row][shot_col] == '*')
							{
								do
								{
									shot_col--;

									*count_left = *count_left + 1;

								}while (game_board[shot_row][shot_col] == '*' && shot_col >= 0);							

								if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '~' || shot_col < 0)
								{
									*miss3 = 1;
								}
								
								if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
								{
									do
									{
									shot_col++;

									num_rights++;

									}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

									if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
									{
										*miss4 = 1;
									}

									if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
									{
										*miss1 = 0;
										*miss2 = 0;
										*miss3 = 0;
										*miss4 = 0;

										*count_up = 0;
										*count_down = 0;
										*count_left = 0;
										*count_right = 0;

										*initial = player_stats->num_hits;
									}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
								}
							}
			}
			}
	
		else if(player_stats->num_hits > *initial && *miss2 == 0 && *sunk != 1)
		{
			
			if(*count_down == 0)
			{
				shot_row = (*row + 1 + *count_up);
				shot_col = *col;
			}
			else 
			{
				shot_row = *row + 1;
				shot_col = *col;
			}

			*count_down = *count_down + 1;
			
			if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
			{
				*miss2 = 1;
			}

			if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
			{
				shot_row = shot_row - 2;
				shot_col = shot_col - 1;
						
				*count_left = *count_left + 1;
			}

			if(game_board[shot_row][shot_col] == '*')
			{
				do
				{
					shot_row++;

					num_downs++;

					*count_down = *count_down + 1;

				}while(num_downs < 10 && (shot_row < 0 || game_board[shot_row][shot_col] == '*'));

				if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
				{
					*miss2 = 1;
				}

				if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
				{
					shot_row = shot_row - *count_down;
					shot_col = shot_col - 1;
						
					*count_left = *count_left + 1;
				}

				if(game_board[shot_row][shot_col] == '*')
				{
				do
				{
					shot_col--;

					*count_left = *count_left + 1;

				}while (game_board[shot_row][shot_col] == '*' && shot_col >= 0);							

				if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '~' || shot_col < 0)
				{
					*miss3 = 1;
				}
				else if (game_board[shot_row][shot_col] != 'o' && game_board[shot_row][shot_col] != '~' && game_board[shot_row][shot_col] != '*')
				{
					*count_down = 0;
				}

								
				if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
				{
					do
					{
						shot_col++;
					
						num_rights++;

					}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss4 = 1;
					}

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						*miss1 = 0;
						*miss2 = 0;
						*miss3 = 0;
						*miss4 = 0;

						*count_up = 0;
						*count_down = 0;
						*count_left = 0;
						*count_right = 0;

						*initial = player_stats->num_hits;
					}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
				}
				}
			}
			}
		
		else if(player_stats->num_hits > *initial && *miss3 == 0 && *sunk != 1)
		{
			if(*count_left == 0)
			{
				shot_row = (*row - *count_down);
				shot_col = *col - 1;
			}
			else 
			{
				shot_row = *row;
				shot_col = *col - 1;
			}

			*count_left = *count_left + 1;
			
			if(game_board[shot_row][shot_col] == 'o' || shot_col < 0 || game_board[shot_row][shot_col] == '~' || game_board[shot_row][shot_col] == '*')
			{
				*miss3 = 1;
			}

			if(game_board[shot_row][shot_col] == '*')
				{
				do
				{
					shot_col--;

					*count_left = *count_left + 1;

				}while (game_board[shot_row][shot_col] == '*' && shot_col >= 0);							

				if(game_board[shot_row][shot_col] == 'o' || game_board[shot_row][shot_col] == '~' || shot_col < 0)
				{
					*miss3 = 1;
				}
				else if (game_board[shot_row][shot_col] != 'o' && game_board[shot_row][shot_col] != '~' && game_board[shot_row][shot_col] != '*')
				{
					*count_down = 0;
				}

								
				if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
				{
					do
					{
						shot_col++;
					
						num_rights++;

					}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss4 = 1;
					}

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						*miss1 = 0;
						*miss2 = 0;
						*miss3 = 0;
						*miss4 = 0;

						*count_up = 0;
						*count_down = 0;
						*count_left = 0;
						*count_right = 0;

						*initial = player_stats->num_hits;
					}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
				}
				if (shot_col < 0 || game_board[shot_row][shot_col] =='o')
				{
					do
					{
						shot_col++;
					
						num_rights++;

					}while(num_rights < 10 && (shot_col < 0 || game_board[shot_row][shot_col] == '*'));

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9 || game_board[shot_row][shot_col] == '~')
					{
						*miss4 = 1;
					}

					if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
					{
						*miss1 = 0;
						*miss2 = 0;
						*miss3 = 0;
						*miss4 = 0;

						*count_up = 0;
						*count_down = 0;
						*count_left = 0;
						*count_right = 0;

						*initial = player_stats->num_hits;
					}

									if(game_board[shot_row][shot_col] == '*')
									{
										shot_col++;

										if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
										{
											*miss1 = 0;
											*miss2 = 0;
											*miss3 = 0;
											*miss4 = 0;

											*count_up = 0;
											*count_down = 0;
											*count_left = 0;
											*count_right = 0;

											*initial = player_stats->num_hits;
										}
									}
				}
			}
		}

		else if(player_stats->num_hits > *initial && *miss4 == 0 && *sunk != 1)
		{
			if(*count_right == 0)
			{
				shot_row = *row;
				shot_col = *col + 1 + *count_left;
			}
			else 
			{
				shot_row = *row;
				shot_col = *col + 1;
			}

			*count_right = *count_right + 1;
			
			if(game_board[shot_row][shot_col] == 'o' || shot_col > 9 || game_board[shot_row][shot_col] == '~' || game_board[shot_row][shot_col] == '*')
			{
				*miss4 = 1;
			}

			if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
			{
				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;

				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;

				*initial = player_stats->num_hits;
			}

			if(game_board[shot_row][shot_col] == '*')
			{
				shot_col++;

				if(game_board[shot_row][shot_col] == 'o' || shot_row > 9)
				{
					*miss1 = 0;
					*miss2 = 0;
					*miss3 = 0;
					*miss4 = 0;

					*count_up = 0;
					*count_down = 0;
					*count_left = 0;
					*count_right = 0;

					*initial = player_stats->num_hits;
				}
			}
		}

		else
		{
			if(*camouflage == 0)
			{
				decision = rand() % 2 + 2;
			}
			if(*camouflage == 1)
			{
				decision = rand() % 2;
			}
			do
			{
			if (decision == 0)
			{
				shot_row = (rand() % 5) * 2;

				shot_col = (rand() % 5) * 2;
			}
			if (decision == 1)
			{
				shot_row = (rand() % 5) * 2 + 1;

				shot_col = (rand() % 5) * 2 + 1;
			}
			if (decision == 2)
			{
				shot_row = (rand() % 5) * 2;

				shot_col = (rand() % 5) * 2 + 1;
			}
			if (decision == 3)
			{
				shot_row = (rand() % 5) * 2 + 1;

				shot_col = (rand() % 5) * 2;
			}

			}while (game_board[shot_row][shot_col] == '*' || game_board[shot_row][shot_col] == 'o');

				*sunk = 0;

				*miss1 = 0;
				*miss2 = 0;
				*miss3 = 0;
				*miss4 = 0;

				*count_up = 0;
				*count_down = 0;
				*count_left = 0;
				*count_right = 0;
		}


printf("\nComputer's Shoot: %d, %d\n", shot_row, shot_col);

*row = shot_row;
*col = shot_col;

}
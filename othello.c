//***************************************************
// Filename: othello.c
//
// Sets up the game board and logic for Othello/Reversii.
//
// @author Jake Miller & Ashley Hendrickson
// @version Winter 2019
//***************************************************

#include "othello.h"
#include <stdio.h>
#include <stdlib.h>

/** Opponent of current player */
char opp(char p);

/** 0 for player, 1 for opponent, 2 for neither */
int checkD(char board[][SIZE], int* row, int* col, char disc);

/** Move row and col pointers in specific direction */
void moveD(char d, int* r, int* c);

/** Direction of peices to flip */
char flip;

//***************************************************
// Displays the board (as SIZE x SIZE grid) on 
// console
// @param board the 2-D array representing the board
//***************************************************
void displayBoard(char board[][SIZE])
{
	printf("\n");
	for (int i = 0; i < SIZE; i++) {
		printf((i == 0 ? "%5d" : "%3d"), i+1);
	}
	printf("\n");

	for (int i = 0; i < SIZE; i++) {
		printf("%2d", i+1);
		for (int j = 0; j < SIZE; j++) {
			printf("%3c", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//***************************************************
// Initializes the board with start configuration of 
// discs (see project specs)
// @param board the 2-D array representing the board
//***************************************************
void initializeBoard(char board[][SIZE])
{
	for(int i =0; i < SIZE; ++i){
		for(int j = 0; j<SIZE; ++j){
			board[i][j] = '-';
		}
	}
	board[3][3] = 'B';
	board[4][4] = 'B';
	board[3][4] = 'W';
	board[4][3] = 'W';
}

//***************************************************
// Returns true if moving the disc to location row,
// col is valid; else returns false
// @param board the game board
// @param row the in the board to check
// @param col the column in the board to check
// @param disc the color disc of the current player
// @retrurn bool
//***************************************************
bool isValidMove(char board[][SIZE], int row, int col, char disc)
{
	// out of bounds
	if(row > (SIZE-1) || col > (SIZE-1) || row < 0 || col < 0){
		return false;
	}
	if(board[row][col] == opp(disc) || board[row][col] == disc){
		return false;
	}

	int dRow = row;
	int dCol = col;
	int* r = &dRow;
	int* c = &dCol;

	int i = 0;
	do{
		moveD('N', r, c);
		i++;
		if(checkD(board, r, c, disc) == 0 && i > 1){
			flip = 'N';
			return true;
		}
	}while(checkD(board, r, c, disc) == 1);

	*r = row;
	*c = col;
	i = 0;
	do{
		moveD('S', r, c);
		i++;
		if(checkD(board, r, c, disc) == 0 && i > 1){
			flip = 'S';
			return true;
		}
	}while(checkD(board, r, c, disc) == 1);

	*r = row;
	*c = col;
	i = 0;
	do{
		moveD('E', r, c);
		i++;
		if(checkD(board, r, c, disc) == 0 && i > 1){
			flip = 'E';
			return true;
		}
	}while(checkD(board, r, c, disc) == 1);

	*r = row;
	*c = col;
	i = 0;
	do{
		moveD('W', r, c);
		i++;
		if(checkD(board, r, c, disc) == 0 && i > 1){
			flip = 'W';
			return true;
		}

	}while(checkD(board, r, c, disc) == 1);

	*r = row;
	*c = col;
	i = 0;
	do{
		moveD('1', r, c);
		i++;
		if(checkD(board, r, c, disc) == 0 && i > 1){
			flip = '1';
			return true;
		}

	}while(checkD(board, r, c, disc) == 1);

	*r = row;
	*c = col;
	i = 0;
	do{
		moveD('2', r, c);
		i++;
		if(checkD(board, r, c, disc) == 0 && i > 1){
			flip = '2';
			return true;
		}

	}while(checkD(board, r, c, disc) == 1);

	*r = row;
	*c = col;
	i = 0;
	do{
		moveD('3', r, c);
		i++;
		if(checkD(board, r, c, disc) == 0 && i > 1){
			flip = '3';
			return true;
		}

	}while(checkD(board, r, c, disc) == 1);

	*r = row;
	*c = col;
	i = 0;
	do{
		moveD('4', r, c);
		i++;
		if(checkD(board, r, c, disc) == 0 && i > 1){
			flip = '4';
			return true;
		}

	}while(checkD(board, r, c, disc) == 1);
	return false;
}

//***************************************************
// Places the disc at location row,col and flips the 
// opponent discs as needed
// @param board the game board
// @param row the row of the board
// @param col the column of the board
// @param disc the players disc color
//***************************************************
void placeDiscAt(char board[][SIZE], int row, int col, char disc)
{
	board[row][col] = disc;

	int dRow = row;
	int dCol = col;
	int* r = &dRow;
	int* c = &dCol;

	do{
		moveD(flip, r, c);
		board[*r][*c] = disc;
	}while(board[*r][*c] == opp(disc));
}
//***************************************************
// Returns true if a valid move for disc is 
// available; else returns false
// @param board the game board
// @param disc the current players disc color
// @return bool
//***************************************************
bool isValidMoveAvailable(char board[][SIZE], char disc)
{	
	if(isBoardFull(board)){
		return false;
	}

	for(int i = 0; i < SIZE; ++i){
		for(int j = 0; j < SIZE; ++j){
			if(isValidMove(board, i, j, disc)){
				return true;
			}
		}
	}
	return false;
}

//***************************************************
// Move row and col pointers in specific direction
// @param d the direction to move (N,S,E,W) & 1,2,3,4
// to represent NE, SE, SW, NW respectively
// @param r the row to move from 
// @param c the column to move from
//***************************************************
void moveD(char d, int* r, int* c){
	switch(d){
		case 'N':
			(*r)++;
			break;
		case 'E':
			(*c)++;
			break;
		case 'S':
			(*r)--;
			break;
		case 'W':
			(*c)--;
			break;
		case '1':
			(*r)--;
			(*c)++;
			break;
		case '2':
			(*r)++;
			(*c)++;
			break;
		case '3':
			(*r)++;
			(*c)--;
			break;
		case '4':
			(*r)--;
			(*c)--;
			break;
	}

}

//***************************************************
// checks the current position and returns 
// 0 for player, 1 for opponent, 2 for neither
// @param board the game board
// @param r the row to check
// @param c the column to check
// @param disc the players disc color
// @return int
//***************************************************
int checkD(char board[][SIZE], int* r, int* c, char disc){
	if(board[*r][*c] == disc){
		return 0;
	}
	if(board[*r][*c] == opp(disc)){
		return 1;
	}
 	if(board[*r][*c] == '-'){
		return 2;
	}
	// out of bounds
	if(*r > (SIZE-1) || *c > (SIZE-1) || *r < 0 || *c < 0){
		return 2;
	}
	return 2;
}

//***************************************************
// Opponent of current player
// @param p the current players disc color
// @return char
//***************************************************
char opp(char p){
	if(p == 'B'){
		return 'W';
	}else{
		return 'B';
	}
}
//***************************************************
// Returns true if the board is fully occupied with 
// discs; else returns false
// @param board the game board
// @return bool
//***************************************************
bool isBoardFull(char board[][SIZE])
{
	for(int i =0; i < SIZE; ++i){
		for(int j = 0; j<SIZE; ++j){
			if(board[i][j] == '-'){
				return false;
			}
		}
	}
	return true;	
}

//***************************************************
// Returns true if either the board is full or a 
// valid move is not available for either disc
// @param board the game board
// @return bool
//***************************************************
bool isGameOver(char board[][SIZE])
{
	if(isBoardFull(board) || (!isValidMoveAvailable(board, 'B') && 
					!isValidMoveAvailable(board, 'W')))
	{
		return true;
	}
	
	return false;
}
//***************************************************
// If there is a winner, it returns the disc 
// (BLACK or WHITE) associated with the winner.
// In case of a tie, it returns EMPTY
// @param board the game board
// @return char
//***************************************************
char checkWinner(char board[][SIZE])
{
	int countB = 0;
	int countW = 0;
	
	for(int i = 0; i < SIZE; ++i){
		for(int j = 0; j < SIZE; ++j){
			if(board[i][j] == 'B'){
				countB++;
			}
			if(board[i][j] == 'W'){
				countW++;
			}
		}
	}
	
	if(countB > countW){
		return BLACK;
	}	
	if(countB < countW){
		return WHITE;
	}
	return EMPTY;	
}

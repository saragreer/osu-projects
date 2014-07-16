//
//  greersA1.h
//
//  Created by Sara Greer on 7/3/14.
//

#ifndef greersA1_H
#define greersA1_H

//Global variables for 2D grid size
const int ROW = 122;
const int COL = 180;

//Prints 22X80 window on total grid
void print(int a[ROW][COL]);

//Menu to choose starting position
void build(int a[ROW][COL], int& choice);

//Menu to choose life cycle
void cycle(int& loop, int& count);

//Checks each cell and determines if it lives or dies
void rules(int a[ROW][COL]);

//Copies grid into temporary array so changes won't affect it
void copy(int a[ROW][COL], int b[ROW][COL]);

//Error checking functions
int validInt();
void newLine();

#endif

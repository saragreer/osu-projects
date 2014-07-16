//
//  greersA1.cpp
//
//  Created by Sara Greer on 7/3/14.
//

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "greersA1.h"

/************************************************************************
 * Function name:   print
 * Entry:           Takes 2D int array of size [32][90]
 * Exit:            Replaces 0s with ' ' and 1s with '*'
 * Purpose:         Prints array to console
 ************************************************************************/
void print(int a[ROW][COL])
{
    //replaces 0s and 1s with white and black squares
    for(int i = 49; i < 72; i++)
    {
        for(int j = 49; j < 129; j++)
        {
            if(a[i][j] == 0)
            {
                cout << "◻︎";
            }
            else if(a[i][j] == 1)
            {
                cout << "◼︎";
            }
        }
        
        cout << endl;
    }
}

/************************************************************************
 * Function name:   rules
 * Entry:           Takes 2D int array of size [32][90]
 * Exit:            Returns altered array according to rules
 * Purpose:         Checks each cell against Game of Life rules
 ************************************************************************/
void rules(int a[ROW][COL])
{
    //Creates copy of array to check rules on so main array isn't affected
    int temp[ROW][COL];
    copy(a, temp);
    
    for(int i = 1; i < ROW-1; i++)
    {
        for(int j = 1; j < COL-1; j++)
        {
            //variable holds current count of all cells adjacent to center cell
            int totalCells = 0;
            totalCells = a[i-1][j-1] +
            a[i-1][j] +
            a[i-1][j+1] +
            a[i][j-1] +
            a[i][j+1] +
            a[i+1][j-1] +
            a[i+1][j] +
            a[i+1][j+1];
            
            if(totalCells < 2 || totalCells > 3)
            {
                temp[i][j] = 0; //dies
            }
            
            if(totalCells == 2)
            {
                temp[i][j] = a[i][j]; //keeps on livin'
            }
            
            if(totalCells == 3)
            {
                temp[i][j] = 1; //lives
            }
        
        }
    }
    
    copy(temp, a);
}

/************************************************************************
 * Function name:   copy
 * Entry:           Takes two 2D int arrays of size [32][90]
 * Exit:            Sets second array equal to first
 * Purpose:         Makes temporary copy of main game array so changes
 *                  won't affect it during rules function
 ************************************************************************/
void copy(int a[ROW][COL], int b[ROW][COL])
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            b[i][j] = a[i][j];
        }
    }
}

/************************************************************************
 * Function name:   build
 * Entry:           Takes 2D int array of size [32][90], menu choice
 * Exit:            Initializes array depending on menu choice
 * Purpose:         Allows user to choose starting position
 ************************************************************************/

void build(int a[ROW][COL], int& choice)
{
    cout << "\nUsers can choose from the following starting positions:\n"
    
         << "1. Glider\n"
         << "2. R-pentomino\n"
         << "3. Random\n"
         << "Choose a starting position (Press 1, 2, or 3, then Enter): ";
    
    choice = validInt();
    
    while (choice < 1 || choice > 3)
    {
        cout << "Invalid input. Press 1, 2, or 3, then Enter: ";
        choice = validInt();
    }
        
    switch (choice) {
        case 1:
            
            //build 2 gliders
            a[51][56] = 1;
            a[52][57] = 1;
            a[53][55] = 1;
            a[53][56] = 1;
            a[53][57] = 1;
            
            a[51][76] = 1;
            a[52][77] = 1;
            a[53][75] = 1;
            a[53][76] = 1;
            a[53][77] = 1;
            
            break;
            
        case 2:
            
            //build R-pentomino
            a[55][81] = 1;
            a[56][80] = 1;
            a[56][81] = 1;
            a[57][81] = 1;
            a[55][82] = 1;
            
            break;
            
        case 3:
            
            //fill randomly
            srand(time_t(NULL));
            
            for(int i = 0; i < ROW; i++)
            {
                for(int j = 0; j < COL; j++)
                {
                    a[i][j] = rand()%2;
                }
            }
            
            break;
            
        default:
            
            cout << "Invalid option.";
            
            break;
    }
    
    system("clear");
}

/************************************************************************
 * Function name:   cycle
 * Entry:           Takes 2D int array of size [32][90], menu choice
 * Exit:            Sets loop equal to 1 or 100
 * Purpose:         Allows user to choose length of life cycle
 ************************************************************************/

void cycle(int& loop, int& count)
{
    cout << "\nUsers can choose the length of the life cycle:\n"
    << "1. One at a time\n"
    << "2. 100 at a time\n\n"
    << "**************************************************************\n"
    << "NOTE: Please adjust your window to fit grid properly (83x25).\n"
    << "**************************************************************\n\n"

    << "Choose a life cycle (Press 1 or 2, then Enter): ";
    
    count = validInt();
    
    while (count < 1 || count > 2)
    {
        cout << "Invalid input. Press 1 or 2, then Enter: ";
        count = validInt();
    }

    if (count == 1)
    {
        loop = 1;
    }
    else
    {
        loop = 100;
        count = loop;
    }
}

/************************************************************************
 * Function name:    validInt (error checking function I built in 161)
 * Entry:            Requests input to assign to a variable of type int.
 * Exit:             Returns an integer.
 * Purpose:          Checks that user input is an integer.
 ************************************************************************/
int validInt()
{
	int value = 0;
	
    cin >> value;
	
    //checks for valid input; special characters, doubles, spaces not allowed
    while (cin.fail() || (value != static_cast<int>(value)))
    {
    	cin.clear();
        cin.ignore(10000,'\n');
        cout << "That is not an acceptable value. Enter an integer: ";
        cin >> value;
    }
    
    //clears input remaining on above cin >>
    newLine();
    
    //returns checked integer
    return value;
}

/************************************************************************
 * Function name:    newLine() (from Savitch "Absolute C++")
 * Entry:			 Checks input stream for leftover data
 * Exit:             Clears input stream
 * Purpose:          Discards input on current input line, including '\n'
 ************************************************************************/
void newLine()
{
	char symbol;
	do
	{
		cin.get(symbol);
        
    } while (symbol != '\n');
}

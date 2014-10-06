/*****
 * Author:           Sara Greer
 * Date:             July 3, 2014
 * Last modified:    October 6, 2014
 * File name:        main.cpp
 *
 * Overview: This is a C++ simulation of Conway's Game of Life.
 *
 * Input: The user can choose from three starting positions and two
 * life cycle lengths, as well as whether to repeat the life cycle and
 * to choose a new starting position.
 *
 * Output: The output is a 22x80 grid of empty spaces and asterisks that
 * transitions according to the rules of Life and how many life cycles
 * the user chooses.
 *
 *****/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

#include "greersA1.h"

int main()
{
    int world[ROW][COL];
    int choice = 0;
    char next = 'y';
    char repeat = 'y';
    string pause;
    
    //Clears screen via http://runnable.com/u/creativename
    system("clear");
    
    cout << "This is a C++ simulation of Conway's Game of Life.\n\n"
    
    << "From Wikipedia:\n"
    << "\"The universe of Game of Life is an infinite 2D grid of cells,\n"
    << "each of which is in one of two states, alive or dead. Every\n"
    << "cell interacts with its eight neighbors, which are the cells\n"
    << "that are horizontally, vertically, or diagonally adjacent.\n\n"
    
    << "\"At each step in time, the following transitions occur:\n"
    << "1. Any live cell with fewer than two live neighbors dies,\n"
    << "as if caused by underpopulation.\n"
    << "2. Any live cell with two or three live neighbors lives\n"
    << "on to the next generation.\n"
    << "3. Any live cell with more than three live neighbors dies\n"
    << "as if by overcrowding.\n"
    << "4. Any dead cell with exactly three live neighbors becomes\n"
    << "a live cell, as if by reproduction.\"\n";
    
    //first loop allows user to choose starting position
    do
    {
        int loop = 0;
        int count = 0;
        int generation = 0;
        
        //start with a blank grid
        for(int i = 0; i < ROW; i++)
        {
            for(int j = 0; j < COL; j++)
            {
                world[i][j] = 0;
            }
        }
        
	//user chooses grid layout
        build(world, choice);

	//user chooses how many cycles to run
        cycle(loop, count);

	//prints first grid layout to console
        print(world);
        
        //print choice, use getline to pause, set next = y to continue
        if (choice == 1)
            cout << "Simulation: GLIDER\n";
        else if (choice == 2)
            cout << "Simulation: R-PENTOMINO\n";
        else
            cout << "Simulation: RANDOM\n";
        
        cout << "Press Enter to continue: ";
        getline(cin, pause);
        next = 'y';
        
        //second loop allows user to repeat life cycle
        do
        {
            //next 2 loops run chosen life cycle once
            //split into 2 so that last cycle stays on screen
            while (loop != 1)
            {
                rules(world);
                print(world);
                cout << "Generation: " << generation + 1 << endl;
                loop--;
                generation++;
                
                //Pauses program for 1/10th of a second via http://runnable.com/u/creativename
                system("sleep .1");
                system("clear");
            }
            
            while (loop != 0)
            {
                rules(world);
                print(world);
                cout << "Generation: " << generation + 1 << endl;
                loop--;
                generation++;
            }
            
            cout << "Repeat life cycle? (Press Y or N, then Enter): ";
            cin >> next;
            newLine();
            
            if (next == 'y' || next == 'Y')
                loop = count;
            else
                break;
            
        } while (next == 'y' || next == 'Y');
        
        cout << "Choose a different starting position? (Press Y or N, then Enter): ";
        cin >> repeat;
        newLine();
        
    } while (repeat == 'y' || repeat == 'Y');
    
    return 0;
}

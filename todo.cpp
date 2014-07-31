/*****
* Author:           Sara Greer
* Date:             May 19, 2014
* Last modified:	  June 8, 2014
* File name:        finalproject.cpp
*
* Overview:         ToDay is a simple to do list app that allows a user
*					          to create a list and edit, mark complete, and view tasks.
*
* Reevaluation:     Please re-evaluate the command line argument requirement
*                   from Assignment 7 based on source code found in main at
*                   line 73 and inside a class function at line 407. At the
*                   time I did not understand how to interpret and convert
*                   the arguments into usable data. After several tutorials
*                   I finally understood the basics and was able to implement
*                   them in a program.
*
*****/

#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;

// ClASS DEFINITION ---------------------------------------------------------------------

class Todo
{
public:
    Todo(); //Default constructor
    //Mutator functions (some complex, defined later)
	void setDescription(string descriptionNew);
	void setPriority(int priorityNew);
	void setCategory(string categoryNew);
    //Accessor functions (simple, defined here)
    string getDescription(){ return description; }
	int getPriority(){ return priority; }
	string getStatus(){ return status; }
	string getCategory(){ return category; }
    void input(int argc, const char * argv[]);
    void input();
private:
    //Member functions
    void menu(Todo task[], int taskListSize);
    void view(Todo task[], int taskListSize);
    void edit(Todo task[], int taskListSize);
    void sortAlpha(Todo task[], int taskListSize);
    //Member variables
	string description;
	int priority;
	string status;
	string category;
    int taskListSize;
};

typedef Todo* TodoPtr;

// FUNCTION PROTOTYPES ------------------------------------------------------------------

//Error check for integer input
int validInt();
//Discards input remaining on current input line, including '\n'
void newLine();
//Function to demonstrate random number generation
void randomQuote();

// PROGRAM STARTS -----------------------------------------------------------------------

int main(int argc, const char * argv[])
{
    
    Todo task;
    
    cout << "\nThis simple to do list program helps keep\n"
         << "track of the day's most important tasks.\n\n";
	
	//checks for command line arguments
    if (argc > 1)
    {
        task.input(argc, argv);
    }
    else
    {
        task.input();
    }
    
    return 0;
}

// FUNCTION DEFINITIONS ------------------------------------------------------------------

/************************************************************************
* Function name:    menu(Todo task[], int taskListSize)
* Entry:			Takes pointer to first array index, size of array
* Exit:             One of two member functions, or exits program.
* Purpose:          Allows user to choose how to manipulate data or exit.
************************************************************************/
void Todo::menu(Todo task[], int taskListSize)
{
	int option = 0;
	
	cout << "---------------------------------------------------------------\n"
    << "MENU | 1 View | 2 Edit | 3 Exit\n"
    << "Select option: ";
	
    //Runs error checking function where input is taken, verified, and returned
	option = validInt();
	
	cout << string(200, '\n');
    
    switch (option)
	{
		case 1:
		{
            //User can view running list of tasks
            cout << "STATUS\tPRIORITY\tTASK DESCRIPTION\tCATEGORY: All\n";
			view(task, taskListSize);
			break;
		}
		case 2:
		{
            //User can edit task description, priority, status, category
            cout << "STATUS\tPRIORITY\tTASK DESCRIPTION\tCATEGORY: All\n";
			edit(task, taskListSize);
			break;
		}
		case 3:
		{
            //User can exit program, all changes will be lost
			exit(1);
		}
		default:
		{
			cout << "That is not an option. Select option 1 - 3.\n";
			menu(task, taskListSize);
		}
	}
	
    //Runs after each menu choice so it's always available, user can choose to quit anytime
	menu(task, taskListSize);
}

/************************************************************************
* Function name:    input()
* Entry:			If no command line arguments, calls from main.
* Exit:             Returns array of class objects input by user.
* Purpose:          Creates task list with description, status, priority
*                   and category information.
************************************************************************/
void Todo::input()
{
    cout << "NOTE: This program accepts command line arguments.\n"
         << "Usage: ./filename \"Task description\" " << "\n"
         << "Enter as many task descriptions as needed.\n"
         << "-------------------------------------------------\n\n"
         << "First we'll create today's to do list.\n"
         << "How many tasks would you like to enter? ";
    
    //Runs error checking function where input is taken, verified, and returned
    taskListSize = validInt();
    
    //creates dynamic array based on user input
    TodoPtr p_task;
	p_task = new Todo[taskListSize];
	
    //Allow user to enter task data for each task they want to enter
	for(int i = 0; i < taskListSize; i++)
	{
		cout << "-----------------------------------------------------------\n"
             << "Task " << i+1 << "\n"
             << "Description: ";
		getline(cin, description);
		p_task[i].setDescription(description);
		
		cout << "Category (Choose letter: [p]ersonal [w]ork [s]chool): ";
		getline(cin, category);
		p_task[i].setCategory(category);
		
		cout << "Priority (Choose 1 for important, 2 for normal): ";
		priority = validInt();
		p_task[i].setPriority(priority);
        
        //p_task[i].setStatus("[ ]"); //commented out after constructor built
		
		cout <<  "-----------------------------------------------------------\n";
        
	}
    
    //Clear screen (idea from code by Ian Bender shared on Piazza)
	cout << string(200, '\n');
    
    randomQuote();
    
    //Calls to a main menu which controls bulk of the program flow
    menu(p_task, taskListSize);
    
}

/************************************************************************
 * Function name:   input(int argc, const char * argv[])
 * Entry:			Runs if command line arguments are detected
 * Exit:			Returns array of objects of class Todo
 * Purpose:         Creates list of task information
 ************************************************************************/
void Todo::input(int argc, const char * argv[])
{
    //Creates dynamic array based on command line arguments
    taskListSize = argc - 1;
	TodoPtr p_task;
	p_task = new Todo[taskListSize];
    
    //Assigns each task description entered to array of tasks
	for(int i = 0, j = 1; i < taskListSize; i++, j++)
	{
        p_task[i].setDescription(argv[j]);
    }
    
    //Allow user to enter other data for each task description entered
    for (int i = 0; i < taskListSize; i++)
    {
        cout << "Task " << i+1 << "\n"
             << p_task[i].getDescription() << "\n"
             << "Category (Choose letter: [p]ersonal [w]ork [s]chool): ";
        
		getline(cin, category);
		p_task[i].setCategory(category);
		
		cout << "Priority (Choose 1 for important, 2 for normal): ";
        priority = validInt();
		p_task[i].setPriority(priority);
        
        //p_task[i].setStatus("[ ]");
        
    }
    
    //Clear screen (idea from code by Ian Bender shared on Piazza)
	cout << string(200, '\n');
    
    randomQuote();
    
    //Calls to a main menu which controls bulk of the program flow
    menu(p_task, taskListSize);
    
}

/************************************************************************
 * Function name:   view(Todo task[], int taskListSize)
 * Entry:			Takes pointer to first array element, size of array
 * Exit:			Prints information entered by user
 * Purpose:         Prints values in private variables of class Todo
 ************************************************************************/
void Todo::view(Todo task[], int taskListSize)
{
    //Prints all tasks in list
    for(int i = 0; i < taskListSize; i++)
	{
		cout << task[i].getStatus() << "\t\t"
             << task[i].getPriority() << "\t"
             << i+1 << ". "
             << task[i].getDescription() << endl;
	}
}

/************************************************************************
* Function name:    edit(Todo task[], int taskListSize)
* Entry:			Takes task array, size of array.
* Exit:             Array values may be changed.
* Purpose:          Allows user to pick which tasks to edit, overwrite
*					data.
************************************************************************/
void Todo::edit(Todo task[], int taskListSize)
{
	int index, option;
    string ans;
    
    //prints task list to screen for reference
    task->view(task, taskListSize);
	
    cout << "Choose number of the task to edit: ";
	index = validInt();
    //subtract one to get true array index
	index = index - 1;
    
	if(index >= 0 && index < taskListSize)
    {
        cout << "What about the task do you want to edit?\n"
        << "1 Everything! | 2 Description | 3 Status | 4 Category | 5 Priority\n"
        << "Select option: ";
        option = validInt();
        
        if(option == 1) //User must reset description, category, priority, and can change status
        {
            cout << "Task " << index+1 << "\n"
            << "Description: ";
            getline(cin, description);
            task[index].setDescription(description);
            
            cout << "Category (Choose letter: [p]ersonal [w]ork [s]chool): ";
            getline(cin, category);
            task[index].setCategory(category);
            
            cout << "Priority (Choose 1 for important, 2 for normal): ";
            priority = validInt();
            task[index].setPriority(priority);
            
            cout << "Set status to done? (y/n)";
            getline(cin, ans);
            if(ans[0] == 'y' || ans[0] == 'Y')
            {
                task[index].status = "[X]";
            }
        }
        else if (option == 2) // User must reset description
        {
            cout << "Task " << index+1 << "\n"
            << "Description: ";
            getline(cin, description);
            task[index].setDescription(description);
        }
        else if (option == 3) // User can change status
        {
            cout << "Set status to done? (Y/N) ";
            getline(cin, ans);
            
            if(ans[0] == 'y' || ans[0] == 'Y')
            {
                task[index].status = "[X]";
            }
        }
        else if (option == 4)
        {
            cout << "Category (Choose letter: [p]ersonal [w]ork [s]chool): ";
            getline(cin, category);
            task[index].setCategory(category);
        }
        else if (option == 5)
        {
            cout << "Priority (Choose 1 for important, 2 for normal): ";
            priority = validInt();
            task[index].setPriority(priority);
        }
        else
        {
            cout << "That's not a valid option. Returning to main menu.\n";
            menu(task, taskListSize);
        }
    }
    else
    {
        cout << "That's not a valid choice. Returning to main menu.\n";
        menu(task, taskListSize);
    }
}

/************************************************************************
 * Function name:   Todo::Todo()
 * Entry:			When object of class Todo is declared
 * Exit:			Sets default values of all member variables
 * Purpose:         Gives new object pre-determined values
 ************************************************************************/
Todo::Todo()
{
    status = "[ ]";
    priority = 2;
    description = "Task description";
    category = "Personal";
}

/************************************************************************
 * Function name:   setDescription(string descriptionNew)
 * Entry:			Called by another function or variable
 * Exit:			Returns data stored in string description
 * Purpose:         Access to private data
 ************************************************************************/
void Todo::setDescription(string descriptionNew)
{
    description = descriptionNew;
}

/************************************************************************
 * Function name:   setPriority(int priorityNew)
 * Entry:			Takes input to be stored in object int priority
 * Exit:			Sets value of priorty
 * Purpose:         Access to private data, keeps input within acceptable range
 ************************************************************************/
void Todo::setPriority(int priorityNew)
{
    //checks input is one of two choices, 1 or 2
    while (priorityNew != 1 && priorityNew != 2)
    {
        cout << "Invalid priority input. Enter 1 or 2: ";
        priorityNew = validInt();
    }
    priority = priorityNew;
}

/************************************************************************
 * Function name:   setCategory(string categoryNew)
 * Entry:			Takes input to be stored in object int category
 * Exit:			Sets value of category
 * Purpose:         Access to private data, keeps input within acceptable range
 ************************************************************************/
void Todo::setCategory(string categoryNew)
{
    
    while (categoryNew[0] != 'p' && categoryNew[0] != 'w' && categoryNew[0] != 's')
    {
        cout << "Invalid category input. Enter a lowercase p, w, or s: ";
        getline(cin, categoryNew);
    }
    
    if (categoryNew[0] == 'p')
        category = "Personal";
    else if (categoryNew[0] == 'w')
        category = "Work";
    else
        category = "School";
}

/************************************************************************
* Function name:    validInt
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
* Function name:    newLine() (from Savitch "Absolute C++"
* Entry:			Checks input stream for leftover data
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

/************************************************************************
 * Function name:   randomQuote()
 * Entry:			Starts before menu appears at end of input functions.
 * Exit:			Returns a quote determined by a random number.
 * Purpose:         To demontrate random numbers, and to add something
                    unexpected to a simple program.
 ************************************************************************/
void randomQuote()
{
	int quote = 0;
	
    //initialize random seed using time clock
	srand (time(NULL));
	
	//generate number between 1 and 3
	quote = rand() % 3 + 1;
	
	if (quote == 1)
	{
		cout << "\nThe moment you panic - you're letting go\n"
        << "of what you know and you're about to learn\n"
        << "something new.\n"
        << "-- Louis CK, comedian\n";
	}
	else if (quote == 2)
	{
		cout << "\nNothing will work unless you do.\n"
        << "-- Maya Angelou, poet and author\n";
	}
	else
	{
		cout << "\nDon't think about your errors or failures;\n"
        << "otherwise, you'll never do a thing.\n"
        << "-- Bill Murray, actor\n";
	}
}

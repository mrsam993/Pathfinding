//include the header file to access all needed libraries and functions 
#include"Header.h"

//function that starts the program
int main()
{
	//clear the screen incase the program is run from the command line
	system("cls");
	//define variables for the function
	int exit = 0;
	char menuOption[100] = { 0 };
	//do while loop that only breaks if the user presses the number 3 to exit the program that runs the menu
	do
	{
		//present the user with the menu options and gather their input into the array
		std::cout << "What would you like to do? Please input a number and press enter to pick an option:\n(1) Select a maze to solve\n(2) Read the instructions\n(3) Quit the game\n";
		std::cin.getline(menuOption, 100);
		//if the user input is over 100 characers or causes an error with the array in any other way, clear and repair the buffer to prevent storing extra inputs or crashing the program
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		//test the users input against the 3 menu options, if none of these are the users input run the default case
		switch (menuOption[0])
		{
			//if the user entered the number 1 clear the screen and run the game function, after this function is complete break from the switch statement
		case '1':
			system("cls");
			mazeSelector();
			break;
			//if the user entered the number 2 clear the screen and run the instructions function, after this function is complete break from the switch statement
		case '2':
			system("cls");
			instructions();
			break;
			//if the user entered the number 3 clear the screen and set the exit integer to be 1 allowing the do while loop to end and for the program to close
		case '3':
			system("cls");
			exit = 1;
			break;
			//if the users input does not match any of theses cases, present an error message, wait for the user to press enter then clear the screen and repeat the loop
		default:
			std::cout << "This is not a valid option please enter a single number (1), (2) or (3)\n";
			system("pause");
			system("cls");
			break;
		}
		//break from the while loop after the user the user has pressed 3 to confirm their exit
	} while (exit == 0);
}
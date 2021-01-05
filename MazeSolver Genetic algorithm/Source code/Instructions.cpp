//include the header file to access all needed libraries and functions 
#include"Header.h"

//function that displays the instructions to the user, after they have entered 2 on the main menu
void instructions()
{
	//clear the screen removing the main menu, then display the different sections of the instructions, wait for the user to press enter giving them time to read the instructions then clear the screen and go back to the menu function allowing the menu to be displayed again
	system("cls");
	std::cout << "This is a program for finding the quickest route from A to B in a maze\n" << " -Each maze must be in the format of a .txt file\n" << " -Each maze must have one start point represented by an '2', and one end point represented by a '3'\n" << " -Empty spaces must be represented by a '0', and obstacles must be represented by a '1'\n" << " -The maze must begin with the two numbers that are the number of rows and the number of columns\n" << " -Mazes must not contain any characters apart from the aforementioned ones\n" << " -There must be a space dividing each number\n" << " -All rows of the maze must be the same size and all columns must be the same size\n" << " -The maze can be a rectangle\n" << " -The maze does not have to have a solution\n" << " -An example maze called 'example' can be found in the directory for clarification\n";
	system("pause");
	system("cls");
}
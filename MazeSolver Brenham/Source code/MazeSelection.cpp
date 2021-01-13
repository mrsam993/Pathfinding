//include the header file to access all needed libraries and functions 
#include"Header.h"

//function that allows the user to select a maze
void mazeSelector()
{
	//define variables for the function
	string mazeOption;
	string mazeLine;
	string mazetemp;
	string maze;

	int lineLength = 0;
	int lineTotal = 0;

	int error = 0;
	int startPoint = 0;
	int endPoint = 0;

	//present the user with instructions and use their input to find and open a file containing a maze
	std::cout << "Enter the name of the file you would like to open:\n" << " -If the maze location is in the same file as the program, enter the file name.\n" << " -If the file is not in the program folder, enter the file location.\n" << " -You do not need to add the file extention when entering the file name.\n" "  EXAMPLE: \'quickest_route_1\' or \'C:\\\\temp\\\\maze\'\n";
	std::getline(std::cin, mazeOption);
	mazeOption.append(".txt");
	
	//use the users input to open the required file
	fstream mazeFile(mazeOption, fstream::in);
	getline(mazeFile, mazetemp);
	//if no lines were read, flag up an error
	if (!mazeFile) {
		error = 1;
	}
	//read the file and assign it to a string
	maze.append(mazetemp);
	//close the file
	mazeFile.close();
	
	//remove all empty space from the maze as well as seperating the rows and column
	int size = maze.find_first_of(" ");
	for (int i = 0; i < size; i++)
	{
		if (i > 0)
		{
			lineLength *= 10;
		}
		lineLength -= 48;
		lineLength += maze[0];
		maze.erase(0, 1);
	}
	maze.erase(0, 1);
	size = maze.find_first_of(" ");
	for (int z = 0; z < size; z++)
	{
		if (z > 0)
		{
			lineTotal *= 10;
		}
		lineTotal -= 48;
		lineTotal += maze[0];
		maze.erase(0, 1);
	}
	maze.erase(remove_if(maze.begin(), maze.end(), isspace), maze.end());
	
	//check each character of the file to determine if there are any invalid characters and to count the amount of start and end points
	for (int i = 0; i < maze.size(); i++)
	{
		if (maze.at(i) == '2')
		{
			startPoint += 1;
		}
		if (maze.at(i) == '3')
		{
			endPoint += 1;
		}
		//if there are any invalid characters, flag up an error
		if (maze.at(i) != '0' && maze.at(i) != '1' && maze.at(i) != '2' && maze.at(i) != '3')
		{
			error = 4;
		}
	}
	//flag any other errors in the cases of multiple start or end points or no start or end point
	if (error != 1)
	{
		if (startPoint < 1)
		{
			error = 2;
		}
		if (endPoint < 1)
		{
			error = 3;
		}
		if (startPoint > 1)
		{
			error = 5;
		}
		if (endPoint > 1)
		{
			error = 6;
		}
	}

	//if no errors have been flagged, run the function to solve the maze
	if (error == 0)
	{
		error = mazeSolver(maze, lineLength);
	}

	//if an error has occured, print a correlating error message
	switch (error)
	{
	case 1:
		std::cout << "The file name or location you have entered is incorrect or invalid.\n";
		break;
	case 2:
		std::cout << "The selected maze has no start point.\n";
		break;
	case 3:
		std::cout << "The selected maze has no end point.\n";
		break;
	case 4:
		std::cout << "The selected maze contains invalid characters.\n";
		break;
	case 5:
		std::cout << "The selected maze contains multiple start points.\n";
		break;
	case 6:
		std::cout << "The selected maze contains multiple end points.\n";
		break;
	case 7:
		std::cout << "This maze has no route from the start to the end.\n";
		break;
	default:
		std::cout << "";
		break;
	}
	//clear the screen after a user input and return to the menu
	system("pause");
	system("cls");
}
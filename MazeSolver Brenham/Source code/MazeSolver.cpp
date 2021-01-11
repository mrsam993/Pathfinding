//include the header file to access all needed libraries and functions 
#include"Header.h"

//function that solves the maze
int mazeSolver(string maze, int length)
{
	//start recording time
	auto start = high_resolution_clock::now();
	//set variables for tracking memory usage
	MEMORYSTATUSEX memTotal;
	PROCESS_MEMORY_COUNTERS_EX memCurrent;
	
	//define variables for the function
	int error = 0;
	int startPosition = maze.find("2");
	int endPosition = maze.find("3");
	int destination;

	int freeSpace = 1;
	int pathsTested = 0;
	string testingPath;

	string directions[4];

	queue<string> possiblePaths;
	vector<int> oldDestinations;
	bool newDestination;
	possiblePaths.push("");

	//calculate the amount of free space in the maze
	for (int i = 0; i < maze.size(); i++)
	{
		if (maze[i] == '0')
		{
			freeSpace += 1;
		}
	}
	//add the start point the the old destinations queue
	oldDestinations.push_back(startPosition);
	//calculate which direction on the X axis should be checked first using the positions of the start and end point
	if ((startPosition - 1) % length < (endPosition - 1) % length)
	{
		directions[0] = "E";
		directions[2] = "W";
	}
	else
	{
		directions[0] = "W";
		directions[2] = "E";
	}
	//calculate which direction on the Y axis should be checked first using the positions of the start and end point
	if (ceil(startPosition / length) - ceil(endPosition / length) < 0)
	{
		directions[1] = "N";
		directions[3] = "S";
	}
	else
	{
		directions[1] = "S";
		directions[3] = "N";
	}
	//the main loop for creating paths, it is only broken if the destinaion of a created path is equal to B
	do
	{
		//reset varibles on the start of a new loop and create a new path to test
		newDestination = true;
		testingPath = possiblePaths.front() + directions[pathsTested % 4];
		//once a new path has been created run the function to find where the path ends
		destination = pathRoute(testingPath, maze, length, startPosition);
		//if the destination of the new path has already been reached by another path, change a bool to flag a repeat destination
		for (int i = 0; i < oldDestinations.size(); i++)
		{
			if (oldDestinations[i] == destination)
			{
				newDestination = false;
			}
		}
		//if the new path yeilds a new destination, add it to the queue for further itteration
		if (newDestination == true)
		{
			if (maze[destination] == '3' || maze[destination] == '0')
			{
				possiblePaths.push(possiblePaths.front() + directions[pathsTested % 4]);
				oldDestinations.push_back(destination);
			}
		}
		//after every 4 itterations of the loop, once all the cardinal directions have been added to the item at the front of the queue, remove it from the queue 
		if (pathsTested % 4 == 3 && possiblePaths.size() > 1)
		{
			possiblePaths.pop();
		}
		//increment the total paths tested variable and compare against the amount of free space times 4 to see if there is no solution to the maze 
		pathsTested += 1;
		if (pathsTested > freeSpace * 4)
		{
			//if there is no solution to the maze, set the destination to B in order to break the loop but flag an error
			destination = endPosition;
			error = 7;
		}
	} while (maze[destination] != '3');
	//if the destination is B and an error has not been flagged, print the solution
	if (error == 0)
	{
		std::cout << "The quickest route through the maze is:" << endl;
		std::cout << possiblePaths.back() << endl;
	}
	//stop recording time
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	//get the total amount of ram and virtual memory available to the computer
	memTotal.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memTotal);
	DWORDLONG VMTotal = memTotal.ullTotalPageFile;
	DWORDLONG RAMTotal = memTotal.ullTotalPhys;
	//get the total amount of ram and virtual memory available used by the program
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&memCurrent, sizeof(memCurrent));
	SIZE_T VMCurrent = memCurrent.PrivateUsage;
	SIZE_T RAMCurrent = memCurrent.WorkingSetSize;
	//get the ram and virtual memory useage as percentages
	float VMPercent = (float(VMCurrent) / float(VMTotal)) * 100;
	float RAMPercent = (float(RAMCurrent) / float(RAMTotal)) * 100;
	//print time taken
	std::cout << "Time taken: " << duration.count() << " microsceonds" << endl;
	//print out memory and ram usage
	std::cout << "Total Virtual Memory usage: " << VMCurrent << "/" << VMTotal << endl;
	std::cout << "As a percentage: " << VMPercent << "%" << endl;
	std::cout << "Total Random Access Memory usage: " << RAMCurrent << "/" << RAMTotal << endl;
	std::cout << "As a percentage: " << RAMPercent << "%" << endl;
	//end the funtion and return the error value
	return error;
}

//function for finding the destination of paths
int pathRoute(string path, string maze, int length, int position)
{
	//get the location of the start position as an error location
	int errorDestination;
	errorDestination = maze.find_first_of('2');
	bool error = false;
	//loop through each step of the path without checking for errors as we know these old steps have already been checked
	for (int i = 0; i < (path.length() - 1); i++)
	{
		switch (path[i])
		{
		case 'N':
			position -= length;
			break;
		case 'S':
			position += length;
			break;
		case 'E':
			position += 1;
			break;
		case 'W':
			position -= 1;
			break;
		default:
			break;
		}
	}
	//if the next move places the user outside the maze or allows them to wrap around the maze, set the destination to the error location and flag an error
	if (position <= length && path.back() == 'N')
	{
		position = errorDestination;
		error = true;
	}
	else if (position >= (maze.size() - length) && path.back() == 'S')
	{
		position = errorDestination;
		error = true;
	}
	else if ((position + 1) % length == 0 && path.back() == 'E')
	{
		position = errorDestination;
		error = true;
	}
	else if ((position + 1) % length == 1 && path.back() == 'W')
	{
		position = errorDestination;
		error = true;
	}
	//if no errors have been flagged, route the final step
	if (error == false)
	{
		switch (path.back())
		{
		case 'N':
			position -= length;
			break;
		case 'S':
			position += length;
			break;
		case 'E':
			position += 1;
			break;
		case 'W':
			position -= 1;
			break;
		default:
			break;
		}
	}
	//return the final destination
	return position;
}
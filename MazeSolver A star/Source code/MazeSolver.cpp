//include the header file to access all needed libraries and functions 
#include"Header.h"

//function that solves the maze
int mazeSolver(string maze, int length)
{
	//start recording time
	auto start = high_resolution_clock::now();

	//define variables for the function
	int error = 0;
	int startPosition = maze.find("2");
	int endPosition = maze.find("3");
	int height = maze.length() / length;
	bool added = false;
	string readablePath;

	//define values for every space in the maze
	struct space
	{
		int position;
		int startDis;
		int endDis;
		int cost;
		bool obstacle = false;
		bool visited = false;
		space* parent;
		vector<space*> connections;
	};

	//create and array to hold the spaces and define things that use the spaces
	space *spaces = nullptr;
	space* startSpace = nullptr;
	space* endSpace = nullptr;
	space* currentSpace = nullptr;
	spaces = new space[maze.length()];

	//set values of spaces
	for (int i = 0; i < maze.length(); i++)
	{
		spaces[i].position = i;
		spaces[i].startDis = INFINITE;
		spaces[i].endDis = INFINITE;
		spaces[i].cost = INFINITE;
		if (maze[i] == '1')
		{
			spaces[i].obstacle = true;
		}
		spaces[i].visited = false;
		spaces[i].parent = nullptr;
	}

	//set node connections
	for (int i = 0; i < maze.length(); i++)
	{
		if (spaces[i].obstacle == false)
		{
			if (spaces[i].position > (length - 0.001))
			{
				if (spaces[i - length].obstacle == false)
				{
					//add up connection if it does not exceed maze boundraies and is not an obstacle 
					spaces[i].connections.push_back(&spaces[i - length]);
				}
			}
			if (spaces[i].position < maze.length() - length)
			{
				if (spaces[i + length].obstacle == false)
				{
					//add down connection if it does not exceed maze boundraies and is not an obstacle 
					spaces[i].connections.push_back(&spaces[i + length]);
				}
			}
			if (spaces[i].position % length != (length - 1))
			{
				if (spaces[i + 1].obstacle == false)
				{
					//add right connection if it does not exceed maze boundraies and is not an obstacle 
					spaces[i].connections.push_back(&spaces[i + 1]);
				}
			}
			if (spaces[i].position % length != 0)
			{
				if (spaces[i - 1].obstacle == false)
				{
					//add left connection if it does not exceed maze boundraies and is not an obstacle 
					spaces[i].connections.push_back(&spaces[i - 1]);
				}
			}
		}
	}

	//pathfind
	startSpace = &spaces[startPosition];
	endSpace = &spaces[endPosition];
	currentSpace = startSpace;
	//set list of open spaces
	vector<space*> openSpace;
	//set list of closed spaces
	vector<space*> closedSpace;
	//calculate cost of starting space
	startSpace->startDis = 0;
	startSpace->endDis = (fabs((endPosition % length)) - fabs((spaces[startPosition].position % length))) + (fabs((endPosition / length)) - fabs((spaces[startPosition].position / length)));
	startSpace->cost = startSpace->startDis + startSpace->endDis;
	//add start space to open list
	openSpace.insert(openSpace.begin(), startSpace);
	//continue while open list is not empty and a solution has not been found
	while (!openSpace.empty() && currentSpace->position != endPosition)
	{
		//set current space to be at the front of the list and set it to visited
		currentSpace = openSpace.front();
		currentSpace->visited = true;
		//adjust all connections if not previously visited
		for (auto connection : currentSpace->connections) 
		{
			if (connection->visited == false)
			{
				if (connection->parent == nullptr)
				{
					connection->parent = currentSpace;
				}
				else if (currentSpace->cost < connection->parent->cost)
				{
					connection->parent = currentSpace;
				}

				//calculate costs of all connections
				connection->startDis = fabs((startPosition % length)) - fabs((connection->position % length)) + fabs((startPosition / length)) - fabs((connection->position / length));
				connection->endDis = fabs((endPosition % length)) - fabs((connection->position % length)) + fabs((endPosition / length)) - fabs((connection->position / length));
				connection->cost = fabs(connection->startDis + connection->endDis);
				//add connections to list in order of cost
				for (int i = 1; i < openSpace.size(); i++)
				{
					if (connection->cost < openSpace[i]->cost)
					{
						openSpace.insert(openSpace.begin() + i, connection);
						added = true;
						i += openSpace.size();
					}
				}
				if (added == false)
				{
					openSpace.push_back(connection);
				}
				added = false;
			}
		}
		//add current space to the closed list
		closedSpace.insert(closedSpace.begin(), currentSpace);
		openSpace.erase(openSpace.begin());
		//increment spaces tested
	}

	//print route or return error
	if (currentSpace->position == endPosition)
	{
		while (currentSpace->parent != nullptr)
		{
			if (currentSpace->position - currentSpace->parent->position == -length)
			{
				readablePath = "Up " + readablePath;
			}
			if (currentSpace->position - currentSpace->parent->position == length)
			{
				readablePath = "Down " + readablePath;
			}
			if (currentSpace->position - currentSpace->parent->position == +1)
			{
				readablePath = "Right " + readablePath;
			}
			if (currentSpace->position - currentSpace->parent->position == -1)
			{
				readablePath = "Left " + readablePath;
			}
			currentSpace = currentSpace->parent;
		}
		std::cout << "Route found: " << readablePath << endl;
	}
	else 
	{
		error = 7;
	}
	//stop recording time
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	//print spaces checked and time taken
	std::cout << "Spaces checked: " << closedSpace.size() - 1 << endl;
	std::cout << "Time taken: " << duration.count() << " microsceonds" << endl;
	//return error value
	return error;
}
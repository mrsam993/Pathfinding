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
	bool solution = false;
	int maxTries = maze.length() * 1000;
	int tries = 0;
	std::vector<int> destinations;

	int gene;
	int chromosomeLength;
	int chromosomeLengthX;
	int chromosomeLengthY;
	int chromosomeIncrease;
	int GPL = 2; 
	string Chromosome1;
	string Chromosome2;
	string Chromosome3;
	string Chromosome4;
	string parent1;
	string parent2;
	string parent3;
	string parent4;
	int destination1;
	int destination2;
	int destination3;
	int destination4;
	float fitness1;
	float fitness2;
	float fitness3;
	float fitness4;
	float fitnessTotal;
	float parentSelector;
	int selectedParent1;
	int selectedParent2;
	float crossoverRate;
	float mutation;
	bool validParent = true;

	string correctPath;
	int generation = 0;

	//set a seed to cause randomization
	srand(time(NULL));

	//set initial chromosome length
	chromosomeLengthX = 2 * (endPosition % length) - (startPosition % length);
	if (chromosomeLengthX < 0)
	{
		chromosomeLengthX *= -1;
	}
	chromosomeLengthY = 2 * (floor(endPosition / length) - floor(startPosition / length));
	if (chromosomeLengthY < 0)
	{
		chromosomeLengthY *= -1;
	}
	chromosomeLength = chromosomeLengthX + chromosomeLengthY;
	chromosomeIncrease = chromosomeLength * GPL;

	//create initial 4 chromosomes SET GOOD INITIAL LENGTH
	for (int i = 0; i < chromosomeLength; i++)
	{
		gene = rand() % 2;
		Chromosome1 = Chromosome1 + to_string(gene);
		gene = rand() % 2;
		Chromosome2 = Chromosome2 + to_string(gene);
		gene = rand() % 2;
		Chromosome3 = Chromosome3 + to_string(gene);
		gene = rand() % 2;
		Chromosome4 = Chromosome4 + to_string(gene);
	}

	//loop until solution is found
	do 
	{
		//check if chromosome length needs to be increased
		if (generation == chromosomeIncrease)
		{
			for (int i = 0; i < 2; i++)
			{
				gene = rand() % 2;
				Chromosome1 = Chromosome1 + to_string(gene);
				gene = rand() % 2;
				Chromosome2 = Chromosome2 + to_string(gene);
				gene = rand() % 2;
				Chromosome3 = Chromosome3 + to_string(gene);
				gene = rand() % 2;
				Chromosome4 = Chromosome4 + to_string(gene);
			}
			chromosomeIncrease += Chromosome1.length() * GPL;
		}
		//test all current chromosomes
		destination1 = pathRoute(Chromosome1, maze, length, startPosition, false);
		destination2 = pathRoute(Chromosome2, maze, length, startPosition, false);
		destination3 = pathRoute(Chromosome3, maze, length, startPosition, false);
		destination4 = pathRoute(Chromosome4, maze, length, startPosition, false);
		generation += 1;
		//add destinations to vector
		if (std::count(destinations.begin(), destinations.end(), destination1))
		{
			//if no new destination is found, increase counter
			tries += 1;
		}
		else
		{
			//if a new destination is found reset the counter and it to the vector 
			tries = 0;
			destinations.insert(destinations.begin(), destination1);
		}

		if (std::count(destinations.begin(), destinations.end(), destination2))
		{
			//if no new destination is found, increase counter
			tries += 1;
		}
		else
		{
			//if a new destination is found reset the counter and it to the vector 
			tries = 0;
			destinations.insert(destinations.begin(), destination2);
		}

		if (std::count(destinations.begin(), destinations.end(), destination3))
		{
			//if no new destination is found, increase counter
			tries += 1;
		}
		else
		{
			//if a new destination is found reset the counter and it to the vector 
			tries = 0;
			destinations.insert(destinations.begin(), destination3);
		}

		if (std::count(destinations.begin(), destinations.end(), destination4))
		{
			//if no new destination is found, increase counter
			tries += 1;
		}
		else
		{
			//if a new destination is found reset the counter and it to the vector 
			tries = 0;
			destinations.insert(destinations.begin(), destination4);
		}

		//check if any paths have reached the goal
		if (destination1 == endPosition)
		{
			solution = true;
		}
		if (destination2 == endPosition)
		{
			solution = true;
		}
		if (destination3 == endPosition)
		{
			solution = true;
		}
		if (destination4 == endPosition)
		{
			solution = true;
		}
		//if a solution hasn't been found create new chromosomes
		if (solution == false)
		{
			//find fitness of each chromosome
			fitness1 = 1 / ((fabs((endPosition % length) - (destination1 % length)) + fabs(floor(endPosition / length) - floor(destination1 / length))) + 1);
			fitness2 = 1 / ((fabs((endPosition % length) - (destination2 % length)) + fabs(floor(endPosition / length) - floor(destination2 / length))) + 1);
			fitness3 = 1 / ((fabs((endPosition % length) - (destination3 % length)) + fabs(floor(endPosition / length) - floor(destination3 / length))) + 1);
			fitness4 = 1 / ((fabs((endPosition % length) - (destination4 % length)) + fabs(floor(endPosition / length) - floor(destination4 / length))) + 1);
			fitnessTotal = fitness1 + fitness2 + fitness3 + fitness4;
			//choose parent 1 randomly
			parentSelector = (rand()) / static_cast <float> (RAND_MAX/fitnessTotal);
			if (parentSelector >= 0 && parentSelector < fitness1)
			{
				parent1 = Chromosome1;
				selectedParent1 = 1;
			}
			else if (parentSelector >= fitness1 && parentSelector < (fitness1 + fitness2))
			{
				parent1 = Chromosome2;
				selectedParent1 = 2;
			}
			else if (parentSelector >= (fitness1 + fitness2) && parentSelector < (fitness1 + fitness2 + fitness3))
			{
				parent1 = Chromosome3;
				selectedParent1 = 3;
			}
			else 
			{
				parent1 = Chromosome4;
				selectedParent1 = 7;
			}
			//choose parent 2 randomly and ensure it is not the same as the first parent
			do 
			{
				validParent = true;
				parentSelector = (rand()) / static_cast <float> (RAND_MAX / fitnessTotal);
				if (parentSelector >= 0 && parentSelector < fitness1)
				{
					parent2 = Chromosome1;
					selectedParent2 = 1;
					if (selectedParent1 == 1)
					{
						validParent = false;
					}
				}
				else if (parentSelector >= fitness1 && parentSelector < (fitness1 + fitness2))
				{
					parent2 = Chromosome2;
					selectedParent2 = 2;
					if (selectedParent1 == 2)
					{
						validParent = false;
					}
				}
				else if (parentSelector >= (fitness1 + fitness2) && parentSelector < (fitness1 + fitness2 + fitness3))
				{
					parent2 = Chromosome3;
					selectedParent2 = 3;
					if (selectedParent1 == 3)
					{
						validParent = false;
					}
				}
				else
				{
					parent2 = Chromosome4;
					selectedParent2 = 7;
					if (selectedParent1 == 7)
					{
						validParent = false;
					}
				}
			} while (validParent == false);
			validParent = true;
			//select parents 3 and 4 using the info from the previously selected parents
			switch (10 - (selectedParent1 + selectedParent2))
			{
				case 7:
					parent3 = Chromosome3;
					parent4 = Chromosome4;
					break;
				case 6:
					parent3 = Chromosome2;
					parent4 = Chromosome4;
					break;
				case 2:
					parent3 = Chromosome2;
					parent4 = Chromosome3;
					break;
				case 5:
					parent3 = Chromosome1;
					parent4 = Chromosome4;
					break;
				case 1:
					parent3 = Chromosome1;
					parent4 = Chromosome3;
					break;
				case 0:
					parent3 = Chromosome1;
					parent4 = Chromosome2;
					break;
			}
			//use selected parents to create offspring of parent 1 and 2
			crossoverRate = rand() % parent1.length();
			for (int i = 0; i < parent1.length(); i++)
			{
				if (i < crossoverRate)
				{
					Chromosome1[i] = parent1[i];
					Chromosome2[i] = parent2[i];
				}
				else 
				{
					Chromosome2[i] = parent1[i];
					Chromosome1[i] = parent2[i];
				}
			}
			//use selected parents to create offspring of parent 3 and 4
			crossoverRate = rand() % parent1.length();
			for (int i = 0; i < parent1.length(); i++)
			{
				if (i < crossoverRate)
				{
					Chromosome3[i] = parent3[i];
					Chromosome4[i] = parent4[i];
				}
				else
				{
					Chromosome4[i] = parent3[i];
					Chromosome3[i] = parent4[i];
				}
			}
			//create mutation 
			mutation = rand() % 100;
			if (mutation < 2)
			{
				mutation = rand() % Chromosome1.length();
				if (Chromosome1[mutation] == '1')
				{
					Chromosome1.replace(mutation, 1, "0");
				}
				else
				{
					Chromosome3.replace(mutation, 1, "1");
				}
				mutation = rand() % Chromosome3.length();
				if (Chromosome3[mutation] == '1')
				{
					Chromosome3.replace(mutation, 1, "0");
				}
				else
				{
					Chromosome3.replace(mutation, 1, "1");
				}
			}
			//if the counter exceeds the maximum amount of attempts it is determined that there is no destination and the loop is broken
			if (tries >= maxTries)
			{
				solution = true;
				error = 7;
			}
		}
		//exit the loop if a solution has been found
	} while (solution == false);
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
	//print generation and time taken
	std::cout << "Generations: " << generation << endl;
	std::cout << "Time taken: " << duration.count() << " microsceonds" << endl;
	//print out memory and ram usage
	std::cout << "Total Virtual Memory usage: " << VMCurrent << "/" << VMTotal << endl;
	std::cout << "As a percentage: " << VMPercent << "%" << endl;
	std::cout << "Total Random Access Memory usage: " << RAMCurrent << "/" << RAMTotal << endl;
	std::cout << "As a percentage: " << RAMPercent << "%" << endl;
	//return the error value
	return error;
}


//function for finding the destination of paths
int pathRoute(string path, string maze, int length, int position, bool correct)
{
	//get the location of the start position as an error location
	int errorDestination = position;
	bool error = false;
	string step;
	string correctPath;
	//loop through each step of the path without checking for errors as we know these old steps have already been checked
	for (int i = 0; i < path.length(); i+=2)
	{
		step = path[i];
		step = step + path[i + 1];
		//north
		if (step == "11")
		{
			//only make next move if it won't put user outside of boundaries and there is no obstacle in the way
			if (position > length)
			{
				if (maze[position -= length] != '1')
				{
					//if step is valid add it to the potential correct path
					correctPath += "Up ";
				}
				else 
				{
					position += length;
				}
			}
		}
		//south
		else if (step == "00")
		{
			//only make next move if it won't put user outside of boundaries and there is no obstacle in the way
			if (position < (maze.size() - length))
			{
				if (maze[position += length] != '1')
				{
					//if step is valid add it to the potential correct path
					correctPath += "Down ";
				}
				else
				{
					position -= length;
				}
			}
		}
		//east
		else if (step == "01")
		{
			//only make next move if it won't put user outside of boundaries and there is no obstacle in the way
			if ((position + 1) % length != 0)
			{
				if (maze[position += 1] != '1')
				{
					//if step is valid add it to the potential correct path
					correctPath += "Right ";
				}
				else
				{
					position -= 1;
				}
			}
		}
		//west
		else if (step == "10")
		{
			//only make next move if it won't put user outside of boundaries and there is no obstacle in the way
			if ((position + 1) % length != 1)
			{
				if (maze[position -= 1] != '1')
				{
					//if step is valid add it to the potential correct path
					correctPath += "Left ";
				}
				else
				{
					position += 1;
				}
			}
		}
		//if any step lands on the destination, print the current correct path and break the loop
		if (position == maze.find("3"))
		{
			std::cout << "Route found: " << correctPath << endl;
			i += path.length();
		}
	}
	//return the final destination
	return position;
}
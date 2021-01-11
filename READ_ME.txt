These are my programs for maze solving, each algorithm has a different executable.
Below you will find details on my algorithm, code and testing split into sections.

===ASSUMPTIONS===
 When making this program I made a few assumptions which are listed below: 
  -The maze should be a rectangle or a square shape
  -The maze must not contain multiple start or end points
  -The program must have at least one start and one end point
  -The user is using a keyboard with English characters and numbers
  -The user can read English
  -The user is using windows

===OUTPUT===
 Each program has a slightly different output so I will break down what they mean.
 A star algorithm:
  -Route found: This is the first solution that is found and the steps you would take to reach the exit
   of the maze represented in steps like up, down, left or right.
  -Spaces tested: This algorith tests one space at a time so this is a record of how many spaces have been
   tested, inefficient spaces may be tested and ignored which results in the amount of tested spaces being 
   longer than the route that is found.
  -Time taken: This is a recording of the amount of time the algorithm has take to run the maze solving function,
   this number doesn't take into account time spent on the menu and only records the time the algorithm spends solving
   the maze.
 Genetic algorithm:
  -Route found: This is the first solution that is found and the steps you would take to reach the exit
   of the maze represented in steps like up, down, left or right.
  -Generations: This algorithm generates paths which are tested and crossbred to create new paths with the best elements
   of previous paths, each time these new paths are generated this is recorded as a new generation and the total amount
   of generations is output upon the mazes completion.
  -Time taken: This is a recording of the amount of time the algorithm has take to run the maze solving function,
   this number doesn't take into account time spent on the menu and only records the time the algorithm spends solving
   the maze.
 Brenhams algorithm:
  -Route found: This is the first solution that is found and the steps you would take to reach the exit of the maze, 
   unlike the other two algorithms the output is represented by singular letters that represent the cardinal directions
   N means north, S means south, E means east and W means west.
  -Time taken: This is a recording of the amount of time the algorithm has take to run the maze solving function,
   this number doesn't take into account time spent on the menu and only records the time the algorithm spends solving
   the maze.  

===INSTRUCTIONS===
 Instructions can be found inside each program but a copy of said instructions can also be read here.
 Instructions screen:
  -Each maze must be in the format of a .txt file
  -Each maze must have one start point represented by an '2', and one end point represented by a '3'
  -Empty spaces must be represented by a '0', and obstacles must be represented by a '1' 
  -The maze must begin with the two numbers that are the number of rows and the number of columns
  -Mazes must not contain any characters apart from the aforementioned ones
  -There must be a space dividing each number
  -All rows of the maze must be the same size and all columns must be the same size
  -The maze can be a rectangle
  -The maze does not have to have a solution
  -An example maze called 'example' can be found in the directory for clarification
 Maze opening instructions:
  -Enter the name of the file you would like to open
  -If the maze location is in the same file as the program, enter the file name
  -If the file is not in the program folder, enter the file location
  -You do not need to add the file extention when entering the file name
  -EXAMPLE: quickest_route_1 or C:\\temp\maze";

===BUILDING AND RUNNING===
 There are three ways to run the program:
  -Open the .exe found inside each file
  -Open the command prompt, navigate to the location and.exe and input the name of the .exe (for example Genetic.exe)
  -Open the .sln file in the source code folder and run the program in visual studio
 The program is already built in the form of the .exe and a new build is saved to the debug folder in the
 source code folder every time the program is changed 
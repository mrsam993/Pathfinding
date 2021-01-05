//define and prototype everything needed in one header file
#pragma once
#ifndef _DELAY_MS_H_
#define _DELAY_MS_H_

//include all needed libraries for the program
#include<windows.h>
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#include<deque>
#include<vector> 
#include<math.h>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cctype>
#include<chrono> 
using namespace std;
using namespace std::chrono;
//define all prototypes for funtions
void instructions();
void mazeSelector();
int mazeSolver(string maze, int length);
int pathRoute(string path, string maze, int length, int position, bool correct);
#endif
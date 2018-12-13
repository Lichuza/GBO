#pragma once
#include <cstdio>
#include <string>
#include <iostream>
#include<thread>
#include <fstream>
#include <sstream>
using namespace std;

class gnuPlot
{
public:
	gnuPlot();
	~gnuPlot();
	void command(const string &command);

private:
	FILE *gnuplotpipe;
};


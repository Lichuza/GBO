#include "gnuPlot.h"

gnuPlot::gnuPlot()
{
	gnuplotpipe = _popen("C:/gnuplot/bin/gnuplot.exe", "w");

	if (!gnuplotpipe)
	{
		cerr << ("Gnuplot not found !");
	}
}

gnuPlot::~gnuPlot()
{
	fprintf(gnuplotpipe, "exit\n");
	_pclose(gnuplotpipe);
}


void gnuPlot::command(const string &command)
{
	fprintf(gnuplotpipe, "%s\n", command.c_str());
	fflush(gnuplotpipe);
}


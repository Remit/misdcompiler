#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "CommonTypesAndConstants.h"
#include <time.h>
#include <math.h>
#include <fstream>

class TimeStamp
{
public:
	TimeStamp(std::string a_file_to_print) : file_to_print(a_file_to_print) {}
	TimeStamp();
	~TimeStamp();
	void startTime(std::string prog_file, int iteration, std::string phase_name);
	void endTime(std::string prog_file, int iteration, std::string phase_name);
	void printDurations();
	
private:
	std::string file_to_print;
	std::map< std::string, clock_t > timestamps;
	std::map< std::string, float > durations; //in seconds
};

#endif
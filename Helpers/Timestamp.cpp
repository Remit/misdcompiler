#include "../include/Timestamp.h"

TimeStamp::TimeStamp() {
	file_to_print = "";
}

TimeStamp::~TimeStamp() {
	
}

void TimeStamp::startTime(std::string prog_file, int iteration, std::string phase_name) {
	time_t start;
	time(&start);
	std::string key = prog_file + ";" + std::to_string(iteration) + ";" + phase_name;
	timestamps[key] = start;
}

void TimeStamp::endTime(std::string prog_file, int iteration, std::string phase_name) {
	time_t end;
	time(&end);
	std::string key = prog_file + ";" + std::to_string(iteration) + ";" + phase_name;
	time_t start = timestamps[key];
	durations[key] = difftime(end,start);
}

void TimeStamp::printDurations() {
	if(file_to_print.compare("") != 0) {
		std::ofstream ofs;
		ofs.open (file_to_print.c_str(), std::ofstream::out | std::ofstream::app);
		std::map< std::string, double >::iterator it;
		for(it = durations.begin(); it != durations.end(); it++) {
			ofs << it->first << ";" << std::trunc(100 * it->second) / 100 << std::endl;
		}
		ofs.close();
	} else {
		std::cout << "Filename for time durations storage is not specified." << std::endl;
	}
}
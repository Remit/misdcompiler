#include "../include/Timestamp.h"

TimeStamp::TimeStamp() {
	file_to_print = "";
}

TimeStamp::~TimeStamp() {
	
}

void TimeStamp::startTime(std::string prog_file, int iteration, std::string phase_name) {
	clock_t start = clock();
	std::string key = prog_file + ";" + std::to_string(iteration) + ";" + phase_name;
	timestamps[key] = start;
}

void TimeStamp::endTime(std::string prog_file, int iteration, std::string phase_name) {
	clock_t end = clock();
	std::string key = prog_file + ";" + std::to_string(iteration) + ";" + phase_name;
	clock_t start = timestamps[key];
	durations[key] = float(end - start) / CLOCKS_PER_SEC;
}

void TimeStamp::printDurations() {
	if(file_to_print.compare("") != 0) {
		std::ofstream ofs;
		ofs.open (file_to_print.c_str(), std::ofstream::out | std::ofstream::app);
		std::map< std::string, float >::iterator it;
		ofs.precision(6);
		for(it = durations.begin(); it != durations.end(); it++) {
			ofs << std::fixed << it->first << ";" << it->second << std::endl;
		}
		ofs.close();
	} else {
		std::cout << "Filename for time durations storage is not specified." << std::endl;
	}
}
#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    
    long hour, min;
    string sec;
    string elapsedTime;
    hour = seconds/3600;
	seconds = seconds%3600;
	min = seconds/60;
	seconds= seconds%60;
    if (seconds<10){
        sec = "0"+ std::to_string(seconds);
    }
    else {
        sec = std::to_string(seconds);
    }
	//sec = seconds; 
    elapsedTime = std::to_string(hour)+":"+std::to_string(min)+":"+sec;
    
    return elapsedTime;
}
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;
Process::Process(int pid):pid_(pid){}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    string key,value,line,ram,token;
    std::vector<string> dataVec;
    float uTime,sTime,cuTime,csTime,startTime,totalTime,seconds;
    std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid_)+LinuxParser::kStatFilename);
    
    if(stream.is_open()){
        getline(stream,line);
        std::istringstream linestream(line);
        for(int i=0;i<25;i++){
            linestream>>token;
            if (i == 13){
                //std::cout<< token;
                uTime = std::stof(token);
            }
            else if(i == 14){
                sTime = std::stof(token);
            }
            else if(i==15){
                cuTime = std::stof(token);
        //csTime = std::stof(dataVec[16]);
            }
            else if(i == 16){
                csTime = std::stof(token);
            }
            else if(i == 21){
                startTime = std::stof(token);
            }
        }
        //uTime = std::stof(dataVec[13]);
        //sTime = std::stof(dataVec[14]);
        //cuTime = std::stof(dataVec[15]);
        //csTime = std::stof(dataVec[16]);
        //startTime = std::stof(dataVec[21]);
        totalTime = uTime + sTime;
        totalTime = totalTime + cuTime + csTime;
        seconds = Process::UpTime() - (float(startTime)/sysconf(_SC_CLK_TCK));
        cpuUtilization_ = (totalTime/sysconf(_SC_CLK_TCK)/seconds);

    }
    //cpuUtilization = uTime;
    
    return cpuUtilization_; }

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(pid_);
 }

// TODO: Return this process's memory utilization
string Process::Ram() {
    return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User() { 

    return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return  cpuUtilization_ < a.cpuUtilization_ ;}

bool Process::operator>(Process const& a[[maybe_unused]]) const { return true; }
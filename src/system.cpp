#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    
    vector<int> pidList = LinuxParser::Pids();
    //processes_.clear();
    
    for(int i:pidList){
        Process proc(i);
        processes_.emplace_back(proc);
    }
    std::sort(processes_.begin(),processes_.end());
    //std::sort(processes_.end(),processes_.begin());
    //    return (p1>p2);
    //});
    
    return processes_; 
    }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    std::string kernel;
    kernel = LinuxParser::Kernel();
    return kernel; 
    }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    float memoryUtilization = LinuxParser::MemoryUtilization();
    return memoryUtilization;
    }

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    std::string operatingSystem;
    operatingSystem = LinuxParser::OperatingSystem();
    return operatingSystem;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    int runningProcesses;
    runningProcesses = LinuxParser::RunningProcesses();
    return runningProcesses;
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    int totalProcesses;
    totalProcesses = LinuxParser::TotalProcesses();
    return totalProcesses;
 }

// TODO: Return the number of seconds since the system started running
long System::UpTime() {
     long upTime;
 
     upTime = LinuxParser::UpTime();
     return upTime; 
     }
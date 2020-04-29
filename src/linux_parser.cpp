#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;

using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float memoryUtilization;
  vector<string> memInfo_vec;
  string key,value,line;
  long MemTotal, MemFree,  Buffers;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    

    for (int i = 0;i<4;i++) {
      std::getline(stream, line);
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        memInfo_vec.push_back(value);
          
        }
    }
    string::size_type sz;   // alias of size_t

    MemTotal = std::stol(memInfo_vec[0],&sz);
    MemFree = std::stol(memInfo_vec[1],&sz);
    //MemAvailable = std::stol (memInfo_vec[2],&sz);
    Buffers = std::stol(memInfo_vec[3],&sz);

    memoryUtilization = (MemTotal - MemFree-Buffers)/1.0/MemTotal;
  }
  return memoryUtilization;
 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long upTime;
  string line,uptimeSystemStr,uptimeIdleStr;
  std::ifstream stream(kProcDirectory +kUptimeFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream >> uptimeSystemStr >> uptimeIdleStr;
    string::size_type sz;   // alias of size_t
    upTime = std::stol(uptimeSystemStr,&sz);

  }
  return upTime;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  
  int totalProcesses;
  string line,key,value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "processes"){
      
        totalProcesses = std::stoi(value);
      }

    }
    
  }

  return totalProcesses;

}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int runningProcesses;
  string line,key,value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "procs_running"){
      
        runningProcesses = std::stoi(value);
      }

    }
    
  }

  return runningProcesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string command,line;
    std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kCmdlineFilename);
    if(stream.is_open()){
        getline(stream,line);
        command = line;
    }
    else{
        command = "";
    }
    return command;
 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string key,value,line,ram;
    int value_int;
    std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatusFilename);
    if(stream.is_open()){
        while(getline(stream,line)){
            std::istringstream linestream(line);
            while(linestream>>key>>value){
                if(key == "VmSize:"){
                    value_int = std::stoi(value);
                    value_int = value_int/1024;
                    value = std::to_string(value_int);
                    ram = value;
                }
            }
        }

    }
    return ram; 
 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string uid,line,key,value;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if(stream.is_open()){
    while (std::getline(stream,line))
    {
      std::istringstream linestream(line);
      while(linestream>>key>>value)
      {
        if(key == "Uid:")
        {
          uid = value;
        }
      }
    }
    
  }
  
  return uid; }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = LinuxParser::Uid(pid); 
  string line; 
  string user; 
  std::ifstream stream(kPasswordPath); 
  if(stream.is_open()){ 
    while(std::getline(stream,line)){ 
      if(line.find(uid) != std::string::npos){ 
        user = line.substr(0,line.find(":")); break;
      } 
    } 
  } 
  return user;  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  long uptime;
  string line;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  if(stream.is_open()){
    getline(stream,line);

    //std::string text = "Let me split this into words";
 
    std::istringstream iss(line);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
    uptime = std::stol(results[21]);
  }
  
  return uptime;
 }
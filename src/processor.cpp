#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float utilization;
    long usertime,niceTime,idealTime,systemTime,virtualTime,totalTime;
    std::string line,cpuIndex;
    std::vector<std::string> CPUDataStr(10,"");
    std::vector<long> CPUData(10,0);
    std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename); 
    if (stream.is_open()){
        std::getline(stream,line);
        std::istringstream linestream(line);
        linestream>>cpuIndex;
        for (int i =0; i<10;i++){
            linestream>>CPUDataStr[i];
            CPUData[i] = std::stof(CPUDataStr[i]);

        }
        usertime = CPUData[0]-CPUData[8];
        niceTime = CPUData[1]-CPUData[9];
        idealTime = CPUData[3]+CPUData[4];
        systemTime = CPUData[2]+CPUData[5]+CPUData[6];
        virtualTime = CPUData[9]+CPUData[10];
        totalTime = usertime + niceTime + idealTime + systemTime + virtualTime;

        utilization = float(totalTime - idealTime)/totalTime;
    }
    return utilization; }
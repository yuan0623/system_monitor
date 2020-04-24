#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float utilization,usertime,niceTime,idealTime,systemTime,virtualTime;
    std::string line,cpuIndex;
    std::vector<std::string> CPUDataStr(10,"");
    std::vector<float> CPUData(10,0.0);
    std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename); 
    if (stream.is_open()){
        std::getline(stream,line);
        std::istringstream linestream(line);
        linestream>>cpuIndex;
        for (int i =0; i<10;i++){
            linestream>>CPUDataStr[i];
            CPUData[i] = std::stof(CPUDataStr[i]);

        }

    }
    return utilization; }
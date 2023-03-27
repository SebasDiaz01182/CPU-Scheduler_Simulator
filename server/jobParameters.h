#ifndef JOBPARAMETERS_H
#define JOBPARAMETERS_H
#include "cpuScheduler.h"
typedef struct JobParameters {
    int socket; //server socket
    struct ProcessList * processes; //list of processes
    struct CpuScheduler * scheduler; //cpu scheduler

}jobParameters;

#endif
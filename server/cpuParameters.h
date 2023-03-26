#ifndef CPUPARAMETERS_H
#define CPUPARAMETERS_H


typedef struct CpuParameters{
    struct CpuScheduler *scheduler;
    struct ProcessList* processList;
    struct ProcessList* finishedList;
    int quantum;
}CpuParameters;
#endif
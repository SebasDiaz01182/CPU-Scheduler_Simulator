#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H
#include "processNode.h"
typedef struct CpuScheduler {
    int inactive; //CPU inactive time

}CpuScheduler;
void *fifoAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList);
void *sjfAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList);
void *hpfAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList);
void *rrAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList,int quantum);

#endif
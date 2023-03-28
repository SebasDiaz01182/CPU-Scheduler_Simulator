#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H
#include "processNode.h"
typedef struct CpuScheduler {
    int inactive; //CPU inactive time
    int timer; //CPU timer
}CpuScheduler;
void *fifoAnalysis(void *arg);
void *sjfAnalysis(void *arg);
void *hpfAnalysis(void *arg);
void *rrAnalysis(void *arg);
void getReport(ProcessList *list,CpuScheduler *scheduler);

#endif
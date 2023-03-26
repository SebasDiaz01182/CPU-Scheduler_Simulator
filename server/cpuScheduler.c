#include "cpuScheduler.h"
#include "processNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *fifoAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList){
    //TODO
    

    int timer = 0;
    while(1){
        ProcessNode* node = getFirstProcess(processList);
        if(node == NULL){
            scheduler->inactive += 1;
            sleep(1);
            printf("Empty List %d\n",timer);
        }
        else{
            printf("Process found: %d\n",timer);
            int sleepTime = node->burst;
            sleep(sleepTime);
            timer += sleepTime;
            node->exit = timer;
            removeProcess(processList,node);
            addProcess(finishedList,node);
            
        }
    }
}
void *sfjAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList){
    //TODO
}
void *hpfAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList){
    //TODO
}
void *rrAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList,int quantum){
    //TODO
}

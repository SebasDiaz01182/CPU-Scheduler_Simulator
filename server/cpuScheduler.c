#include "cpuScheduler.h"
#include "cpuParameters.h"
#include "processNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *fifoAnalysis(void *arg){
    //TODO
    struct CpuParameters * parameters = (struct CpuParameters*)arg;
    struct CpuScheduler * scheduler = parameters->scheduler;
    struct ProcessList * processList = parameters->processList;
    struct ProcessList * finishedList = parameters->finishedList;
    ProcessNode* node;
    while(1){
        node = getFirstProcess(processList);
        if(node == NULL){
            scheduler->timer += 1;
            scheduler->inactive += 1;
            sleep(1);
            printf("Empty List %d\n",scheduler->timer);
        }
        else{
            printf("Process found: %d\n",scheduler->timer);
            int sleepTime = node->burst;
            sleep(sleepTime);
            scheduler->timer += sleepTime;
            node->exit = scheduler->timer;
            removeProcess(processList,node);
            addProcess(finishedList,node);
        }
    }
}
void *sjfAnalysis(void *arg){

    struct CpuParameters * parameters = (struct CpuParameters*)arg;
    struct CpuScheduler * scheduler = parameters->scheduler;
    struct ProcessList * processList = parameters->processList;
    struct ProcessList * finishedList = parameters->finishedList;

    ProcessNode* node;
    while(1){
        node = getSJFProcess(processList);
        if(node == NULL){
            scheduler->timer += 1;
            scheduler->inactive += 1;
            sleep(1);
            printf("Empty List %d\n",scheduler->timer);
        }
        else{
            printf("Process found: %d\n",scheduler->timer);
            int sleepTime = node->burst;
            sleep(sleepTime);
            scheduler->timer += sleepTime;
            node->exit = scheduler->timer;
            removeProcess(processList,node);
            addProcess(finishedList,node);
        }
    }
}
void *hpfAnalysis(void *arg){
    
    struct CpuParameters * parameters = (struct CpuParameters*)arg;
    struct CpuScheduler * scheduler = parameters->scheduler;
    struct ProcessList * processList = parameters->processList;
    struct ProcessList * finishedList = parameters->finishedList;

    
    ProcessNode* node;

    while(1){
       node = getHPFProcess(processList);
        if(node == NULL){
            scheduler->timer += 1;
            scheduler->inactive += 1;
            sleep(1);
            printf("Empty List %d\n",scheduler->timer);
        }
        else{
            printf("Process found: %d\n",scheduler->timer);
            int sleepTime = node->burst;
            sleep(sleepTime);
            scheduler->timer += sleepTime;
            node->exit = scheduler->timer;
            removeProcess(processList,node);
            addProcess(finishedList,node);
        }
    }
}
void *rrAnalysis(void *arg){
    
    struct CpuParameters * parameters = (struct CpuParameters*)arg;
    struct CpuScheduler * scheduler = parameters->scheduler;
    struct ProcessList * processList = parameters->processList;
    struct ProcessList * finishedList = parameters->finishedList;
    int quantum = parameters->quantum;
    

    ProcessNode* node;
    while(1){
        node = getFirstProcess(processList);
        if(node == NULL){
            scheduler->timer += 1;
            scheduler->inactive += 1;
            sleep(1);
            printf("Empty List %d\n",scheduler->timer);
        }
        else{
            if(node->remainingBurst > quantum){
                printf("Process found: %d\n",scheduler->timer);
                int sleepTime = quantum;
                sleep(sleepTime);
                scheduler->timer += sleepTime;
                node->remainingBurst -= quantum;
                //Move to next process 
            }else{
                printf("Process found: %d\n",scheduler->timer);
                int sleepTime = node->remainingBurst;
                sleep(sleepTime);
                scheduler->timer += sleepTime;
                node->exit = scheduler->timer;
                removeProcess(processList,node);
                addProcess(finishedList,node);
            }
            
        }
    }
}

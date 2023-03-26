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

   int timer = 0;
   ProcessNode* node = getFirstProcess(processList);
   int processQueue = sizeof(processList) / sizeof(struct ProcessNode);
   qsort(processList, processQueue, sizeof(struct ProcessNode), sortByBurst());

   while(1){
       node = getFirstProcess(processList);
        if(node == NULL){
            scheduler->inactive += 1;
            sleep(1);
            printf("Empty List %d\n",timer);
        }
        else{
            while (node != NULL) {
                if(node->arrive <= timer){
                    printf("Process found: %d\n",timer);
                    int sleepTime = node->burst;
                    sleep(sleepTime);
                    timer += sleepTime;
                    node->exit = timer;
                    removeProcess(processList,node);
                    addProcess(finishedList,node);
                    break;
                }
                node = node->next;
            }
        }
    }
}
void *hpfAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList){
    
    int timer = 0;
    ProcessNode* node = getFirstProcess(processList);
    int processQueue = sizeof(processList) / sizeof(struct ProcessNode);
    qsort(processList, processQueue, sizeof(struct ProcessNode), sortByPriority());

    while(1){
       node = getFirstProcess(processList);
        if(node == NULL){
            scheduler->inactive += 1;
            sleep(1);
            printf("Empty List %d\n",timer);
        }
        else{
            while (node != NULL) {
                if(node->arrive <= timer){
                    printf("Process found: %d\n",timer);
                    int sleepTime = node->burst;
                    sleep(sleepTime);
                    timer += sleepTime;
                    node->exit = timer;
                    removeProcess(processList,node);
                    addProcess(finishedList,node);
                    break;
                }
                node = node->next;
            }
        }
    }
}
void *rrAnalysis(CpuScheduler* scheduler,ProcessList* processList,ProcessList* finishedList,int quantum){
    
    int timer = 0;
    while(1){
        ProcessNode* node = getFirstProcess(processList);
        if(node == NULL){
            scheduler->inactive += 1;
            sleep(1);
            printf("Empty List %d\n",timer);
        }
        else{
            if(node->burst> quantum){
                printf("Process found: %d\n",timer);
                int sleepTime = quantum;
                sleep(sleepTime);
                timer += sleepTime;
                //Move to next process 
            }else{
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
}

#include "cpuScheduler.h"
#include "cpuParameters.h"

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
            
            int sleepTime = node->burst;
            while(sleepTime > 0){
                scheduler->timer +=1;
                sleep(1);
                sleepTime -=1;
            }
            node->exit = scheduler->timer;
            removeProcess(processList,node);
            addProcess(finishedList,node);
            //fix arrive time
            
            
            node = NULL;
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
            while(sleepTime > 0){
                scheduler->timer +=1;
                sleep(1);
                sleepTime -=1;
            }
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
            while(sleepTime > 0){
                scheduler->timer +=1;
                sleep(1);
                sleepTime -=1;
            }
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
    

    ProcessNode* node = NULL;
    while(1){
        node = getNextProcess(processList,node);
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
                while(sleepTime > 0){
                    scheduler->timer +=1;
                    sleep(1);
                    sleepTime -=1;
                }
                node->remainingBurst -= quantum;
                //Move to next process 
            }else{
                printf("Process found: %d\n",scheduler->timer);
                int sleepTime = node->remainingBurst;
                while(sleepTime > 0){
                    scheduler->timer +=1;
                    sleep(1);
                    sleepTime -=1;
                }
                node->exit = scheduler->timer;
                removeProcess(processList,node);
                addProcess(finishedList,node);
            }
            
        }
    }
}
void getReport(ProcessList *list, CpuScheduler * scheduler){
    ProcessNode * nodeTmp = list->first;
    int totalProcesses = getAmountItems(list);
    printf("Procesos ejecutados: %d\n", totalProcesses);
    printf("Tiempo CPU Ocioso: %d\n", scheduler->inactive);
    float WTAvg,TATAvg;
    int WTTotal = 0, TATTotal = 0;
    while (nodeTmp != NULL) {
        int TATTmp = nodeTmp->exit-nodeTmp->arrive;
        int WTTmp = TATTmp - nodeTmp->burst;
        WTTotal += WTTmp;
        TATTotal += TATTmp;

        printf("pid: %d Burst: %d Llegada: %d Salida: %d TAT: %d WT: %d\n",nodeTmp->pid,nodeTmp->burst,nodeTmp->arrive,nodeTmp->exit,TATTmp,WTTmp);
        nodeTmp = nodeTmp->next;
    }
    WTAvg = WTTotal/totalProcesses;
    TATAvg = TATTotal/totalProcesses;
    printf("Promedio de TAT: %f \nPromedio de WT: %f\n",TATAvg,WTAvg);

}
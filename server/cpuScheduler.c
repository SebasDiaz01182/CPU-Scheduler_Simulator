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
            printf("Proceso PID %d Burst %d Priority %d entra en ejecucion\n",node->pid,node->burst,node->priority);
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
            printf("Proceso terminado PID %d Burst %d Priority %d \n",node->pid,node->burst,node->priority);
            
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
            printf("Proceso PID %d Burst %d Priority %d entra en ejecucion\n",node->pid,node->burst,node->priority);
            int sleepTime = node->burst;
            while(sleepTime > 0){
                scheduler->timer +=1;
                sleep(1);
                sleepTime -=1;
            }
            node->exit = scheduler->timer;
            removeProcess(processList,node);
            addProcess(finishedList,node);
            printf("Proceso terminado PID %d Burst %d Priority %d \n",node->pid,node->burst,node->priority);
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
            printf("Proceso PID %d Burst %d Priority %d entra en ejecucion\n",node->pid,node->burst,node->priority);
            int sleepTime = node->burst;
            while(sleepTime > 0){
                scheduler->timer +=1;
                sleep(1);
                sleepTime -=1;
            }
            node->exit = scheduler->timer;
            removeProcess(processList,node);
            addProcess(finishedList,node);
            printf("Proceso terminado PID %d Burst %d Priority %d \n",node->pid,node->burst,node->priority);
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
                printf("Proceso PID %d Burst %d Priority %d entra en ejecucion\n",node->pid,node->burst,node->priority);
                int sleepTime = quantum;
                while(sleepTime > 0){
                    scheduler->timer +=1;
                    sleep(1);
                    sleepTime -=1;
                }
                node->remainingBurst -= quantum;
                printf("Proceso PID %d Burst %d Priority %d mantiene un burst de %d\n",node->pid,node->burst,node->priority,node->remainingBurst);
                //Move to next process 
            }else{
                printf("Proceso PID %d Burst %d Priority %d entra en ejecucion\n",node->pid,node->burst,node->priority);
                int sleepTime = node->remainingBurst;
                while(sleepTime > 0){
                    scheduler->timer +=1;
                    sleep(1);
                    sleepTime -=1;
                }
                node->exit = scheduler->timer;
                removeProcess(processList,node);
                addProcess(finishedList,node);
                printf("Proceso terminado PID %d Burst %d Priority %d \n",node->pid,node->burst,node->priority);
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
    float WTTotal = 0, TATTotal = 0;
    while (nodeTmp != NULL) {
        int TATTmp = nodeTmp->exit-nodeTmp->arrive;
        int WTTmp = TATTmp - nodeTmp->burst;
        WTTotal += WTTmp;
        TATTotal += TATTmp;

        printf("pid: %d Priority: %d Burst: %d Llegada: %d Salida: %d TAT: %d WT: %d\n",nodeTmp->pid,nodeTmp->priority,nodeTmp->burst,nodeTmp->arrive,nodeTmp->exit,TATTmp,WTTmp);
        nodeTmp = nodeTmp->next;
    }
    WTAvg = WTTotal/totalProcesses;
    TATAvg = TATTotal/totalProcesses;
    printf("Promedio de TAT: %f \nPromedio de WT: %f\n",TATAvg,WTAvg);

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "processNode.h"
#include "cpuScheduler.h"
#include "jobParameters.h"
#include "cpuParameters.h"


#define PORT 8080

void *threadServer(void* arg){
    struct JobParameters * parameters = (struct JobParameters*)arg;
    struct ProcessList * processListP = parameters->processes;
    struct ProcessList * finishedProcessListP = parameters->finishedProcesses;
    struct CpuScheduler * scheduler = parameters->scheduler;
    int newSocket = (int)parameters->socket;
    
    

    char buffer[1024] = {0};
    int valread;

    while(1){
        
        valread = read(newSocket, buffer, 1024);
        
        if(valread == 0){
            printf("Cliente desconectado %d\n", valread);
            return NULL;

        }
       
        
        
        const char delimiter[] = "  ";
        int burst;
        int priority;
        
        burst=atoi(strtok(buffer, delimiter));
        
        priority=atoi(strtok(NULL, delimiter));
        
        int pidTmp = getAmountItems(processListP)+getAmountItems(finishedProcessListP);
        
        
        addProcessP(processListP, burst, scheduler->timer, priority, pidTmp);
        char recievedMsg[256];

        sprintf(recievedMsg,"Se recibio el proceso PID %d Burst %d Priority %d",pidTmp,burst,priority);
        send(newSocket,recievedMsg,strlen(recievedMsg),0);
        //send confirmation

        
    }
}

void *socketConnections(void* arg){
    //struct ProcessList *list = (struct ProcessList*)arg;

    struct JobParameters * parameters = (struct JobParameters*)arg;
    struct ProcessList * list = parameters->processes;
    struct ProcessList * finishedList = parameters->finishedProcesses;
    

    int server, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    server = socket(AF_INET, SOCK_STREAM, 0);
    
    // Creating socket file descriptor
    if (server == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Attaching socket to the port 8080
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind the socket to the address and port number
    if (bind(server, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    
    while(1){
        // Start listening for connections from clients
        if (listen(server, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        //printf("Waiting for connections\n");
        new_socket = accept(server, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        //printf("Connected to server\n");
        pthread_t thread_id;
        struct JobParameters jobParametersThread = {new_socket,list,parameters->scheduler,finishedList};
        struct JobParameters * jobParametersThreadP = &jobParametersThread;

        
        pthread_create(&thread_id, NULL, threadServer, jobParametersThreadP);
        //printf("After Create");
        //pthread_join(thread_id, NULL);
        
    }
    // Accept connections from clients and send response
    
    
    
    

}

int main(int argc, char const *argv[]) {
    //Variables
    struct ProcessList processList = {NULL};
    struct ProcessList * processListP = &processList;

    struct ProcessList finishedList = {NULL};
    struct ProcessList * finishedListP = &finishedList;

    struct CpuScheduler scheduler = {0,0};
    struct CpuScheduler * schedulerP = &scheduler;

    struct CpuParameters cpuParameters = {schedulerP,processListP,finishedListP,0};
    struct CpuParameters * cpuParametersP = &cpuParameters;
    
    struct JobParameters jobParameters = {0,processListP,schedulerP,finishedListP};
    struct JobParameters * jobParametersP = &jobParameters;

    int quantum=0;
    int option;
    
    //display menu
    
    printf("Ingrese que modalidad desea utilizar \n1. FIFO\n2. SJF\n3. HPF\n4. Round Robin\n");
    scanf("%d",&option);
    if(option==1) {
        pthread_t threadIdCPU;
        pthread_create(&threadIdCPU, NULL, fifoAnalysis, cpuParametersP);
    }
    else if(option==2) {
        pthread_t threadIdCPU;
        pthread_create(&threadIdCPU, NULL, sjfAnalysis, cpuParametersP);
    }
    else if(option==3){
        pthread_t threadIdCPU;
        pthread_create(&threadIdCPU, NULL, hpfAnalysis, cpuParametersP);
    }
    else{
        printf("Ingrese el valor del quantum:\n");
        
        scanf("%d",&quantum);
        cpuParametersP->quantum = (int)quantum;
        pthread_t threadIdCPU;
        pthread_create(&threadIdCPU, NULL, rrAnalysis, cpuParametersP);

    }
    //start jobscheduler
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, socketConnections, jobParametersP);
    //TODO posible scanf para recibir el comando de reporte o de terminacion de la ejecucion.
    while(1){
        int command;
        scanf("%d",&command);
        if(command == 1){
            printList(processListP);
        }else{

            getReport(finishedListP,schedulerP);
            return 0;
        }
    }
    pthread_join(thread_id, NULL);
    return 0;
}

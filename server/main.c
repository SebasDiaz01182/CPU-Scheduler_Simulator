#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "processNode.h"
#include "cpuScheduler.h"


#define PORT 8080

void *threadServer(void* arg){
    int new_socket = *(int*)arg;
    char buffer[1024] = {0};
    int valread;

    while(1){
        valread = read(new_socket, buffer, 1024);
        if(valread == 0){
            printf("end of socket connection %d\n", valread);
            return NULL;

        }
        printf("%s,%d\n", buffer,valread);
    }
}

void *socketConnections(){
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
        printf("Waiting for connections\n");
        new_socket = accept(server, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Connected to server\n");
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, threadServer, &new_socket);
        //printf("After Create");
        //pthread_join(thread_id, NULL);
        printf("Thread Started\n");
    }
    // Accept connections from clients and send response
    
    
    
    

}

int main(int argc, char const *argv[]) {
    //create process list
    //display menu
    printf("Ingrese que modalidad desea utilizar \n1. FIFO\n2. SJF\n3. HPF\n4. Round Robin\n")
    int option;
    scanf("%d",&option);
    if(option==1) {

    }
    if(option==2) {

    }
    if(option==3){
        printf("Ingrese el valor del quantum:\n");
        int quantum;
        scanf("%d",&quantum);


    }
    else{

    }
    //start jobscheduler
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, socketConnections, NULL);
    pthread_join(thread_id, NULL);
    return 0;
}

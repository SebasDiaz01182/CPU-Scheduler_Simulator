#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    printf("Que modalidad desea utilizar: \n 1.Automatica \n 2.Manual\n");
    int option;
    scanf("%d",&option);

    int sock = 0, valread;
    struct sockaddr_in server;
    char buffer[256] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        printf("Error: socket creation failed \n");
        return -1;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {
        printf("Error: invalid address\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error: connection failed \n");
        return -1;
    }

    if(option == 1) {
        sleep(2);
        while(1) {
            char process[256];
            int priority = random()%5+1;
            
            int minBurst,maxBurst,creationRate;
            printf("Ingrese el minimo de burst:\n");
            scanf("%d", &minBurst);
            printf("Ingrese el maximo de burst:\n");
            scanf("%d", &maxBurst);
            printf("Ingrese la taza de creacion:\n");
            scanf("%d",&creationRate);


            int burst = random()%(maxBurst-minBurst+1)+minBurst;

            sprintf(process,"%d     %d",priority,burst);
            send(sock, process, strlen(process), 0);
            
            sleep(creationRate);
        }
    }
    else{

    
        printf("Ingrese el nombre del archivo: \n");
        char filename[256];
        scanf("%s",filename);
        FILE * file;
        char content[256];

        file = fopen(filename, "r");

        if (file == NULL) {
            printf("Error: there was an error opening the file %s\n",filename);
            return -1;
        }
        sleep(2);
        while (fgets(content,256,file) != NULL) {
            
            
            send(sock, content, strlen(content), 0);
            int rand = (int)random()%6+3;
            valread = read(sock, buffer, 256);
            if(valread < 0){
                close(sock);
            }
            printf("%s\n",buffer);
            sleep(1);
            //TODO: get process info from server
        }

        close(sock);
    
        
    }
    return 0;
}

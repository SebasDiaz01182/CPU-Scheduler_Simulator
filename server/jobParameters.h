#ifndef JOBPARAMETERS_H
#define JOBPARAMETERS_H
typedef struct JobParameters {
    int socket; //server socket
    struct ProcessList * processes; //list of processes

}jobParameters;

#endif
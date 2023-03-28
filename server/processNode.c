
#include "processNode.h"


void addProcess(ProcessList *list,ProcessNode *newNode){
    if (list->first == NULL){
        list->first = newNode;
    }
    else{
        struct ProcessNode * tmpNode = list->first;

        while (tmpNode->next != NULL){
            tmpNode= tmpNode->next;
        }
        tmpNode->next = newNode;
    }
}
void addProcessP(ProcessList *list, int burst, int arrive,int priority,int pid){
    ProcessNode *newNode = (ProcessNode *) malloc(sizeof(ProcessNode));
    newNode->burst = burst;
    newNode->arrive = arrive; 
    newNode->priority = priority;
    newNode->pid = pid; 
    newNode->next = NULL; 
    newNode->remainingBurst = burst; 

    if (list->first == NULL){
        list->first = newNode;
    }
    else{
        struct ProcessNode * tmpNode = list->first;

        while (tmpNode->next != NULL){
            tmpNode= tmpNode->next;
        }
        tmpNode->next = newNode;
    }
}

void printList(ProcessList *list){

    ProcessNode * tmpNode = list->first;
    while (tmpNode != NULL){
        printf("BURST: %d PRIORITY: %d \n",tmpNode->burst,tmpNode->priority);
        tmpNode = tmpNode->next;
    }
}

ProcessNode * removeProcess(ProcessList *list,ProcessNode *node){
    struct ProcessNode * tmpNode = list->first;
    struct ProcessNode * deleteNode = NULL;
    
    if(tmpNode == NULL){
        return NULL;
    }
    if(tmpNode == node){
        
        list->first = list->first->next;
        tmpNode->next = NULL;
        return tmpNode;
    }
    
    while(tmpNode->next != NULL){
        if(tmpNode->next == node){
            deleteNode = tmpNode->next;

            tmpNode->next = deleteNode->next;
            deleteNode->next = NULL;
            return deleteNode;
        }

        tmpNode = tmpNode->next;
    }
    return NULL;
}
ProcessNode * getFirstProcess(ProcessList *list){
    return list->first;
}
ProcessNode * getSJFProcess(ProcessList *list){
    struct ProcessNode * resNode = list->first;
    if(resNode == NULL){
        return NULL;
    }
    if(resNode->next == NULL){
        return resNode;
    }

    struct ProcessNode * tmpNode = list->first->next;

    while(tmpNode != NULL){
        if(resNode->burst > tmpNode->burst){
            resNode = tmpNode;
        }
        tmpNode = tmpNode->next;
    }
    return resNode;
    
}
ProcessNode * getHPFProcess(ProcessList *list){
    struct ProcessNode * resNode = list->first;
    if(resNode == NULL){
        return NULL;
    }
    if(resNode->next == NULL){
        return resNode;
    }

    struct ProcessNode * tmpNode = list->first->next;

    while(tmpNode != NULL){
        if(resNode->priority > tmpNode->priority){
            resNode = tmpNode;
        }
        tmpNode = tmpNode->next;
    }
    return resNode;
}
ProcessNode * getNextProcess(ProcessList *list,ProcessNode* node){
    if(node == NULL){
        return list->first;
    }
    if(node->next !=NULL){
        return list->first;
    }
    return node->next;

}

int getAmountItems(ProcessList *list){
    int res = 0;
    ProcessNode * tmpNode = list->first;

    while(tmpNode != NULL){
        
        res +=1;
        tmpNode = tmpNode->next;
    }
    return res;
}



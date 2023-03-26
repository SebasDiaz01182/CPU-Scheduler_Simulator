
#include "processNode.h"



void addProcess(ProcessList *list, int burst, int arrive,int priority,int pid){
    ProcessNode *newNode = {burst, arrive, priority, pid,-1};

    if (list->firstNode == NULL){
        list->firstNode = newNode;
    }
    else{
        ProcessNode * tmpNode = list->firstNode;

        while (tmpNode->next != NULL){
            tmpNode= tmpNode->next;
        }
        tmpNode->next = newNode;
    }
}
void addProcess(ProcessNode* firstNode,ProcessNode *newNode){
    if (list->firstNode == NULL){
        list->firstNode = newNode;
    }
    else{
        ProcessNode * tmpNode = list->firstNode;

        while (tmpNode->next != NULL){
            tmpNode= tmpNode->next;
        }
        tmpNode->next = newNode;
    }
}
ProcessNode * removeProcess(ProcessList *list,int pid){
    ProcessNode * tmpNode = list->first;
    ProcessNode * deleteNode = NULL;

    if(tmpNode == NULL){
        return NULL;
    }
    if(tmpNode->pid == pid){
        list->first = tmpNode->next;
        return tmpNode;
    }
    while(tmpNode->next != NULL){
        if(tmpNode->next->pid == pid){
            deleteNode = tmpNode->node;

            tmpNode->next = deleteNode->next;
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
    ProcessNode * resNode = list->first;
    if(resNode == NULL){
        return NULL;
    }
    if(resNode->next == NULL){
        return resNode;
    }

    ProcessNode * tmpNode = list->first->next;

    while(tmpNode != NULL){
        if(resNode->burst > tmpNode->burst){
            resNode = tmpNode;
        }
        tmpNode = tmpNode->next;
    }
    return resNode;
    
}
ProcessNode * getHPFProcess(ProcessList *list){
    ProcessNode * resNode = list->first;
    if(resNode == NULL){
        return NULL;
    }
    if(resNode->next == NULL){
        return resNode;
    }

    ProcessNode * tmpNode = list->first->next;

    while(tmpNode != NULL){
        if(resNode->priority > tmpNode->priority){
            resNode = tmpNode;
        }
        tmpNode = tmpNode->next;
    }
    return resNode;
}
ProcessNode * getNextProcess(ProcessList *list,ProcessNode* node){
    if(node->next !=NULL){
        return list->first;
    }
    return node->next;

}

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
    struct ProcessNode newNodeNP = {burst, arrive, priority, pid,NULL,-1};
    struct ProcessNode *newNode = &newNodeNP;

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

ProcessNode * removeProcess(ProcessList *list,ProcessNode *node){
    struct ProcessNode * tmpNode = list->first;
    struct ProcessNode * deleteNode = NULL;

    if(tmpNode == NULL){
        return NULL;
    }
    if(tmpNode == node){
        list->first = NULL;
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
    if(node->next !=NULL){
        return list->first;
    }
    return node->next;

}
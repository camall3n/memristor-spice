//
//  timelist.c
//  
//
//  Created by Cam on 4/9/11.
//  Copyright 2011 Cameron Allen. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "timelist.h"

/* Add a new node, and connect it to the list at the head */
void TimeListAdd(TimeNode **headptr, double time, double val){
    TimeNode* newNode = TimeNodeNew(time,val);
    TimeNode* priorNode;
    if (*headptr==NULL)
        priorNode=NULL;
    else if (time > (*headptr)->time)
        priorNode = *headptr;
    else
        priorNode = TimeListTruncAtTime(headptr,time);
    newNode->prev = priorNode;
    *headptr = newNode;
}

/* Get the node no later than the given time */
TimeNode* TimeListTruncAtTime(TimeNode **headptr, double time){
    if (headptr==NULL)
        return NULL;
    TimeNode* here = *headptr;
    while(here!=NULL){
        if (here->time <= time)
            break;
        here = here->prev;
    }
    if (here!=NULL){
        TimeNode* newList = TimeNodeNew(here->time,here->val);
        TimeListDelete(*headptr);
        *headptr = newList;
    } else {
        TimeListDelete(*headptr);
        *headptr = NULL;
    }
    return *headptr;
}

/* Delete an entire TimeList */
void TimeListDelete(TimeNode *head){
    TimeNode* temp;
    while(head!=NULL){
        temp = head;
        head = head->prev;
        TimeNodeDelete(temp);
    }
}

/* Printing function for debugging */
void TimeListPrint(TimeNode *head){
    TimeNode *temp = head;
    printf("Time\t\tResistance\n");
    while(temp!=NULL){
        printf("% f\t% f\n",temp->time, temp->val);
        temp = temp->prev;
    }
}


/* Create a new time/value node, with prev=NULL */
TimeNode* TimeNodeNew(double time, double val){
    TimeNode* node = malloc(sizeof(TimeNode));
    node->time = time;
    node->val  = val;
    node->prev = NULL;
    return node;
}

/* Delete a time/value node */
void TimeNodeDelete(TimeNode* ptr){
    if(ptr!=NULL)
        free(ptr);
}
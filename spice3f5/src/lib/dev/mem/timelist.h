//
//  timelist.h
//  
//
//  Created by Cam on 4/9/11.
//  Copyright 2011 Cameron Allen. All rights reserved.
//

#ifndef TIMELIST_INC
#define TIMELIST_INC

/* Struct for holding res/time pairs */
typedef struct sTimeNode {
    double time;
    double val;
    struct sTimeNode *prev;
} TimeNode;


/* --- List Functions --- */
/* Add a new node, and connect it to the list at the head */
void TimeListAdd(TimeNode **head, double time, double val);

/* Get the node no later than the given time */
TimeNode* TimeListTruncAtTime(TimeNode **head, double time);

/* Delete an entire resistance list */
void TimeListDelete(TimeNode *head);

/* Printing function for debugging */
void TimeListPrint(TimeNode *head);

/* --- Node Functions --- */
/* Create a new time/value node, with prev=NULL */
TimeNode* TimeNodeNew(double time, double val);

/* Delete a time/value node */
void TimeNodeDelete(TimeNode *ptr);


#endif
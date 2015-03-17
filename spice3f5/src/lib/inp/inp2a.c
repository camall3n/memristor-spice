/**********
 Copyright 1990 Regents of the University of California.  All rights reserved.
 Author: 1988 Thomas L. Quarles
 **********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "inpdefs.h"
#include "inpmacs.h"
#include "fteext.h"
#include "suffix.h"

void
INP2A(ckt,tab,current)
GENERIC *ckt;
INPtables *tab;
card *current;

{
    /* parse a memristor card */
    /* Aname <node> <node> [<val>][<mname>][w=<val>][l=<val>] */
    
    int mytype; /* the type we determine memristors are */
    int type;   /* the type the model says it is */
    char *line; /* the part of the current line left to parse */
    char *name; /* the memristor's name */
    char *model;    /* the name of the memristor's model */
    char *nname1;   /* the first node's name */
    char *nname2;   /* the second node's name */
    GENERIC *node1; /* the first node's node pointer */
    GENERIC *node2; /* the second node's node pointer */
    double val;     /* temp to held memristance */
    int error;      /* error code temporary */
    int error1;     /* secondary error code temporary */
    INPmodel *thismodel;    /* pointer to model structure describing our model */
    GENERIC *mdfast;    /* pointer to the actual model */
    GENERIC *fast;  /* pointer to the actual instance */
    IFvalue ptemp;  /* a value structure to package memristance into */
    int waslead;    /* flag to indicate that funny unlabeled number was found */
    double leadval; /* actual value of unlabeled number */
    IFuid uid;      /* uid for default model */
    
    mytype = INPtypelook("Memristor");
    if(mytype < 0 ) {
        LITERR("Device type Memristor not supported by this binary\n")
        return;
    }
    line = current->line;
    INPgetTok(&line,&name,1);
    INPinsert(&name,tab);
    INPgetTok(&line,&nname1,1);
    INPtermInsert(ckt,&nname1,tab,&node1);
    INPgetTok(&line,&nname2,1);
    INPtermInsert(ckt,&nname2,tab,&node2);
    val = INPevaluate(&line,&error1,1);
    /* either not a number -> model, or
     * follows a number, so must be a model name
     * -> MUST be a model name (or null)
     */
    INPgetTok(&line,&model,1);
    if(*model) { /* token isn't null */
        INPinsert(&model,tab);
        thismodel = (INPmodel *)NULL;
        current->error = INPgetMod(ckt,model,&thismodel,tab);
        if(thismodel != NULL) {
            if(mytype != thismodel->INPmodType) {
                LITERR("incorrect model type")
                return;
            }
            mdfast = thismodel->INPmodfast;
            type = thismodel->INPmodType;
        } else {
            type = mytype;
            if(!tab->defAmod) {
                /* create default A model */
                IFnewUid(ckt,&uid,(IFuid)NULL,"A",UID_MODEL,(GENERIC**)NULL);
                IFC(newModel, (ckt,type,&(tab->defAmod),uid))
            }
            mdfast = tab->defAmod;
        }
        IFC(newInstance,(ckt,mdfast,&fast,name))
    } else  {
        type = mytype;
        if(!tab->defAmod) {
            /* create default A model */
            IFnewUid(ckt,&uid,(IFuid)NULL,"A",UID_MODEL,(GENERIC**)NULL);
            IFC(newModel, (ckt,type,&(tab->defAmod),uid))
        }
        IFC(newInstance,(ckt,tab->defAmod,&fast,name))
    }
    if(error1 == 0) { /* got a memristance above */
        ptemp.rValue = val;
        GCA(INPpName,("memristance",&ptemp,ckt,type,fast))
    }
    
    IFC(bindNode,(ckt,fast,1,node1))
    IFC(bindNode,(ckt,fast,2,node2))
    PARSECALL((&line,ckt,type,fast,&leadval,&waslead,tab))
    if(waslead) {
        ptemp.rValue = leadval;
        GCA(INPpName,("memristance",&ptemp,ckt,type,fast))
    }
    return;
}
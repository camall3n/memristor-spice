/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "smpdefs.h"
#include "memdefs.h"
#include "sperror.h"
#include "suffix.h"

#include "timelist.h"

/* ARGSUSED */
int
MEMsetup(matrix,inModel,ckt,state)
    register SMPmatrix *matrix;
    GENmodel *inModel;
    CKTcircuit*ckt;
    int *state;
        /* load the memristor structure with those pointers needed later 
         * for fast matrix loading 
         */
{
    register MEMmodel *model = (MEMmodel *)inModel;
    register MEMinstance *here;
    double onFrac; /* For calculating onLength from Length and resistances */

    /*  loop through all the memristor models */
    for( ; model != NULL; model = model->MEMnextModel ) {

        /* Fill in missing resistance values with defaults */
        if (model->MEMrOnGiven && !model->MEMrOffGiven)
            model->MEMresOff = 10*model->MEMresOn;
        else if (model->MEMrOffGiven && !model->MEMrOnGiven)
            model->MEMresOn = model->MEMresOff/10;
        else if (!model->MEMrOnGiven && !model->MEMrOffGiven){
            model->MEMresOn  = 100;
            model->MEMresOff = 1000;
        }
        
        /* Check that model resistance values make sense */
        if (model->MEMresOn  >= model->MEMresOff 	||
            model->MEMresOn  <= 0  			    	||
            model->MEMresOff <= 0)
        {
            fprintf(stderr,"Invalid params: memristor model resistance.");
            return(E_BADPARM);
        }
        
        /* Other model parameters */
        if (!model->MEMwinExpGiven || model->MEMwindowExponent < 0)
            model->MEMwindowExponent=0;/* linear dopant drift */
        if (!model->MEMvacMobGiven)
            model->MEMvacMobility=1E-12;/* m^2/(V*s) */
        if (!model->MEMlengthGiven){
            model->MEMlength=50E-9;/* meters */
        }
        
        
        /* loop through all the instances of the model */
        for (here = model->MEMinstances; here != NULL ;
                here=here->MEMnextInstance) {
            
/* macro to make elements with built in test for out of memory */
#define TSTALLOC(ptr,first,second) \
if((here->ptr = SMPmakeElt(matrix,here->first,here->second))==(double *)NULL){\
return(E_NOMEM);\
}
            
            TSTALLOC(MEMposPosptr, MEMposNode, MEMposNode);
            TSTALLOC(MEMnegNegptr, MEMnegNode, MEMnegNode);
            TSTALLOC(MEMposNegptr, MEMposNode, MEMnegNode);
            TSTALLOC(MEMnegPosptr, MEMnegNode, MEMposNode);
       
            /* Fill in missing resistance value with default */
            if (!here->MEMresGiven)
                here->MEMresist = (model->MEMresOn + model->MEMresOff)/2;
            
            /* Check that resistance value makes sense */
            if (here->MEMresist <= model->MEMresOn   ||
                here->MEMresist >= model->MEMresOff  ||
                here->MEMresist <= 0)
            {
                fprintf(stderr,"Invalid params: memristor instance resistance.");
                return(E_BADPARM);
            }
            
            /* Now worry about length */
            onFrac = (model->MEMresOff - here->MEMresist) /
                     (model->MEMresOff - model->MEMresOn);
            here->MEMonLength = onFrac * model->MEMlength;
            TimeListAdd(&(here->MEMstateList),0.0,here->MEMonLength);
        }
    }
    return(OK);
}

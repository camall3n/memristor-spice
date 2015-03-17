/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "cktdefs.h"
#include "memdefs.h"
#include "sperror.h"
#include "suffix.h"

#include "timelist.h"

/* Window function to calculate drift slowdown near state variable boundaries */
static double windowFunction(double x, int e){
    if (x >= 0 && x <= 1)
        if (e > 0)
            return 1 - pow(2*x-1,2*e);
        else
            return 1;
    else
        return 0;
}

/*ARGSUSED*/
int
MEMload(inModel,ckt)
    GENmodel *inModel;
    CKTcircuit *ckt;
        /* actually load the current resistance value into the 
         * sparse matrix previously provided 
         */
{
    register MEMmodel *model = (MEMmodel *)inModel;
    register MEMinstance *here;
    double vmem; /* voltage across memristor */
    double time = ckt->CKTtime; /* current time */
    double dt;   /* timestep */
    double oldOnLength;
    double dOnLength; /* change in length of ON region */
    double onFrac; /* fraction of memristor that is ON */
    double slowdown; /* output of window function for state variable */
    double uV, ron, roff, len;
    int exp;
    
    
    /*  loop through all the memristor models */
    for( ; model != NULL; model = model->MEMnextModel ) {

        len  = model->MEMlength;
        ron  = model->MEMresOn;
        roff = model->MEMresOff;
        uV   = model->MEMvacMobility;
        exp  = model->MEMwindowExponent;
        
        /* loop through all the instances of the model */
        for (here = model->MEMinstances; here != NULL ;
                here=here->MEMnextInstance)
        {
            /* Get old state variable (onLength) from state list */
            if (here->MEMstateList==NULL){
                fprintf(stderr,"No state list found!!\n");
                return(E_BADPARM);
            }
            TimeListTruncAtTime(&(here->MEMstateList),time);
            oldOnLength = (here->MEMstateList->val);
            
            /* Calculate time step and voltage difference */
            dt = time - here->MEMstateList->time;
            vmem = *(ckt->CKTrhsOld+here->MEMposNode) - 
              *(ckt->CKTrhsOld+here->MEMnegNode);
            
            /* Calculate new state variable */
            dOnLength = dt*uV*vmem/len;
            slowdown = windowFunction(oldOnLength/len, exp);
            here->MEMonLength = oldOnLength + dOnLength;
            TimeListAdd(&(here->MEMstateList),time,here->MEMonLength);
            
            /* Update resistance */
            onFrac = here->MEMonLength / len;
            here->MEMresist = ron*onFrac+roff*(1-onFrac);

            /* Confine resistance to within [Ron,Roff] */
            if (here->MEMresist > roff)
                here->MEMresist = roff;
            else if (here->MEMresist < ron)
                here->MEMresist = ron;
            
            /* Update the matrix */
            here->MEMconduct = 1.0/here->MEMresist;
            *(here->MEMposPosptr) += here->MEMconduct;
            *(here->MEMnegNegptr) += here->MEMconduct;
            *(here->MEMposNegptr) -= here->MEMconduct;
            *(here->MEMnegPosptr) -= here->MEMconduct;
        }
    }
    return(OK);
}







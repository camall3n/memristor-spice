/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "const.h"
#include "util.h"
#include "ifsim.h"
#include "memdefs.h"
#include "sperror.h"
#include "suffix.h"


/* ARGSUSED */
int
MEMparam(param,value,inst,select)
    int param;
    IFvalue *value;
    GENinstance *inst;
    IFvalue *select;
{
    MEMinstance *here = (MEMinstance *)inst;
    switch(param) {
        case MEM_TEMP:
            here->MEMtemp = value->rValue+CONSTCtoK;
            here->MEMtempGiven = TRUE;
            break;
        case MEM_RESIST:
            here->MEMresist = value->rValue;
            here->MEMresGiven = TRUE;
            break;
        case MEM_WIDTH:
            here->MEMwidth = value->rValue;
            here->MEMwidthGiven = TRUE;
            break;
        case MEM_RESIST_SENS:
            here->MEMsenParmNo = value->iValue;
            break;
        default:
            return(E_BADPARM);
    }
    return(OK);
}

/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "const.h"
#include "cktdefs.h"
#include "ifsim.h"
#include "memdefs.h"
#include "sperror.h"
#include "devdefs.h"
#include "suffix.h"


/* ARGSUSED */
int 
MEMmodAsk(ckt,inModel,which,value)
    CKTcircuit *ckt;
    GENmodel *inModel;
    int which;
    IFvalue *value;
{
    MEMmodel *model = (MEMmodel *)inModel;
    switch(which) {
        case MEM_MOD_TNOM:
            value->rValue = model->MEMtnom-CONSTCtoK;
            return(OK);
        case MEM_MOD_TC1:
            value->rValue = model->MEMtempCoeff1;
            return(OK);
        case MEM_MOD_TC2:
            value->rValue = model->MEMtempCoeff2;
            return(OK);
        case MEM_MOD_MSH:
            value->rValue = model->MEMsheetMem;
            return(OK);
        case MEM_MOD_DEFWIDTH:
            value->rValue = model->MEMdefWidth;
            return(OK);
        case MEM_MOD_NARROW: 
            value->rValue = model->MEMnarrow;
            return(OK);
        case MEM_LENGTH:
            value->rValue = model->MEMlength;
            return(OK);
        default:
            return(E_BADPARM);
    }
}


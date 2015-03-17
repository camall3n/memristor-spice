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


int
MEMmParam(param,value,inModel)
    int param;
    IFvalue *value;
    GENmodel *inModel;
{
    register MEMmodel *model = (MEMmodel *)inModel;
    switch(param) {
        case MEM_MOD_TNOM:
            model->MEMtnom = value->rValue+CONSTCtoK;
            model->MEMtnomGiven = TRUE;
            break;
        case MEM_MOD_TC1:
            model->MEMtempCoeff1 = value->rValue;
            model->MEMtc1Given = TRUE;
            break;
        case MEM_MOD_TC2:
            model->MEMtempCoeff2 = value->rValue;
            model->MEMtc2Given = TRUE;
            break;
        case MEM_MOD_MSH:
            model->MEMsheetMem = value->rValue;
            model->MEMsheetMemGiven = TRUE;
            break;
        case MEM_MOD_DEFWIDTH:
            model->MEMdefWidth = value->rValue;
            model->MEMdefWidthGiven = TRUE;
            break;
        case MEM_MOD_NARROW:
            model->MEMnarrow = value->rValue;
            model->MEMnarrowGiven = TRUE;
            break;
        case MEM_LENGTH:
            model->MEMlength = value->rValue;
            model->MEMlengthGiven = TRUE;
            break;
        case MEM_RON:
            model->MEMresOn = value->rValue;
            model->MEMrOnGiven = TRUE;
            break;
        case MEM_ROFF:
            model->MEMresOff = value->rValue;
            model->MEMrOffGiven = TRUE;
            break;
        case MEM_VACMOB:
            model->MEMvacMobility = value->rValue;
            model->MEMvacMobGiven = TRUE;
            break;
        case MEM_WINEXP:
            model->MEMwindowExponent = value->rValue;
            model->MEMwinExpGiven = TRUE;
            break;
        case MEM_MOD_A:
            /* just being reassured by user that this is a memristor model */
            /* no-op */
            break;
        default:
            return(E_BADPARM);
    }
    return(OK);
}

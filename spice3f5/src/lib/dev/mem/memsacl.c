/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "memdefs.h"
#include "sperror.h"
#include "suffix.h"


int
MEMsAcLoad(inModel,ckt)
    GENmodel *inModel;
    CKTcircuit *ckt;
        /* actually load the current ac sensitivity info into the 
         * array previously provided 
         */
{
    register MEMmodel *model = (MEMmodel *)inModel;
    register MEMinstance *here;
    double vmem;
    double ivmem;
    double value;
    double ivalue;

    /*  loop through all the memristor models */
    for( ; model != NULL; model = model->MEMnextModel ) {

        /* loop through all the instances of the model */
        for (here = model->MEMinstances; here != NULL ;
                here=here->MEMnextInstance) {

            if(here->MEMsenParmNo){
                vmem = *(ckt->CKTrhsOld+here->MEMposNode) -
                  *(ckt->CKTrhsOld+here->MEMnegNode);
                ivmem = *(ckt->CKTirhsOld+here->MEMposNode) -
                  *(ckt->CKTirhsOld+here->MEMnegNode);
                value = vmem * here->MEMconduct * here->MEMconduct;
                ivalue = ivmem * here->MEMconduct * here->MEMconduct;

                /* load the RHS matrix */
                *(ckt->CKTsenInfo->SEN_RHS[here->MEMposNode] + 
                  here->MEMsenParmNo) += value;
                *(ckt->CKTsenInfo->SEN_iRHS[here->MEMposNode] +
                  here->MEMsenParmNo) += ivalue;
                *(ckt->CKTsenInfo->SEN_RHS[here->MEMnegNode] + 
                  here->MEMsenParmNo) -= value;
                *(ckt->CKTsenInfo->SEN_iRHS[here->MEMnegNode] + 
                  here->MEMsenParmNo) -= ivalue;
            }
        }
    }
    return(OK);
}



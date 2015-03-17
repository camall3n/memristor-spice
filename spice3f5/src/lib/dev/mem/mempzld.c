/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "complex.h"
#include "sperror.h"
#include "memdefs.h"
#include "suffix.h"


/*ARGSUSED*/
int
MEMpzLoad(inModel,ckt,s)
    GENmodel *inModel;
    CKTcircuit *ckt;
    SPcomplex *s;
        /* actually load the current resistance value into the 
         * sparse matrix previously provided 
         */
{
    register MEMmodel *model = (MEMmodel *)inModel;
    register MEMinstance *here;

    /*  loop through all the memristor models */
    for( ; model != NULL; model = model->MEMnextModel ) {

        /* loop through all the instances of the model */
        for (here = model->MEMinstances; here != NULL ;
                here=here->MEMnextInstance) {
            
            *(here->MEMposPosptr) += here->MEMconduct;
            *(here->MEMnegNegptr) += here->MEMconduct;
            *(here->MEMposNegptr) -= here->MEMconduct;
            *(here->MEMnegPosptr) -= here->MEMconduct;
        }
    }
    return(OK);
}

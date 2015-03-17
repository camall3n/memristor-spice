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
#include "cktdefs.h"


int
MEMsSetup(info,inModel)
    register SENstruct *info;
    GENmodel *inModel;
        /* loop through all the devices and 
         * assign parameter #s to design parameters 
         */
{
    register MEMmodel *model = (MEMmodel *)inModel;
    register MEMinstance *here;

    /*  loop through all the memristor models */
    for( ; model != NULL; model = model->MEMnextModel ) {

        /* loop through all the instances of the model */
        for (here = model->MEMinstances; here != NULL ;
            here=here->MEMnextInstance) {

            if(here->MEMsenParmNo){
                here->MEMsenParmNo = ++(info->SENparms);
            }
        }
    }
    return(OK);
}

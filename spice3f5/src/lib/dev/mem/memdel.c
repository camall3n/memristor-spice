/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "memdefs.h"
#include "sperror.h"
#include "suffix.h"


int
MEMdelete(inModel,name,inst)
    GENmodel *inModel;
    IFuid name;
    GENinstance **inst;
{
    MEMmodel *model = (MEMmodel *)inModel;
    MEMinstance **fast = (MEMinstance **)inst;
    MEMinstance **prev = NULL;
    MEMinstance *here;

    for( ; model ; model = model->MEMnextModel) {
        prev = &(model->MEMinstances);
        for(here = *prev; here ; here = *prev) {
            if(here->MEMname == name || (fast && here==*fast) ) {
                *prev= here->MEMnextInstance;
                TimeListDelete(here->MEMstateList);
                FREE(here);
                return(OK);
            }
            prev = &(here->MEMnextInstance);
        }
    }
    return(E_NODEV);
}

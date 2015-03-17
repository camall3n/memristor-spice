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
MEMmDelete(inModel,modname,kill)
    GENmodel **inModel;
    IFuid modname;
    GENmodel *kill;
{
    MEMmodel **model = (MEMmodel **)inModel;
    MEMmodel *modfast = (MEMmodel *)kill;
    MEMinstance *here;
    MEMinstance *prev = NULL;
    MEMmodel **oldmod;
    oldmod = model;
    for( ; *model ; model = &((*model)->MEMnextModel)) {
        if( (*model)->MEMmodName == modname || 
                (modfast && *model == modfast) ) goto delgot;
        oldmod = model;
    }
    return(E_NOMOD);

delgot:
    *oldmod = (*model)->MEMnextModel; /* cut deleted device out of list */
    for(here = (*model)->MEMinstances ; here ; here = here->MEMnextInstance) {
        if(prev) FREE(prev);
        prev = here;
    }
    if(prev) FREE(prev);
    FREE(*model);
    return(OK);

}

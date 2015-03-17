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
#include "suffix.h"


void
MEMdestroy(inModel)
    GENmodel **inModel;
{
    MEMmodel **model = (MEMmodel **)inModel;
    MEMinstance *here;
    MEMinstance *prev = NULL;
    MEMmodel *mod = *model;
    MEMmodel *oldmod = NULL;

    for( ; mod ; mod = mod->MEMnextModel) {
        if(oldmod) FREE(oldmod);
        oldmod = mod;
        prev = (MEMinstance *)NULL;
        for(here = mod->MEMinstances ; here ; here = here->MEMnextInstance) {
            if(prev) FREE(prev);
            prev = here;
        }
        if(prev) FREE(prev);
    }
    if(oldmod) FREE(oldmod);
    *model = NULL;
}

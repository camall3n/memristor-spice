/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

/* Pretty print the sensitivity info for all 
 * the memristors in the circuit.
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "memdefs.h"
#include "sperror.h"
#include "suffix.h"


void
MEMsPrint(inModel,ckt)
    GENmodel *inModel;
    register CKTcircuit *ckt;
{
    register MEMmodel *model = (MEMmodel *)inModel;
    register MEMinstance *here;
    printf("MEMRISTORS-----------------\n");

    /*  loop through all the memristor models */
    for( ; model != NULL; model = model->MEMnextModel ) {

        printf("Model name:%s\n",model->MEMmodName);

        /* loop through all the instances of the model */
        for (here = model->MEMinstances; here != NULL ;
                here=here->MEMnextInstance) {

            printf("    Instance name:%s\n",here->MEMname);
            printf("      Positive, negative nodes: %s, %s\n",
            CKTnodName(ckt,here->MEMposNode),CKTnodName(ckt,here->MEMnegNode));
            printf("      Memristance: %f ",here->MEMresist);
            printf(here->MEMresGiven ? "(specified)\n" : "(default)\n");
            printf("    MEMsenParmNo:%d\n",here->MEMsenParmNo);

        }
    }
}

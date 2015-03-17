/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "cktdefs.h"
#include "memdefs.h"
#include "sperror.h"
#include "suffix.h"


int
MEMtemp(inModel,ckt)
    GENmodel *inModel;
    register CKTcircuit *ckt;
        /* perform the temperature update to the memristors
         * calculate the conductance as a function of the
         * given nominal and current temperatures - the
         * memristance given in the struct is the nominal
         * temperature memristance
         */
{
    register MEMmodel *model =  (MEMmodel *)inModel;
    register MEMinstance *here;
    double factor;
    double difference;


    /*  loop through all the memristor models */
    for( ; model != NULL; model = model->MEMnextModel ) {

#ifdef notdef
        /* Default Value Processing for Memristor Models */
        if(!model->MEMtnomGiven) model->MEMtnom = ckt->CKTnomTemp;
        if(!model->MEMsheetMemGiven) model->MEMsheetMem = 0;
        if(!model->MEMdefWidthGiven) model->MEMdefWidth = 10.e-6; /*M*/
        if(!model->MEMtc1Given) model->MEMtempCoeff1 = 0;
        if(!model->MEMtc2Given) model->MEMtempCoeff2 = 0;
        if(!model->MEMnarrowGiven) model->MEMnarrow = 0;
#endif /* notdef */

        /* loop through all the instances of the model */
        for (here = model->MEMinstances; here != NULL ;
                here=here->MEMnextInstance) {
            
#ifdef notdef
            /* Default Value Processing for Memristor Instance */
            if(!here->MEMtempGiven) here->MEMtemp = ckt->CKTtemp;
            if(!here->MEMwidthGiven) here->MEMwidth = model->MEMdefWidth;
            if(!here->MEMlengthGiven)  here->MEMlength = 0 ;
            if(!here->MEMresGiven)  {
                if(model->MEMsheetMemGiven && (model->MEMsheetMem != 0) &&
                        (here->MEMlength != 0)) {
                    here->MEMresist = model->MEMsheetMem * (here->MEMlength -
                        model->MEMnarrow) / (here->MEMwidth - model->MEMnarrow);
                } else {
                    (*(SPfrontEnd->IFerror))(ERR_WARNING,
                            "%s: memristance=0, set to 1000",&(here->MEMname));
                    here->MEMresist=1000;
                }
            }

            difference = here->MEMtemp - model->MEMtnom;
            factor = 1.0 + (model->MEMtempCoeff1)*difference + 
                    (model->MEMtempCoeff2)*difference*difference;
#endif /* notdef */
            // OLD VERSION (from standard resistor)
            // here->MEMconduct = 1.0/(here->MEMresist * factor);
            here->MEMconduct = 1.0/(here->MEMresist);
        }
    }
    return(OK);
}

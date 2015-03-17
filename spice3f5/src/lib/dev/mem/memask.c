/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "const.h"
#include "memdefs.h"
#include "ifsim.h"
#include "cktdefs.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"

/*ARGSUSED*/
int
MEMask(ckt,inst,which,value,select)
    CKTcircuit *ckt;
    GENinstance *inst;
    int which;
    IFvalue *value;
    IFvalue *select;
{
    MEMinstance *fast = (MEMinstance *)inst;
    double vr;
    double vi;
    double sr;
    double si;
    double vm;
    static char *msg = "Current and power not available for ac analysis";
    switch(which) {
        case MEM_TEMP:
            value->rValue = fast->MEMtemp-CONSTCtoK;
            return(OK);
        case MEM_CONDUCT:
            value->rValue = fast->MEMconduct;
            return(OK);
        case MEM_RESIST:
            value->rValue = fast->MEMresist;
            return(OK);
        case MEM_WIDTH :
            value->rValue = fast->MEMwidth;
            return(OK);
        case MEM_QUEST_SENS_DC:
            if(ckt->CKTsenInfo){
                value->rValue = *(ckt->CKTsenInfo->SEN_Sap[select->iValue + 1]+
                        fast->MEMsenParmNo);
            }
            return(OK);
        case MEM_QUEST_SENS_REAL:
            if(ckt->CKTsenInfo){
                value->rValue = *(ckt->CKTsenInfo->SEN_RHS[select->iValue + 1]+
                        fast->MEMsenParmNo);
            }
            return(OK);
        case MEM_QUEST_SENS_IMAG:
            if(ckt->CKTsenInfo){
                value->rValue = *(ckt->CKTsenInfo->SEN_iRHS[select->iValue + 1]+
                        fast->MEMsenParmNo);
            }
            return(OK);
        case MEM_QUEST_SENS_MAG:
            if(ckt->CKTsenInfo){
                vr = *(ckt->CKTrhsOld + select->iValue + 1); 
                vi = *(ckt->CKTirhsOld + select->iValue + 1); 
                vm = sqrt(vr*vr + vi*vi);
                if(vm == 0){
                    value->rValue = 0;
                    return(OK);
                }
                sr = *(ckt->CKTsenInfo->SEN_RHS[select->iValue + 1]+
                        fast->MEMsenParmNo);
                si = *(ckt->CKTsenInfo->SEN_iRHS[select->iValue + 1]+
                        fast->MEMsenParmNo);
                value->rValue = (vr * sr + vi * si)/vm;
            }
            return(OK);
        case MEM_QUEST_SENS_PH:
            if(ckt->CKTsenInfo){
                vr = *(ckt->CKTrhsOld + select->iValue + 1); 
                vi = *(ckt->CKTirhsOld + select->iValue + 1); 
                vm = vr*vr + vi*vi;
                if(vm == 0){
                    value->rValue = 0;
                    return(OK);
                }
                sr = *(ckt->CKTsenInfo->SEN_RHS[select->iValue + 1]+
                        fast->MEMsenParmNo);
                si = *(ckt->CKTsenInfo->SEN_iRHS[select->iValue + 1]+
                        fast->MEMsenParmNo);
                value->rValue = (vr * si - vi * sr)/vm;
            }
            return(OK);
        case MEM_QUEST_SENS_CPLX:
            if(ckt->CKTsenInfo){
                value->cValue.real= 
                        *(ckt->CKTsenInfo->SEN_RHS[select->iValue + 1]+
                        fast->MEMsenParmNo);
                value->cValue.imag= 
                        *(ckt->CKTsenInfo->SEN_iRHS[select->iValue + 1]+
                        fast->MEMsenParmNo);
            }
            return(OK);
        case MEM_CURRENT:
            if (ckt->CKTcurrentAnalysis & DOING_AC) {
                errMsg = MALLOC(strlen(msg)+1);
                errRtn = "MEMask";
                strcpy(errMsg,msg);
                return(E_ASKCURRENT);
            } else {
                value->rValue = (*(ckt->CKTrhsOld + fast->MEMposNode) -  
                        *(ckt->CKTrhsOld + fast->MEMnegNode))
                        *fast->MEMconduct;    
            }
            return(OK);
        case MEM_POWER:
            if (ckt->CKTcurrentAnalysis & DOING_AC) {
                errMsg = MALLOC(strlen(msg)+1);
                errRtn = "MEMask";
                strcpy(errMsg,msg);
                return(E_ASKPOWER);
            } else {
                value->rValue = (*(ckt->CKTrhsOld + fast->MEMposNode) -  
                        *(ckt->CKTrhsOld + fast->MEMnegNode)) * 
                        fast->MEMconduct *  
                        (*(ckt->CKTrhsOld + fast->MEMposNode) - 
                        *(ckt->CKTrhsOld + fast->MEMnegNode));
            }
            return(OK);
        default:
            return(E_BADPARM);
    }
    /* NOTREACHED */
}

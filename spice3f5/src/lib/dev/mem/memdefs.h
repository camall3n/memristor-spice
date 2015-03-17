/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#ifndef MEM
#define MEM

#include "ifsim.h"
#include "cktdefs.h"
#include "gendefs.h"
#include "complex.h"
#include "noisedef.h"

#include "timelist.h"

        /* definitions used to describe memristors */


/* information used to describe a single instance */

typedef struct sMEMinstance {
    struct sMEMmodel *MEMmodPtr;    /* backpointer to model */
    struct sMEMinstance *MEMnextInstance;   /* pointer to next instance of 
                                             * current model*/

    IFuid MEMname;  /* pointer to character string naming this instance */
    int MEMstate;   /* pointer to start of memristor state vector */
    int MEMposNode; /* number of positive node of memristor */
    int MEMnegNode; /* number of negative node of memristor */

    double MEMtemp;     /* temperature at which this memristor operates */
    double MEMconduct;  /* instantaneous conductance */
    double MEMresist;   /* instantaneous resistance */
    double MEMwidth;    /* width of the memristor */
    double MEMonLength; /* current length of ON section. (less than MEMlength) */
    TimeNode *MEMstateList; /* Pointer to list of time/value pairs */

    double *MEMposPosptr;    /* pointer to sparse matrix diagonal at 
                              * (positive,positive) */
    double *MEMnegNegptr;    /* pointer to sparse matrix diagonal at 
                              * (negative,negative) */
    double *MEMposNegptr;    /* pointer to sparse matrix offdiagonal at 
                              * (positive,negative) */
    double *MEMnegPosptr;    /* pointer to sparse matrix offdiagonal at 
                              * (negative,positive) */
    unsigned MEMresGiven : 1;   /* flag to indicate memristance was specified */
    unsigned MEMwidthGiven  : 1;    /* flag to indicate width given */
    unsigned MEMtempGiven   : 1;    /* indicates temperature specified */
    int    MEMsenParmNo;         /* parameter # for sensitivity use;
                set equal to  0 if not a design parameter*/
#ifndef NONOISE
    double MEMnVar[NSTATVARS];
#else /* NONOISE */
	double *MEMnVar;
#endif /* NONOISE */

} MEMinstance ;


/* per model data */

typedef struct sMEMmodel {       /* model structure for a memristor */
    int MEMmodType; /* type index of this device type */
    struct sMEMmodel *MEMnextModel; /* pointer to next possible model in 
                                     * linked list */
    MEMinstance * MEMinstances; /* pointer to list of instances that have this
                                 * model */
    IFuid MEMmodName;       /* pointer to character string naming this model */

    double MEMtnom;         /* temperature at which memristance measured */
    double MEMtempCoeff1;   /* first temperature coefficient of memristors */
    double MEMtempCoeff2;   /* second temperature coefficient of memristors */
    double MEMsheetMem;     /* sheet memristance of devices in ohms/square */
    double MEMdefWidth;     /* default width of a memristor */
    double MEMnarrow;       /* amount by which device is narrower than drawn */
    double MEMlength;   /* length of the memristor */
    double MEMresOn;    /* Resistance of ON section */
    double MEMresOff;   /* Resistance of OFF section */
    double MEMvacMobility; /* Mobility of oxygen vacancies */
    int MEMwindowExponent; /* Exponent to use for window function */
    
    unsigned MEMtnomGiven: 1;   /* flag to indicate nominal temp. was given */
    unsigned MEMtc1Given : 1;   /* flag to indicate tc1 was specified */
    unsigned MEMtc2Given : 1;   /* flag to indicate tc2 was specified */
    unsigned MEMsheetMemGiven  :1; /* flag to indicate sheet memristance given*/
    unsigned MEMdefWidthGiven  :1; /* flag to indicate default width given */
    unsigned MEMnarrowGiven    :1; /* flag to indicate narrow effect given */
    unsigned MEMlengthGiven : 1;    /* flag to indicate length given */
    unsigned MEMrOnGiven    : 1;    /* flag to indicate resOn given */
    unsigned MEMrOffGiven   : 1;    /* flag to indicate resOff given */
    unsigned MEMvacMobGiven : 1;    /* flag to indicate vacMobility given */
    unsigned MEMwinExpGiven : 1;    /* flag to indicate windowExponent given */

} MEMmodel;

/* device parameters */
#define MEM_RESIST 1
#define MEM_WIDTH 2
#define MEM_CONDUCT 3
#define MEM_RESIST_SENS 4
#define MEM_CURRENT 5
#define MEM_POWER 6
#define MEM_TEMP 7

/* model parameters */
#define MEM_MOD_TC1 101
#define MEM_MOD_TC2 102
#define MEM_MOD_MSH 103
#define MEM_MOD_DEFWIDTH 104
#define MEM_MOD_NARROW 105
#define MEM_MOD_A 106
#define MEM_MOD_TNOM 107
#define MEM_LENGTH 108
#define MEM_RON 109
#define MEM_ROFF 110
#define MEM_VACMOB 111
#define MEM_WINEXP 112

/* device questions */
#define MEM_QUEST_SENS_REAL      201
#define MEM_QUEST_SENS_IMAG      202
#define MEM_QUEST_SENS_MAG       203
#define MEM_QUEST_SENS_PH        204
#define MEM_QUEST_SENS_CPLX      205
#define MEM_QUEST_SENS_DC        206

/* model questions */


#include "memext.h"

#endif /*MEM*/

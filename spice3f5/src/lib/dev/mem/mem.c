/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "memdefs.h"
#include "devdefs.h"
#include "ifsim.h"
#include "suffix.h"

IFparm MEMpTable[] = { /* parameters */ 
 IOPP( "r0",  MEM_RESIST, IF_REAL,"Instantaneous Resistance"),
 IOPZU( "temp",        MEM_TEMP,    IF_REAL,"Instance operating temperature"),
 IOPZU( "w",           MEM_WIDTH,   IF_REAL,"Width"),
 IP(   "sens_resist", MEM_RESIST_SENS, IF_FLAG,   
        "flag to request sensitivity WRT resistance"),
 OP( "i",              MEM_CURRENT, IF_REAL,"Current"),
 OP( "p",              MEM_POWER,   IF_REAL,"Power"),
 OPU( "sens_dc",  MEM_QUEST_SENS_DC,  IF_REAL,    "dc sensitivity "),
 OPU( "sens_real",MEM_QUEST_SENS_REAL,IF_REAL,    
        "dc sensitivity and real part of ac sensitivity"),
 OPU( "sens_imag",MEM_QUEST_SENS_IMAG,IF_REAL,    
        "dc sensitivity and imag part of ac sensitivity"),
 OPU( "sens_mag", MEM_QUEST_SENS_MAG, IF_REAL, "ac sensitivity of magnitude"),
 OPU( "sens_ph",  MEM_QUEST_SENS_PH,  IF_REAL,    "ac sensitivity of phase"),
 OPU( "sens_cplx",MEM_QUEST_SENS_CPLX,IF_COMPLEX,    "ac sensitivity")
} ;

IFparm MEMmPTable[] = { /* model parameters */
 IOP( "ron",  MEM_RON, IF_REAL, "Minimum (ON) resistance value"),
 IOP( "roff", MEM_ROFF, IF_REAL, "Maximum (OFF) resistance value"),
 IOP( "uvac", MEM_VACMOB, IF_REAL, "Mobility of oxygen vacancies"),
 IOP( "wexp", MEM_WINEXP, IF_REAL, "Exponent for window function"),
 IOP( "l",    MEM_LENGTH,  IF_REAL,"Length"),
 IOPQ( "rsh",    MEM_MOD_MSH,      IF_REAL,"Sheet memristance"),
 IOPZ( "narrow", MEM_MOD_NARROW,   IF_REAL,"Narrowing of memristor"),
 IOPQ( "tc1",    MEM_MOD_TC1,      IF_REAL,"First order temp. coefficient"),
 IOPQO( "tc2",    MEM_MOD_TC2,      IF_REAL,"Second order temp. coefficient"),
 IOPX( "defw",   MEM_MOD_DEFWIDTH, IF_REAL,"Default device width"),
 IOPXU("tnom",  MEM_MOD_TNOM,     IF_REAL,"Parameter measurement temperature"),
 IP( "a",      MEM_MOD_A,        IF_FLAG,"Device is a memristor model")
};

char *MEMnames[] = {
    "A+",
    "A-"
};

int	MEMnSize = NUMELEMS(MEMnames);
int	MEMpTSize = NUMELEMS(MEMpTable);
int	MEMmPTSize = NUMELEMS(MEMmPTable);
int	MEMiSize = sizeof(MEMinstance);
int	MEMmSize = sizeof(MEMmodel);

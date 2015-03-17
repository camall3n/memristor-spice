/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/
#ifdef DEV_mem

#ifndef DEV_MEM
#define DEV_MEM

#include "memext.h"
extern IFparm MEMpTable[ ];
extern IFparm MEMmPTable[ ];
extern char *MEMnames[ ];
extern int MEMpTSize;
extern int MEMmPTSize;
extern int MEMnSize;
extern int MEMiSize;
extern int MEMmSize;

SPICEdev MEMinfo = {
    {
        "Memristor",
        "Simple memristor",

        &MEMnSize,
        &MEMnSize,
        MEMnames,

        &MEMpTSize,
        MEMpTable,

        &MEMmPTSize,
        MEMmPTable,
	0
    },

    MEMparam,
    MEMmParam,
    MEMload,
    MEMsetup,
    NULL,
    MEMsetup,
    MEMtemp,
    NULL,
    NULL,
    MEMload,  /* ac load and normal load are identical */
    NULL,
    MEMdestroy,
#ifdef DELETES
    MEMmDelete,
    MEMdelete,
#else /* DELETES */
    NULL,
    NULL,
#endif /* DELETES */
    NULL,
    MEMask,
    MEMmodAsk,
#ifdef AN_pz
    MEMpzLoad,
#else /* AN_pz */
    NULL,
#endif /* AN_pz */
    NULL,
#ifdef AN_sense2
    MEMsSetup,
    MEMsLoad,
    NULL,
    MEMsAcLoad,
    MEMsPrint,
    NULL,
#else /* AN_sense2 */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#endif /* AN_sense2 */
    NULL, /* Disto */
#ifdef AN_noise
    MEMnoise,
#else	/* AN_noise */
    NULL,
#endif	/* AN_noise */

    &MEMiSize,
    &MEMmSize

};

#endif
#endif

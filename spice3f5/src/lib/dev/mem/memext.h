/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#ifdef __STDC__
extern int MEMask(CKTcircuit*,GENinstance*,int,IFvalue*,IFvalue*);
extern int MEMdelete(GENmodel*,IFuid,GENinstance**);
extern void MEMdestroy(GENmodel**);
extern int MEMload(GENmodel*,CKTcircuit*);
extern int MEMmodAsk(CKTcircuit*,GENmodel*,int,IFvalue*);
extern int MEMmDelete(GENmodel**,IFuid,GENmodel*);
extern int MEMmParam(int,IFvalue*,GENmodel*);
extern int MEMparam(int,IFvalue*,GENinstance*,IFvalue*);
extern int MEMpzLoad(GENmodel*,CKTcircuit*,SPcomplex*);
extern int MEMsAcLoad(GENmodel*,CKTcircuit*);
extern int MEMsLoad(GENmodel*,CKTcircuit*);
extern int MEMsSetup(SENstruct*,GENmodel*);
extern void MEMsPrint(GENmodel*,CKTcircuit*);
extern int MEMsetup(SMPmatrix*,GENmodel*,CKTcircuit*,int*);
extern int MEMtemp(GENmodel*,CKTcircuit*);
extern int MEMnoise(int,int,GENmodel*,CKTcircuit*,Ndata*,double*);
#else /* stdc */
extern int MEMask();
extern int MEMdelete();
extern void MEMdestroy();
extern int MEMload();
extern int MEMmodAsk();
extern int MEMmDelete();
extern int MEMmParam();
extern int MEMparam();
extern int MEMpzLoad();
extern int MEMsAcLoad();
extern int MEMsLoad();
extern int MEMsSetup();
extern void MEMsPrint();
extern int MEMsetup();
extern int MEMtemp();
extern int MEMnoise();
#endif /* stdc */


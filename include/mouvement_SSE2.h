#ifndef __MOUVEMENT_SSE2_H__
#define __MOUVEMENT_SSE2_H__


void routine_FrameDifference_SSE2(vuint8 **I1, vuint8 **I0, vuint8 **Et, long rawl, long rawh, long coll, long colh, vuint8 threshold);	
void routine_SigmaDelta_step0_SSE2(vuint8** It1, vuint8 **M, vuint8 **V, long rawl, long rawh, long coll, long colh);
void routine_SigmaDelta_step1_SSE2(vuint8** It1,  vuint8** Vt0, vuint8** Vt1, vuint8** Mt0, vuint8** Mt1, vuint8 **Et, vuint8 **V, long rawl, long rawh, long coll, long colh);
void routine_FrameDifference_SSE2_thread(vuint8 **I1p, vuint8 **I0p, vuint8 **Etp, long rawl, long rawh, long coll, long colh, vuint8 threshold);


#endif

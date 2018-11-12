#ifndef __MOUVEMENT_H__
#define __MOUVEMENT_H__


void routine_FrameDifference(uint8 **I1, uint8 **I0, uint8 **E0, long rawl, long rawh, long coll, long colh, int threshold)
int maxmin(uint8 ** Vt);
void routine_SigmaDelta_step0_initialisation(uint8** It1, uint8 **M, uint8 **V, int rawl, int rawh, int coll, int colh );
void routine_SigmaDelta_step1(uint8** It, uint8** Mt1, uint8** Mt, uint8** Vt, uint8** Vt1, uint8** Et);


#endif

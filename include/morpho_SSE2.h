#ifndef __MORPHO_SSE2_H__
#define __MORPHO_SSE2_H__

void dilatation3x3_SSE2(vuint8 **X, vuint8 **B, long nrl, long ncl, long nrh, long nch);
void erosion3x3_SSE2(vuint8 **X, vuint8 **B, long nrl,long ncl,long nrh,long nch);
void fermeture3x3_SSE2(vuint8 **A,vuint8 **B,long nrl,long ncl,long nrh,long nch);
void ouverture3x3_SSE2(vuint8 **A,vuint8 **B,long nrl,long ncl,long nrh,long nch);


#endif

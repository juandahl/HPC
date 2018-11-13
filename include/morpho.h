#ifndef __MORPHO_H__
#define __MORPHO_H__


void routine_dilatation3x3(uint8** X,uint8** B, long nrl, long ncl, long nrh, long nch);
void routine_erosion3x3(uint8** X, uint8** B, long nrl, long ncl, long nrh, long nch);
void routine_fermeture3x3(uint8** A,uint8** B, long nrl, long ncl, long nrh, long nch);
void routine_ouverture3x3(uint8** A, uint8** B, long nrl, long ncl, long nrh, long nch);
void routine_dilatation5x5(uint8** X, uint8** B, long nrl, long ncl, long nrh, long nch);
void routine_erosion5x5(uint8** X, uint8** B, long nrl, long ncl, long nrh, long nch);
void routine_fermeture5x5(uint8** A, uint8** B, long nrl, long ncl, long nrh, long nch);
void routine_ouverture5x5(uint8** A, uint8** B, long nrl, long ncl, long nrh, long nch);

#endif

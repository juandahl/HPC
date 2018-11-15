//les implémentations SSE2


#include "mouvement_SSE2.h"



void routine_FrameDifference_SSE2(vuint8 **I1, vuint8 **I0, vuint8 **Et, long rawl, long rawh, long coll, long colh, vuint8 threshold)
{
 
    vuint8 tmpI1, tmpI0, tmpOt, tmpEt;
    vuint8 signe = init_vuint8(128);
    vuint8 Emouv = init_vuint8(255); //pixel blanc qui correspond à un mouvement

    for(int i = rawl; i <= rawh; i++ )
    {
        for(int j = coll; j <= colh; j++)
        {
            //Calcul de Ot, image de difference en niveau de gris
	    //chargement des pixels
            tmpI1 = _mm_load_si128(&I1[i][j]);
            tmpI0 = _mm_load_si128(&I0[i][j]);
	    //calcul valeur absolue
            vuint8 max = _mm_max_epu8(tmpI1, tmpI0);
            vuint8 min = _mm_min_epu8(tmpI1, tmpI0);
            tmpOt = _mm_sub_epi8(max, min);

            //Si Ot < 0, on a 255, sinon 0 donc on inverse pour avoir 255 sur Et quand Ot>=0 et 0 pour Ot < 0
            vuint8 result = _mm_cmplt_epi8(_mm_sub_epi8(tmpOt, signe), _mm_sub_epi8(threshold, signe)); //= 1 si < threshold sinon = 0

            result = _mm_andnot_si128(result, Emouv);
            _mm_store_si128(&Et[i][j], result);

        }
    }
};



void routine_SigmaDelta_step0_SSE2(vuint8** It1, vuint8 **M, vuint8 **V, long rawl, long rawh, long coll, long colh)
{
    vuint8 tmpIt1, tmpM, tmpV;
    vuint8 ecartTypeInit = init_vuint8(VMIN);

    for(int i = rawl; i <= rawh; i++ )
    {
        for(int j = coll; j <= colh; j++)
        {
            tmpIt1 = _mm_load_si128(&It1[i][j]); //M[i][j] = I[i][j];
            _mm_store_si128(&M[i][j], tmpIt1);
            _mm_store_si128(&V[i][j], ecartTypeInit); //V[i][j] = VMIN;
        }
    }
}




void routine_SigmaDelta_step1_SSE2(vuint8** It1,  vuint8** Vt0, vuint8** Vt1, vuint8** Mt0, vuint8** Mt1, vuint8 **Et, vuint8 **V, long rawl, long rawh, long coll, long colh)
{
    vuint8 tmpMt0, tmpVt0, tmpIt1, tmpMt, tmpVt1, tmpOt, tmpEt;
    vuint8 un = init_vuint8(1);
    vuint8 Vmax = init_vuint8(VMAX);
    vuint8 Vmin = init_vuint8(VMIN);
    vuint8 Mt0Add1, Mt0Sub1;
    vuint8 NTimesOt;
    vuint8 result;
    vuint8 Vt0Add1, Vt0Sub1;
    vuint8 signe = init_vuint8(128);
    vuint8 Emouv = init_vuint8(255); //pixel blanc qui correspond à un mouvement

    for(int i = rawl; i <= rawh; i++ )
    {
        for(int j = coll; j <= colh; j++)
        {
	    //step 1
	    tmpIt1 = _mm_load_si128(&It1[i][j]);
	    tmpVt0 = _mm_load_si128(&Vt0[i][j]);
	    tmpMt0 = _mm_load_si128(&Mt0[i][j]);

            Mt0Add1 = _mm_add_epi8(tmpMt0, un);
            Mt0Sub1 = _mm_sub_epi8(tmpMt0, un);

	    //Si Mt0 < It
            result = _mm_cmplt_epi8(_mm_sub_epi8(tmpMt0, signe), _mm_sub_epi8(tmpIt1, signe));
            tmpMt1 = _mm_or_si128(_mm_and_si128(result, Mt0Add1), _mm_andnot_si128(result, tmpMt0)); 

	    //Si Mt0 > It
            result = _mm_cmpgt_epi8(_mm_sub_epi8(tmpMt0, signe), _mm_sub_epi8(tmpIt1, signe));
            tmpMt1 = _mm_or_si128(_mm_and_si128(result, Mt0Sub1), _mm_andnot_si128(result, tmpMt1)); 


            //Step 2
	    //Ot = |Mt-It|
            vuint8 max = _mm_max_epu8(tmpIt1,tmpMt1);
            vuint8 min = _mm_min_epu8(tmpIt1, tmpMt1);
            tmpOt = _mm_sub_epi8(max, min); //valeur absolue
            
            //Step 3
	    NTimesOt = init_vuint8(0);
	    Vt0Add1 = _mm_add_epi8(tmpVt0, un);
            Vt0Sub1 = _mm_sub_epi8(tmpVt0, un);

            for(int k = 0; k < N; k++)
            {
                NTimesOt = _mm_adds_epu8(NTimesOt, tmpOt);
            }

	    // si Vt-1 < N*Ot
            result = _mm_cmplt_epi8(_mm_sub_epi8(tmpVt0, signe), _mm_sub_epi8(NTimesOt, signe));
            tmpVt1 = _mm_or_si128(_mm_and_si128(result, Vt0Add1), _mm_andnot_si128(result, tmpVt0)); 

	    //si Vt-1 > N*Ot
            result = _mm_cmpgt_epi8(_mm_sub_epi8(tmpVt0, signe), _mm_sub_epi8(NTimesOt, signe));
            tmpVt1 = _mm_or_si128(_mm_and_si128(result, Vt0Sub1), _mm_andnot_si128(result, tmpVt1));

	    //sinon
            tmpVt1 = _mm_max_epu8(_mm_min_epu8(tmpVt1, Vmax), Vmin);


            //Step 4
	    //si Ot < Vt
            result = _mm_cmplt_epi8(_mm_sub_epi8(tmpOt,signe), _mm_sub_epi8(tmpVt1,signe));

	    //Inverse les 255 et 0 pour avoir la bonne couleur de pixel
            vuint8 destination = _mm_andnot_si128(result, Emouv);

            _mm_store_si128(&Et[i][j], destination);
            _mm_store_si128(&Vt1[i][j], tmpVt1);
            _mm_store_si128(&Mt1[i][j], tmpMt1);
        }
    }

}








//morphologie mathématique


void dilatation3x3(uint8** X,uint8** B, long nrl,long nrh,long ncl,long nch)
{

	//Pour des images binaires, la dilatation consiste à calculer un OR sur le voisinage B dans l’image source
	// et à l’écrire dans l’image destination. Inversement l’érosion consiste à calculer un AND sur le voisinage.
    int i,j,k,l;
    uint8 result;
    for(i=nrl; i<=nrh; i++)
        for(j=ncl; j<=nch; j++)
        {
        	//it is inicialize in 0 because it is an Or
        	result = 0;
    	    for(k=j-1; k<=j+1; k++)
		        for(l=i-1; l<=i+1; k++)
		        	result = result | X[i][j];

            B[i][j] = result;
        }
}


//existe deux opérations de base : la dilatation de X notée  B(X) et l’érosion de X noté B(X).
void erosion3x3(uint8** X,uint8** B, long nrl,long nrh,long ncl,long nch)
{
    uint8 result;
    for( int i = nrl; i <= nrh; i++ )
        for( int j = ncl; j <= nch; j++ )
        {
        	//it is inicialize with 1 because it is an Or
        	result = 255;
    	    for( k = i-1; k <= i+1; k++ )
		        for(l = j-1; l <= j+1; k++)
		        	result = result & X[i][j];
		        
            B[i][j] = result;
        }
}





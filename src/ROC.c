#include "nrdef.h"
#include "nrutil.h"

#define RANGEMIN 0
#define RANGEMAX 300

int nrl, nrh, ncl, nch;

void get_results(uint8 **groundTruth,uint8 ** imageToCompare,long roc[2][2])
{
    //roc: [TP, FN; FP, TN]
    for(int i = nrl; i <= nrh; i++)
    {
        for(int j = ncl; j <= nch; j++)
        {
            if (groundTruth[i][j] == 255)
                if (imageToCompare[i][j] == 255)
                    roc[0][0]++;
                else
                    roc[0][1]++;
            else
                if (imageToCompare[i][j] == 255)
                        roc[1][0]++;
                    else
                        roc[1][1]++; 
        }
    }

}

void compare_with_ground_truth(char path[40])
{
    //initialization
	char imageToCompare[40];
    char nameGroundTruth[40];
    
	uint8 **groundTruth =  LoadPGM_ui8matrix("groundTruth/hall000000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8 **image = ui8matrix(nrl, nrh, ncl, nch);
	long roc[2][2] = { {0,0}, {0,0} };
    
    int pixelTotal = (nrh*nch);

    
    //calculate for each image
    for(int i = RANGEMIN; i < RANGEMAX; i++)
	{
        get_results(groundTruth, image, roc);
        sprintf(imageToCompare,"%s/hall000%03d%s.pgm",path, i);//Image a t
        MLoadPGM_ui8matrix(imageToCompare, nrl, nrh, ncl, nch, image);
        sprintf(nameGroundTruth,"groundTruth/hall000%03d%s.pgm",i);//Image a t
        MLoadPGM_ui8matrix(nameGroundTruth, nrl, nrh, ncl, nch, groundTruth);

    }

    //print results
    printf("ROC = \n%d %d\n%d %d\n",roc[0][0], roc[0][1], roc[1][0], roc[1][1]);
    printf("ROC average = \n%d %d\n%d %d\n",roc[0][0]/pixelTotal, roc[0][1]/pixelTotal, roc[1][0]/pixelTotal, roc[1][1]/pixelTotal);
    
    //free memory
    free_ui8matrix(groundTruth, nrl, nrh, ncl, nch);
    free_ui8matrix(image, nrl, nrh, ncl, nch);
}

#include "gauss.h"
#include <math.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int i,j,k;
    double mnoznik;
    double maxVal;
    int maxIdx;

    for(i=0;i<mat->r;i++){
        maxVal = fabs(mat->data[i][i]);
        maxIdx = i;

        for(j=i+1;j<mat->r;j++){
            if(fabs(mat->data[j][i]) > maxVal){
                maxVal = fabs(mat->data[j][i]);
                maxIdx = j;
            }
        }


        if(maxIdx != i){
            for(k=i; k<mat->c; k++){
                double temp = mat->data[i][k];
                mat->data[i][k] = mat->data[maxIdx][k];
                mat->data[maxIdx][k] = temp;
            }

            double tempB = b->data[i][0];
            b->data[i][0] = b->data[maxIdx][0];
            b->data[maxIdx][0] = tempB;
        }

        for(j=i+1; j<mat->r; j++){
            if(mat->data[i][i]==0){
                return 1;
            }
            mnoznik=mat->data[j][i]/mat->data[i][i];
            for(k=i;k<mat->c;k++){
                mat->data[j][k]=mat->data[j][k]-mnoznik*mat->data[i][k];
            }
            b->data[j][0]=b->data[j][0]-mnoznik*b->data[i][0];
        }
    }
    return 0;
}



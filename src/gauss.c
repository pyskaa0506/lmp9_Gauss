#include "gauss.h"
#include <math.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int i,j,k;
    double mnoznik;
    for(i=0;i<mat->r;i++){
        for(j=i+1;j<mat->r;j++){
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

/*To rozszerzenie metody eliminacji Gaussa polega na dodaniu procedury wyboru elementu diagolnego
Standartowo jest używany element diagonalny
Ale dla zwiększenia stabilności programu możemy zrobić tak, żeby pivot był wybrany
jako największy element w kolumnie.
*/

void rozszerzenie_gauss(double **matrix, double *wektor, int size) 
{
    //Wybieramy pivota jako element diagonalny
    for (int k = 0; k < size - 1; ++k) 
    {
        int indeks_pivot = k;
        double wartosc_pivot = fabs(matrix[k][k]);

        for (int i = k + 1; i < size; ++i) 
        {
            if (fabs(matrix[i][k]) > wartosc_pivot) 
            {
                wartosc_pivot = fabs(matrix[i][k]);
                indeks_pivot = i;
            }
        }

        if (indeks_pivot != k) //Zamieniamy wierszy w przypadku gdy pivot jest w innym wiersu
        {
            for (int j = 0; j < size; ++j) //zamieniamy wiersze
            {
                double temp = matrix[k][j];
                matrix[k][j] = matrix[indeks_pivot][j];
                matrix[indeks_pivot][j] = temp;
            }

            double temp = wektor[k]; //Zamieniamy elementy wektora prawych stron
            wektor[k] = wektor[indeks_pivot];
            wektor[indeks_pivot] = temp;
        }

        //Proces eliminacji Gaussa 
        for (int i = k + 1; i < size; ++i) //przechodzi przez wszystkie wiersze poniżej aktualnego
        {
            double wspolczynnik = matrix[i][k] / matrix[k][k]; //współ. do wyzerowania elementów po diagonali w pewnej kolumnkie k

            for (int j = k; j < size; ++j)  //przechodzi przez wszystkie elementy w aktualnym wierszu
            {
                matrix[i][j] -= wspolczynnik * matrix[k][j]; //redukcja elementów
            }

            wektor[i] -= wspolczynnik * wektor[k]; //redukcja elementów wektora prawych stron 
        }
    }
}


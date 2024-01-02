#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b)
{
	int n = mat -> r;
	double sum = 0.0;

	//return 2; nieprawidłowy rozmiar macierzy
	if (mat->r != mat->c || x->r != mat->r || b->c != 1 || b->r != mat->r || x->c != 1 )
	{
		/*
		mat->r != mat->c czy liczba wierszy (r) nie jest równa liczbie kolumb (c); tzn - macierz nie jest kwadratowa
		x->r != mat->r czy liczba wrs mac. X nie równa lb. wiersz. mac. Mat
		b->c != 1 czy liczba kolumn mac. b nie równa 1
		b->r != mat->r czy liczba wier. mac. b nie równa lb. lb. wiers. mac. Mat
		x->c != 1 czy lb. kolumn mac. X nie równa 1
		*/
		return 2;
	}

    for (int i = n-1; i >= 0; i--) //iteruje macierz od ostatniego do pierwszego wiersza
    {
        double sum = 0.0; // Zerowanie sumy dla każdego wiersza

        for (int j = i + 1; j < n; j++) {  //iteruje po kolumnach
            sum += mat->data[i][j] * x->data[j][0]; //suma iloczynów współczynników i odpowiednich wartości x
        }

        if (mat -> data[i][i] == 0.0) { //czy element przekątnej wynosi 0
            return 1;
        }
    // obliczanie rozwiązania x dla pewnego (bieżącego) wiersza za pomocą podstawienia wstecznego
        x->data[i][0] = (b->data[i][0] - sum) / mat->data[i][i];
    }


	return 0;
}



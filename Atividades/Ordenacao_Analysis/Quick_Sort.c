#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void quickSort(int array[], int inicio, int fim) {

    void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
    }

    int particiona (int array[], int inicio, int fim) {
        int pivo = array[fim];
        int i = (inicio - 1);

        for (int j = inicio; j <= fim - 1; j++) {
            if (array[j] < pivo) {
                i++;
                swap(&array[i], &array[j]);
            }
        }
        swap(&array[i + 1], &array[fim]);
        return (i + 1);
    }

    if (inicio < fim) {

        int pi = particiona(array, inicio, fim);

        quickSort(array, inicio, pi - 1);
        quickSort(array, pi + 1, fim);
    }
}

int main() {
    int n;
    time_t t;
    double quick_time;
    clock_t inicio, fim;

    printf("Digite o tamanho maximo do array:\n");
    scanf("%d", &n);

    int array [n];

    srand(time(&t));

    /**
    //Povoando Array Randomicamente
    for (int i = 0; i < n; i++){
        array[i] = rand()%n;
    }
    */

    /**
    //Povoando Array Ordem Crescente
    for (int i = 0; i <= n; i++)
        array[i] = i;
    */


    //Povoando Array Ordem Decrescente
    int aux = n;

    for (int i = 0; i < n; i++){
        array[i] = aux;
        aux--;
    }


    printf("Array desordenado:\n\t[");
    for (int i = 0; i < n; i++)
        printf("%d\t", array[i]);

    printf("]\n\n");

    inicio = clock();
    quickSort(array, 0, n-1);
    fim = clock();

    printf("Array ordenado:\n\t[");
    for (int i = 0; i < n; i++){
        printf("%d,\t", array[i]);
    }


    quick_time = ((double)fim - (double)inicio) / (double)CLOCKS_PER_SEC;

    printf("]\n\n");

    printf("Tempo de execucao para n = %d e de: %lf\n", n, quick_time);



    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *vet, int tam){
    int i, j, aux;

    for(i = 1; i < tam; i++){
        aux = vet[i];
        for(j = i; (j > 0) && (aux < vet[j - 1]); j--){
            vet[j] = vet[j - 1];
        }
        vet[j] = aux;
    }
}

int main() {
    int n;
    time_t t;
    double insertion_time;
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
    insertionSort(array,n);
    fim = clock();

    printf("Array ordenado:\n\t[");
    for (int i = 0; i < n; i++){
        printf("%d,\t", array[i]);
    }


    insertion_time = ((double)fim - (double)inicio) / (double)CLOCKS_PER_SEC;

    printf("]\n\n");

    printf("Tempo de execucao para n = %d e de: %lf\n", n, insertion_time);



    return 0;
}


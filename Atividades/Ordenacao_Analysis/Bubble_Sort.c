#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int vet[], int tam){
    int i, j, aux;

    for (i = 0 ; i < tam; i++){
        for (j = 0 ; j < tam - i; j++){
            if (vet[j] > vet[j+1]){
                aux = vet[j];
                vet[j]   = vet[j+1];
                vet[j+1] = aux;
             }
         }
     }
}


int main() {
    int n;
    time_t t;
    double bubble_time;
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
    bubble_sort(array, n);
    fim = clock();

    printf("Array ordenado:\n\t[");
    for (int i = 0; i < n; i++){
        printf("%d,\t", array[i]);
    }


    bubble_time = ((double)fim - (double)inicio) / (double)CLOCKS_PER_SEC;

    printf("]\n\n");

    printf("Tempo de execucao para n = %d e de: %lf\n", n, bubble_time);



    return 0;
}

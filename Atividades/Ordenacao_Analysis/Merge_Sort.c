#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void mergeSort (int *vet, int inicio, int fim){

    void merge(int *vet, int inicio, int meio, int fim){
        int *aux, p1, p2, tam, i, j, k;
        int fim1 = 1, fim2 = 1;
        tam = fim-inicio+1;
        p1 = inicio;
        p2 = meio +1;

        aux = (int *) malloc(tam*sizeof(int));

        for (i = 0; i < tam; i++){
            if(fim1 && fim2){
                if(vet[p1] < vet[p2]){
                    aux[i] = vet[p1++];
                }
                else{
                    aux[i] = vet[p2++];
                }
                if(p1 > meio)
                    fim1 = 0;
                if(p2 > fim)
                    fim2 = 0;
            }
            else{
                if(fim1){
                    aux[i] = vet[p1++];
                }
                else{
                    aux[i] = vet[p2++];
                }
            }
        }
        for(j = 0, k = inicio; j < tam; j++, k++){
            vet[k] = aux[j];
        }

        free(aux);
    }

    int meio;
    if (inicio < fim){
        meio = (inicio + fim)/2;
        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio+1, fim);
        merge(vet, inicio, meio, fim);
    }
}

int main() {
    int n;
    time_t t;
    double merge_time;
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
    mergeSort(array, 0, n-1);
    fim = clock();

    printf("Array ordenado:\n\t[");
    for (int i = 0; i < n; i++){
        printf("%d,\t", array[i]);
    }


    merge_time = ((double)fim - (double)inicio) / (double)CLOCKS_PER_SEC;

    printf("]\n\n");

    printf("Tempo de execucao para n = %d e de: %lf\n", n, merge_time);



    return 0;
}



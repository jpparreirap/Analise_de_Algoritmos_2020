/**
    Implementação Livro do Cormen
*/
#include <limits.h>
#include <stdio.h>

int MatrixChainOrder(int p[], int n){

    int m[n][n];
    int i, j, k, l, q;

    for (i = 1; i < n; i++)
        m[i][i] = 0;

    for (l = 2; l < n; l++){
        for (i = 1; i < n - l + 1; i++){
            j = i + l - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++){
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    return m[1][n - 1];
}

int main(){
    int p[] = { 30, 35, 15, 5, 10, 20, 25 };
    int tam = sizeof(p) / sizeof(p[0]);

    printf("Numero minimo de multiplicacoes: %d\n", MatrixChainOrder(p, tam));

    return 0;
}

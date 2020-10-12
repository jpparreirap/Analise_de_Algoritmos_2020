#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int m, p, r;
float q, s, pr, qs, y, uv;

float karatsuba(int u, int v, int n){ //sendo que u e v são numeros naturais
    if (n <= 3)
        return u*v;
    m = ceil(n/2); //pega o teto
    p = floor(u/pow(10, m)); //pega o piso
    q = fmod(u, pow(10,m)); //resto da divisao
    r = floor(v/pow(10, m));
    s = fmod(v, pow(10,m));
    pr = karatsuba(p, r, m);
    qs = karatsuba(q, s, m);
    y = karatsuba(p+q, r+s, m+1);

    uv = pr * pow(10, 2*m) + (y - pr - qs) * pow(10, m) + qs;

    return uv;
}

int main(){
    int u, v, n;


    printf("Digite o n maximo digitos de u e v :\n");
    scanf("%d", &n);

    char str[n];

    for (int i = 0; i < n; i++){
        str[i] = '9';
    }

    printf("Digite o numero natural u:\n");
    scanf("%d", &u);

    if (u > atoi(str)){
        printf("Numero natural invalido, digite um numero de ate %d digitos:\n", n);
        scanf("%d", &u);
    }

    printf("Digite o numero natural v:\n");
    scanf("%d", &v);

    if (v > atoi(str)){
        printf("Numero natural invalido, digite um numero de ate %d digitos:\n", n);
        scanf("%d", &v);
    }

    printf("Resultado do algoritmo de karatsuba: %.2lf\n", karatsuba(u, v, n));


    return 0;
}

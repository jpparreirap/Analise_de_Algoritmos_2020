#include <stdio.h>

int fat(n) {
    if ((n == 1) || (n == 0)) 
        return 1;
    else 
        return n * fat(n-1);
}

main() {
    int n;
    printf("Informe o numero que deseja obter o fatorial:\n");
    scanf("%d", &n);
    printf("O fatorial de %d = %d", n, fat(n));
}
#include <stdio.h>

int fat(n) {
    if ((n == 1) || (n == 0)) return 1;
    else return fat(n-1)*n;
}

main() {
    int n;
    printf("Informe o numero que deseja obter o fatorial:\n");
    scanf("%d", &n);
    printf("O fatorial de %d = %d", n, fat(n));
}
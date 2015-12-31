/**
Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков
пирамиду.
Формат входных данных:
На вход подается количество кубиков N.
Формат выходных данных:
Вывести число различных пирамид из N кубиков.
Широкая пирамида. Каждый вышележащий слой пирамиды должен быть строго меньше
нижележащего.
*/

#include <stdio.h>
#include <stdlib.h>

double dec(int n, int k, double **d) {
    if ( n < 0  || k < 0) return 0;
    if(k == 1) {
        if(n == 1) {
            return 1;
        }
        return 0;
    }
    else if(n <= 2) {
        return 1;
    }

    if ( d[n][k] >= 0 ) return d[n][k];

    d[n][k] =  dec(n, k-1, d) + dec(n-k, k-1, d);

    return d[n][k];
}

int main() {
    int m, i, j;
    scanf("%d", &m);

    double **d = (double **) malloc(sizeof(double *) * (m + 1));

    for (i = 0; i < m + 1; i++) {
        d[i] = (double *) malloc(sizeof(double) * (m + 1));
        for (j = 0; j < m + 1; j++) {
            d[i][j] = -1;
        }
    }
    printf("%.0f\n", dec(m, m, d));

    for(int i = 0; i < m + 1; i++) {
        free(d[i]);
    }
    free(d);
    return 0;
}

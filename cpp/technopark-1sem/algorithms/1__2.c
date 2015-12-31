/**
Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. Найти количество
таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
n, m ≤ 100000.
Указание. Обходите массив B от конца к началу.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int countIndexes(int, int *, int, int*, int);

/**
 * Main
 */
int main() {
    int lengthA = 0,
                 lengthB = 0,
                 *arrayA = NULL,
                 *arrayB = NULL;

    // ввод длины массива А
    if(scanf("%d", &lengthA) != 1) {
        return 0;
    }
    assert(lengthA > 0);

    // ввод массива А
    arrayA = (int *) malloc(lengthA * sizeof(int));
    for(int i = 0; i < lengthA; i++) {
        if(scanf("%d", arrayA + i) != 1) {
            printf("%d", *(arrayA+i));
            free(arrayA);
            return 0;
        }
    }

    // ввод длины массива B
    if(scanf("%d", &lengthB) != 1) {
        return 0;
    }
    assert(lengthB > 0);

    // ввод массива B
    arrayB = (int *) malloc(lengthB * sizeof(int));
    for(int i = 0; i < lengthB; i++) {
        if(scanf("%d", arrayB + i) != 1) {
            free(arrayA);
            free(arrayB);
            return 0;
        }
    }

    // ввод k
    int k = 0;
    if(scanf("%d", &k) != 1) {
        free(arrayA);
        free(arrayB);
        return 0;
    }

    // подсчет индексов и вывод
    int result = countIndexes(lengthA, arrayA, lengthB, arrayB, k);
    printf("%d", result);

    // очистка памяти
    free(arrayA);
    free(arrayB);

    return 0;
}

/**
 * Подсчет кол-ва индексов, удовлетворяющих условию
 */
int countIndexes(int lengthA, int *arrayA, int lengthB, int *arrayB, int k) {
    int lastJ = 0, // последний ключ в A
        res = 0; // кол-во индексов

    // обход B
    for(int i = lengthB - 1; i >= 0; i--) {
        int b = arrayB[i]; // текущий элемент b

        // обход А с j, которое не удовлетворило условию для прошлого b
        for(int j = lastJ; j < lengthA; j++) {
            int sum = b + arrayA[j];
            if(sum == k) {
                // правильная сумма
                res++;
                //printf("%d %d =%d\n", b, arrayA[j], sum);
            }
            else if(sum > k) {
                // сумма больше, чем надо
                // сохраняем значение j для следующего b
                lastJ = j;
                break;
            }
        }
    }
    return res;
}

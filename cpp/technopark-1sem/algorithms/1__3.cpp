/**
Дан отсортированный массив целых чисел A[0..n­1] и массив целых чисел B[0..m­1]. Для каждого
элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
Время работы поиска для каждого элемента B[i]: O(log(k)).
n ≤ 100000, m ≤ 1000.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int inputNumbers(int **);
int getNearestValueIndex(int, int *, int);

int main() {
    // ввод массива A
    int *arrayA = NULL,
        countA = inputNumbers(&arrayA);

    if(countA < 1) {
        return 0;
    }

    // ввод массива B
    int *arrayB = NULL,
        countB = inputNumbers(&arrayB);

    if(countB < 1) {
        return 0;
    }

    // поиск нужных индексов
    for(int i = 0; i < countB; i++) {
        int res = getNearestValueIndex(arrayB[i], arrayA, countA);
        printf("%d ", res);
    }

    free(arrayA);
    free(arrayB);

    return 0;
}

/**
 * Ввод массива чисел
 */
int inputNumbers(int **result) {
    *result = NULL;

    int count = 0;
    if(scanf("%d", &count) != 1) {
        return -1;
    }

    int *array = (int *) malloc(count * sizeof(int));
    if(array == NULL) {
        return -1;
    }
    for(int i = 0; i < count; i++) {
        if(scanf("%d", array + i) != 1) {
            free(array);
            return -1;
        }
    }
    *result = array;
    return count;
}

/**
 * Индекс ближайшего к b значения из массива arrayA длиной countA
 */
int getNearestValueIndex(int b, int *arrayA, int countA) {
    // простые случаи - b за границами массива arrayA
    if(b < arrayA[0]) {
        return 0;
    }
    else if(b > arrayA[countA - 1]) {
        return countA - 1;
    }

    // определяем границы (через i^2)
    int first = 0,
        last = countA - 1;

    for(int i = first; i * i < last; i++) {
        int curSquare = i*i;
        if(arrayA[curSquare] < b) {
            first = curSquare;
        }
        else if(arrayA[curSquare] > b) {
            last = curSquare;
        }
    }

    // бинарный поиск
    while(last - first > 1) {
        int mid = (last + first) / 2;
        if(arrayA[mid] >= b) {
            last = mid;
        }
        else
        {
            first = mid;
        }
    }

    int minIndex = first,
        maxIndex = last;
    if(minIndex == maxIndex && minIndex > 0) {
        minIndex--;
    }
    return (b - arrayA[minIndex] <= arrayA[maxIndex] - b) ? minIndex : maxIndex;
}

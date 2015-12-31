/**
Составить программу определения такой максимальной последовательности среди элементов заданного
целочисленного массива, элементы которой увеличиваются по порядку. Элементы последовательности
функция должна вернуть через указатель-параметр, а ее длину — через возвращаемый результат
Формат входных данных N - длина последовательности A1 ... An - последовательность Формат выходных
данных N - длинна найденной подпоследовательности A1 ... An - подпоследовательность
Если заданная подпоследовательность не найдена, или если найдена только вырожденная
подпоследовательность(длиной 1), необходимо вывести только длину - 0. Программа должна уметь 
обрабатывать ошибки во входных данных (отрицательные числа и др.). В случае возникновения ошибки 
нужно вывести в поток стандартного вывода сообщение "[error]" и завершить выполнение программы.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void onError();
static size_t inputNumbers(int **);
static size_t getSequence(int *, size_t, int **);

int main() {
    // ввод массива
    int *array = NULL;
    size_t arrayCount = inputNumbers(&array);

    if(arrayCount == 0) {
        // ввели 0 элементов
        printf("0");
        return 0;
    }

    // поиск последовательности
    int *sequence = NULL;
    size_t sequenceCount = getSequence(array, arrayCount, &sequence);
    if(sequenceCount <= 1) {
        // вырожденная последовательность (длиной 1)
        free(array);
        free(sequence);
        printf("0");
        return 0;
    }

    // вывод найденной последовательности
    printf("%zu\n", sequenceCount);
    for(size_t i = 0; i < sequenceCount; i++) {
        if(i > 0) {
            printf(" ");
        }
        printf("%d", *(sequence + i));
    }

    // очистка памяти
    free(array);
    free(sequence);

    return 0;
}

/**
 * Ввод чисел и сохранение их в массив
 */
size_t inputNumbers(int **numbers) {
    // проверка входных данных
    assert(numbers != NULL);
    
    int count = 0;
    *numbers = NULL;

    // ввод длины массива
    if(scanf("%d", &count) == 1) {
        if(count > 0) {
            // выделили память
            *numbers = (int *) malloc(count * sizeof(int));

            if(*numbers) {
                for(size_t i = 0; i < count; i++) {
                    // вводим числа
                    if(scanf("%d", (*numbers) + i) != 1) {
                        // не удалось ввести
                        free(*numbers);
                        onError();
                    }
                }
                return count;
            }
            else
            {
                // не удалось выделить память
                onError();
            }
        }
        else if(count == 0)
        {
            // число элементов = 0
            return count;
        }
        else
        {
            // число элементов < 0
            onError();
        }
    }
    else
    {
        // не удалось считать число элементов в массиве
        onError();
    }
    return 0;
}

/**
 * Поиск последовательности
 */
size_t getSequence(int *numbers, size_t count, int **result) {
    // проверка входных данных
    assert(numbers != NULL); // массив
    assert(count > 0); // длина массива
    assert(result != NULL); // результирующий массив

    size_t sequenceCount = 1, // длина текущей последовательности
           maxSequenceCount = 1; // макс. длина
    int *sequenceStart = numbers, // начало текущей последовательности
        *maxSequenceStart = numbers;

    for(size_t i = 1; i < count; i++) {
        if(*(numbers + i - 1) < *(numbers + i)) {
            // последовательность продолжается
            sequenceCount++;
        }
        else {
            // последовательность нарушена
            if(sequenceCount > maxSequenceCount) {
                // длина последовательности оказалась максимальной
                maxSequenceCount = sequenceCount;
                maxSequenceStart = sequenceStart;
            }
            // начинаем последовательность заново
            sequenceCount = 1;
            sequenceStart = numbers + i;
        }
    }

    if(sequenceCount > maxSequenceCount) {
        // длина последовательности оказалась максимальной
        maxSequenceCount = sequenceCount;
        maxSequenceStart = sequenceStart;
    }

    *result = NULL;

    if(maxSequenceCount > 1) {
        // нашли невырожденную последовательность
        int *tmpResult = (int *) malloc(maxSequenceCount * sizeof(int));
        if(tmpResult == NULL) {
            // не удалось выделить память под последовательность
            onError();
        }
        
        for(size_t i = 0; i < maxSequenceCount; i++) {
            tmpResult[i] = maxSequenceStart[i];
        }
        *result = tmpResult;
    }

    return maxSequenceCount;
}

/**
 * Действия при ошибке: вывод [error] и выход с кодом 0
 */
void onError() {
    printf("[error]");
    exit(0);
}
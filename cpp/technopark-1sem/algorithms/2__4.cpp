/*
Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте
методом прохода двумя итераторами от начала массива к концу.
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется 
найти k­ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k 
(0..n­1) в отсортированном массиве. Напишите нерекурсивный алгоритм.  
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).  
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном 
направлении. Описание для случая прохода от начала массива к концу: 
● Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.  
● Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.  
Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат 
нерассмотренные элементы. Последним элементом лежит опорный.  
● Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.  
● Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.  
● Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, 
то сдвигаем j.  
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.  
● В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
*/

#include <iostream>

// выбор опорного элемента
// медиана трёх
template<class T>
size_t selectPivot(T *data, size_t l, size_t r) {
    size_t half = (l + r - 1) / 2; // середина списка

    // выбор среднего из трех элементов
    if(data[l] < data[half]) {
        if(data[r] < data[l]) {
            return l;
        }
        else if(data[r] < data[half]) {
            return r;
        }
        return half;
    }
    else
    {
        if(data[r] < data[half]) {
            return half;
        }
        else if(data[r] < data[l]) {
            return r;
        }
        return l;
    }
}

// partition
template<class T>
size_t partition(T *data, size_t l, size_t r) {
    size_t pivotPos = selectPivot(data, l, r);

    if(pivotPos != r - 1) { // меняем местами опорный элемент с последним
        std::swap(data[r - 1], data[pivotPos]);
    }

    size_t i = l, j = l;
    T pivot = data[r - 1];
    while(j < r - 1) {
        if(data[j] <= pivot) {
            // текущий элемент не больше опорного
            // меняем его с первым из больших
            std::swap(data[i++], data[j]);
        }
        j++;
    }
    if(i != r - 1) { // ставим опорный элемент на место
        std::swap(data[i], data[r - 1]);
    }
    return i;
}

// поиск к-ой порядковой статистики
template<class T>
T findKStatistics(T *data, size_t l, size_t r, size_t k) {
    size_t lastPivotPos = 0,
           left = l,
           right = r;
    while(left < right) {
        if((lastPivotPos = partition(data, left, right)) == k) { // нашли
            return data[lastPivotPos];
        }
        else if(lastPivotPos > k) {
            // опорный элемент оказался правее искомого
            right = lastPivotPos;
        }
        else
        {
            // опорный элемент не дошел до искомого
            left = lastPivotPos + 1;
        }
    }
    return data[lastPivotPos];
}

int main() {
    size_t n = 0, // количество элементов в массиве
           k = 0; // номер для поиска порядковой статистики

    std::cin >> n >> k;

    int *numbers = new int[n];
    for(size_t i = 0; i < (size_t) n; i++) {
        std::cin >> numbers[i];
    }

    std::cout << findKStatistics(numbers, 0, (size_t) n, k);

    delete[] numbers;
}

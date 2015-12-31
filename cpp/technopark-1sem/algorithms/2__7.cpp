/*
7_1. Быстрейшая сортировка.
Дан массив целых чисел в диапазоне [0..10^9]. Размер массива ограничен сверху значением 2.5 * 10^7 элементов. Все значения массива являются элементами псевдо­рандомной
последовательности.
В контест необходимо отправить реализацию функции
voidFastSort(int *vector, int n);
За основу должна быть взят алгоритм быстрой сортировки.
Набор оптимизаций, который необходимо реализовать:
1. Оптимизация выбора опорного элемента.
2. Оптимизация Partition.
3. Оптимизация концевой рекурсии.
4. Написать без рекурсии. */

#include <iostream>
#include <string.h>
#include <assert.h>
#include <cmath>

#define STACK_MIN_LENGTH 10
#define QUICK_SORT_STOP_LENGTH 7

template<class T>
class Stack {
private:
    T *_buffer; // буфер
    int _bufferSize; // размер буфера
    int _size; // действительное количество элементов

    // выделение/перевыделение памяти
    void _resize(int newBufferSize = STACK_MIN_LENGTH) {
        T *newBuffer = new T[newBufferSize];

        if(_buffer != NULL && _size > 0) {
            memmove(newBuffer, _buffer, _size * sizeof(T));
        }

        delete[] _buffer;
        _buffer = newBuffer;
        _bufferSize = newBufferSize;
    }

public:
    // конструктор
    Stack(int size = STACK_MIN_LENGTH) : _buffer(NULL), _bufferSize(0), _size(0) {
        _resize(size);
    }

    // стек пуст?
    bool isEmpty() {
        return _size < 1;
    }

    // добавить в стек
    void push(const T &val) {
        if(_size == _bufferSize) {
            _resize(_bufferSize * 2);
        }

        _buffer[_size++] = val;
    }

    // убрать из стека и вернуть удаленное значение
    T pop() {
        assert(!isEmpty());
        return _buffer[--_size];
    }

    // деструктор
    ~Stack() {
        delete[] _buffer;
    }
};

// выбираем опорный элемент
// медиана трёх
// медиана медиан работает медленно :(
template<class T>
int getPivot(T *data, int start, int end) {
    int pivotPos = 0, half = (start + end - 1) / 2 - 1;
    if (data[start] < data[half]) {
        pivotPos = 0;
        if (data[half] < data[end - 1]) {
            pivotPos = half;
        }
        else if(data[start] < data[end - 1]) {
            pivotPos = end - 1;
        }
    }
    else
    {
        pivotPos = end - 1;
        if (data[end - 1] < data[half]) {
            pivotPos = half;
        }
        else if (data[start] < data[end - 1]) {
            pivotPos = start;
        }
    }
    return pivotPos;
}

// partition
template<class T>
int partition(T *data, int start, int end, int pivotPos) {
    if (pivotPos < start)
        pivotPos = start;
    if (pivotPos > end)
        pivotPos = end;

    if (start == end)
        return pivotPos;

    std::swap(data[pivotPos], data[end]);
    pivotPos = end;

    int i = start,
        j = i;
    while(j < end) {
        if(data[j] <= data[pivotPos]) {
            if (i != j)
                std::swap(data[j], data[i]);
            ++i;
            ++j;
        }
        if(j < end) {
            while(data[j] > data[pivotPos]) {
                if(++j == end) break;
            }
        }
    }
    std::swap(data[i], data[pivotPos]);
    pivotPos = i;
    return pivotPos;
}

// быстрая сортировка
template<class T>
void quickSort(T *data, int start, int end) {
    Stack<T> stack(2 * log2(end - start) + 2);
    // предполагаем, что в один момент времени в стеке будет log2(n) "вызовов" qsort и еще один вызов на всякий случай 

    int first = start;
    int last = end - 1;
    stack.push(first);
    stack.push(last);
    int pivotPos = 0;

    // вместо рекурсии [стека вызовов] используем свой стек
    while(!stack.isEmpty()) {
        last = stack.pop();
        first = stack.pop();

        if(last - first < QUICK_SORT_STOP_LENGTH) {
            continue;
        }
        else
        {
            pivotPos = getPivot<T>(data, first, last);
            pivotPos = partition<T>(data, first, last, pivotPos);

            if(pivotPos < last) {
                stack.push(pivotPos + 1);
                stack.push(last);
            }
            if(first < pivotPos - 1) {
                stack.push(first);
                stack.push(pivotPos - 1);
            }
        }

    }
}

// сортировка вставками
template<class T>
void insertionSort(T *data, int left, int right) {
    for (int i = left + 1; i < right; i++) {
        // бинарный поиск места вставки
        int l = 0, r = i;
        T toSearch = data[i];
        while(l < r) {
            int middle = (l + r) / 2;
            if(toSearch > data[middle]) {
                l = middle + 1;
            }
            else {
                r = middle;
            }
        }

        int position = r;
        if(position < i ) {
            T temp = data[i];
            memmove(&data[position+1], &data[position], (i - position) * sizeof(T));
            data[position] = temp;
        }
    }
}

// функция для контеста
void FastSort(int *data, int n) {
    // сначала быстрая сортировка
    quickSort(data, 0, n);
    // а потом вставками подкорректируем
    insertionSort(data, 0, n);
}

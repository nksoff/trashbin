/**
Закраска прямой 2.
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого
отрезка (Li и Ri). Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
*/

#include <iostream>
#include <cstring>
#include <assert.h>
#include <map>

// КУЧА <тип элемента>
template <class T>
class Heap {
private:
    T* _buffer; // выделенная память
    size_t _size; // количество элементов в куче
    size_t _bufferSize; // количество элементов, на которые выделена память
    bool (*_lessFunc)(const T &, const T &); // функция сравнения на меньше

    // выделение памяти
    void growBufferSize(size_t n = 0) {
        if(n < _bufferSize) return;

        size_t newBufferSize = (n > 0) ? n : 5;

        T *newBuffer = new T[newBufferSize];

        for(size_t i = 0; i < _size; i++) {
            newBuffer[i] = _buffer[i];
        }

        delete[] _buffer;
        _buffer = newBuffer;
        _bufferSize = newBufferSize;
    }

    // проталкиваем элемент вверх
    void siftUp(size_t index) {
        size_t parent = ((int) index - 1) / 2;
        while(_lessFunc(_buffer[parent], _buffer[index])) {
            // если потомок > своего бати, то меняем их местами
            std::swap(_buffer[index], _buffer[parent]);
            index = parent;
        }
    }

    // проталкиваем элемент вниз
    void siftDown(size_t index) {
        while(2 * index + 1 < _size) {
            size_t left = index * 2 + 1; // индекс левого потомка
            size_t right = left + 1; // индекс правого потомка
            size_t k = left; // индекс наибольшего из потомков
            if (right < _size && _lessFunc(_buffer[left], _buffer[right])) {
                ++k;
            }
            if (_lessFunc(_buffer[index], _buffer[k])) { // батя меньше потомка
                // меняем местами батю и потомка
                std::swap(_buffer[k], _buffer[index]);
                index = k;
            } else {
                break;
            }
        }
    }

public:
    // конструктор [неотсортированный массив, количество элементов]
    // работает локально!!! массив не будет откопирован
    Heap(T *buffer, size_t size, bool (*lessFunc)(const T &, const T &)) : _buffer(buffer), _size(size), _bufferSize(size), _lessFunc(lessFunc) {
        // превращаем неотсортированный массив в кучу за линейное время
        for (int i = size/2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    T* getBuffer() {
        return _buffer;
    }

    // получаем кол-во элементов в куче
    size_t getSize() {
        return _size;
    }

    // возвращает значение с вершины кучи, НЕ УДАЛЯЯ его из кучи
    const T &peek() {
        assert(_size > 0);
        return _buffer[0];
    }

    // возвращает значение с вершины кучи, УДАЛЯЯ его из кучи
    T popPeek() {
        assert(_size > 0);
        T elem = _buffer[0];

        _size--;
        if(_size > 0) {
            std::swap(_buffer[0], _buffer[_size]);
            siftDown(0);
        }

        return elem;
    }

    // добавляем элемент в кучу
    void insert(const T &elem){
        if(_bufferSize == _size) {
            growBufferSize(_bufferSize * 2);
        }

        _buffer[_size] = elem;
        siftUp(_size);
        _size++;
    }
};

// точка
class Point {
public:
    long x; // координата
    bool start; // начало
    Point(long _x = 0, bool _start = false) : x(_x), start(_start) {}
};

// сравнение точек
bool isPointLess(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

// пирамидальная сортировка
template<class T>
void heapSort(T *data, size_t left, size_t right, bool (*isLess)(const T &, const T &)) {
    Heap<T> heap(data + left, right - left, isLess);

    for(size_t i = left; i < right; i++) {
        heap.popPeek();
    }
}

// определение длины, на которой есть только один слой
int getSingleLayerNumber(Point *points, size_t n) {
    int result = 0;

    heapSort<Point>(points, 0, n, &isPointLess);

    long lastStart = -1;
    int curLayers = 0;

    for(size_t i = 0; i < n; i++) {
        bool was1 = (curLayers == 1);

        curLayers += (points[i].start) ? 1 : -1;

        if(curLayers == 1) {
            // теперь один слой, сохраняем координату
            lastStart = points[i].x;
        }
        else if(was1) {
            // был один слой, а теперь нет
            result += (points[i].x - lastStart);
        }
    }

    return result;
}

int main() {
    size_t n = 0;
    std::cin >> n;

    n *= 2;
    Point *points = new Point[n];

    for(size_t i = 0; i < n; i++) {
        std::cin >> points[i].x;
        points[i].start = (i % 2 == 0);
    }

    std::cout << getSingleLayerNumber(points, n);

    delete[] points;
    return 0;
}

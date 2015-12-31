/**
Жадина.
Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью. Определить за сколько подходов Вовочка съест все фрукты в корзине.
Формат входных данных. Вначале вводится n ­ количество фруктов и n строк с массами фруктов.
Затем K ­ "грузоподъемность".
Формат выходных данных. Неотрицательное число ­ количество подходов к корзине.
*/

#include <iostream>
#include <cstring>
#include <assert.h>
#include <vector>

// сравнение с помощью оператора <
template <class T>
bool isLess(const T &obj1, const T &obj2) {
    return obj1 < obj2;
}

// КУЧА <тип элемента, функция для сравнения на меньше>
template <class T, bool (*lessFunc)(const T &, const T &)>
class Heap {
private:
    T* _buffer; // выделенная память
    size_t _size; // количество элементов в куче
    size_t _bufferSize; // количество элементов, на которые выделена память

public:
    // конструктор [количество элементов]
    Heap(size_t dataSize = 0): _buffer(NULL), _size(0), _bufferSize(0) {
        growSize(dataSize);
    }

    // конструктор [неотсортированный массив, количество элементов]
    Heap(const T *data, size_t size) : _buffer(NULL), _size(0), _bufferSize(0) {
        growSize(size);
        memcpy(&_buffer[0], &data[0], sizeof(T) * size);
        _size = size;

        // превращаем неотсортированный массив в кучу за линейное время
        for (int i = size/2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    // деструктор
    ~Heap() {
        delete[] _buffer;
    }

    // получаем кол-во элементов в куче
    size_t getSize() {
        return _size;
    }

    // выделение памяти
    void growSize(size_t n = 0) {
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

    // возвращает значение с вершины кучи, НЕ УДАЛЯЯ его из кучи
    T peek() {
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
    void insert(T elem){
        if(_bufferSize == _size) {
            growSize(_bufferSize * 2);
        }

        _buffer[_size] = elem;
        siftUp(_size);
        _size++;
    }

    // проталкиваем элемент вверх
    void siftUp(size_t index) {
        size_t parent = ((int) index - 1) / 2;
        while(lessFunc(_buffer[parent], _buffer[index])) {
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
            if (right < _size && lessFunc(_buffer[left], _buffer[right])) {
                ++k;
            }
            if (lessFunc(_buffer[index], _buffer[k])) { // батя меньше потомка
                // меняем местами батю и потомка
                std::swap(_buffer[k], _buffer[index]);
                index = k;
            } else {
                break;
            }
        }
    }

    // вывод содержимого кучи
    void show() {
        for(size_t i = 0; i < _size; i++) {
            std::cout << _buffer[i] << std::endl;
        }
    }
};

// считаем количество шагов для поедания парнем фруктов
template <class T>
int countEatingSteps(T *fruits, size_t left, size_t right, T maxWeight) {
    int steps = 0; // количество шагов

    // превращаем фрукты в кучу фруктов
    Heap<T, isLess> fruitsHeap(fruits + left, right);

    // временный буфер
    std::vector<T> buffer;

    T curWeight = 0, // вес текущего фрукта
      totalWeight = 0; // вес фруктов на текущем шаге

    while(true) {
        // взяли фрукт
        curWeight = fruitsHeap.getSize() > 0 ? fruitsHeap.peek() : 0;

        if(fruitsHeap.getSize() > 0 && totalWeight + curWeight <= maxWeight) {
            // парень может взять текущий фрукт
            totalWeight += fruitsHeap.popPeek();
            if(curWeight != 1) {
                // съел, половину оставил
                buffer.push_back(curWeight / 2);
            }
        }
        else
        {
            // больше взять фруктов не может
            while(buffer.size() > 0) {
                fruitsHeap.insert(buffer.back());
                buffer.pop_back();
            }
            totalWeight = 0;
            steps++;
        }

        // фрукты в корзине закончились
        if(fruitsHeap.getSize() == 0 && buffer.size() == 0){
            steps++;
            break;
        }
    }

    return steps;
}

int main() {
    int fruitsCount = 0; // количество фруктов
    std::cin >> fruitsCount;

    // сохраняем фрукты
    int *fruits = new int[fruitsCount];
    for(size_t i = 0; i < fruitsCount; i++) {
        std::cin >> fruits[i];
    }

    int maxWeight = 0; // "грузоподъемность" парня
    std::cin >> maxWeight;

    // считаем кол-во шагов для поедания фруктов
    int steps = countEatingSteps(fruits, 0, fruitsCount, maxWeight);

    std::cout << steps << std::endl;

    delete[] fruits;

    return 0;
}

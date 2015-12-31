/**
Прямоугольники.  
Дана последовательность N прямоугольников различной ширины и высоты (wi,hi). Прямоугольники
расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо). Требуется найти M ­
площадь максимального прямоугольника (параллельного осям координат), который можно вырезать из этой
фигуры.

Время работы ­ O(n).

Формат входных данных. В первой строке задано число N (1 ≤ N ≤ 10000). Далее идет N строк. В каждой
строке содержится два числа width и height: ширина и высота i­го прямоугольника. (0 ≤ width ≤ 10000,
0 ≤ height ≤ 10000)

Формат выходных данных. вывести число M. (0 ≤ M ≤ 10 9 ). 
*/

#include <iostream>
using namespace std;

// прямоугольник
class Rectangle {
public:
    Rectangle(int w = 0, int h = 0) : _width(w), _height(h) {
    }

    // получение ширины
    int getWidth() {
        return _width;
    }

    // получение высоты
    int getHeight() {
        return _height;
    }

    // задание ширины
    void setWidth(int w) {
        _width = w;
    }

    // добавление ширины
    void growWidth(int addw) {
        _width += addw;
    }

    // задание высоты
    void setHeight(int h) {
        _height = h;
    }

    // площадь прямоугольника
    int getArea() {
        return _width * _height;
    }

    // оператор присваивания
    Rectangle &operator = (const Rectangle &r) {
        if(&r == this) return *this;
        _width = r._width;
        _height = r._height;
        return *this;
    }

    // оператор вывода в поток
    friend ostream &operator << (ostream &stream, Rectangle &r);

protected:
    int _width; // ширина
    int _height; // высота
};

ostream &operator << (ostream &stream, Rectangle &r) {
    return stream <<  r.getWidth() << "x" << r.getHeight();
}

// стек прямоугольников
template <class T>
class Stack {
public:
    Stack() : _data(NULL), _memorySize(0), _elements(0) {
    }

    // увеличение кол-ва памяти
    void growSize() {
        int newMemorySize = _memorySize > 0 ? _memorySize * 2 : 5;
        T *newData = new T[newMemorySize];

        if(_elements > 0) {
            for(size_t i = 0; i < _elements; i++) {
                newData[i] = _data[i];
            }
        }

        _data = newData;
        _memorySize = newMemorySize;
    }

    // получение элемента с вершины
    // remove = удалить элемент из стека?
    T &pop(bool remove = true) {
        if(remove) {
            return _data[(_elements--) - 1];
        }
        return _data[_elements - 1];
    }

    // получение элемента с вершины (без удаления)
    T &peek() {
        return pop(false);
    }

    // добавление прямоугольника в стек
    void push(T rect) {
        if(_memorySize == _elements) {
            growSize();
        }
        _data[_elements] = rect;
        _elements++;
    }

    // пустой стек?
    bool isEmpty() {
        return _elements == 0;
    }

    // вывод стека на печать [для отладки only]
    void show() {
        cout << "{{{{\n";
        for(size_t i = 0; i < _elements; i++) {
            cout << "[" << i  << "] => " << _data[i] << endl;
        }
        cout << "}}}}\n";
    }

    // деструктор
    ~Stack() {
        delete[] _data;
    }

protected:
    T *_data;
    size_t _memorySize; // кол-во выделенной памяти
    size_t _elements; // кол-во элементов
};

// определение максимально возможной площади прямоугольника (по условию)
int getMaxSquare(Rectangle *rectangles, size_t count) {
    Stack<Rectangle> stack;
    stack.push(rectangles[0]);

    int max = rectangles[0].getArea();
    // cout << max << endl;

    for(size_t i = 1; i < count; i++) {
        // cout << rectangles[i].getWidth() << " "
        // << rectangles[i].getHeight() << endl;

        Rectangle *lastRect = &stack.peek(), // последний прямоугольник в стеке
                  *curRect = &rectangles[i]; // текущий прямоугольник

        if(curRect->getHeight() >= lastRect->getHeight()) {
            // текущий прямоугольник выше, добавляем его в стек
            stack.push(*curRect);
        }
        else
        {
            // текущий прямоугольник ниже предыдущих
            int newHeight = lastRect->getHeight();

            while(newHeight > curRect->getHeight()) { // пока не встретим прямоугольник ниже или такой же по высоте
                lastRect = &stack.pop();

                if(lastRect->getArea() > max) {
                    // найден прямоугольник с большей площадью
                    max = lastRect->getArea();
                }

                if(stack.isEmpty()) {
                    // больше прямоугольников нет
                    // проверяем прямоугольник, сложенный с последним по высоте как текущий
                    newHeight = curRect->getHeight();
                    Rectangle r1(lastRect->getWidth() + curRect->getWidth(), (newHeight = curRect->getHeight()));
                    stack.push(r1);
                }
                else
                {
                    // складываем с предыдущим прямоугольником
                    stack.peek().growWidth(lastRect->getWidth());

                    int nextHeight = stack.peek().getHeight();
                    if(nextHeight > curRect->getHeight()) {
                        // предпредыдущий выше текущего
                        newHeight = nextHeight;
                    }
                    else if(nextHeight == curRect->getHeight()) {
                        // предпредыдущий такой же, как текущий
                        stack.peek().growWidth(curRect->getWidth());
                        newHeight = curRect->getHeight();
                    }
                    else
                    {
                        // предпредыдущий ниже, чем текущий
                        newHeight = curRect->getHeight();
                        Rectangle r2(lastRect->getWidth() + curRect->getWidth(), (newHeight = curRect->getHeight()));
                        stack.push(r2);
                    }
                }
            }
        }
    }

    return max;
}

int main() {
    // кол-во прямоугольников
    size_t rectanglesCount = 0;
    cin >> rectanglesCount;
    rectanglesCount++; // в конце добавим еще один прмоугольник 0x0

    Rectangle *rectangles = new Rectangle[rectanglesCount];

    // ввод ширин и высот прямоугольников
    for(size_t i = 0; i < rectanglesCount - 1; i++) {
        int w = 0, h = 0;
        cin >> w >> h;
        // создание прямоугольников
        rectangles[i].setWidth(w);
        rectangles[i].setHeight(h);
    }
    rectangles[rectanglesCount - 1].setWidth(0);

    cout << getMaxSquare(rectangles, rectanglesCount);

    // очистка памяти
    delete[] rectangles;

    return 0;
}

/**
Ломаная 1.  
Задано N точек на плоскости. Указать (N­1)­звенную несамопересекающуюся незамкнутую ломаную, проходящую через все эти точки.
Указание: стройте ломаную в порядке возрастания x­координаты. Если имеются две точки с одинаковой x­координатой, то расположите раньше ту точку, у которой y­координата меньше.
*/

#include <iostream>
#include <vector>
#include <assert.h>
#include <cstring>

// структура Точка
struct Point {
    int x;
    int y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

// сравнение точек сначала по x, потом по y 
bool operator < (const Point &p1, const Point &p2) {
    return (p1.x == p2.x) ? p1.y < p2.y : p1.x < p2.x;
}

// сравнение с помощью оператора <
template <class T>
bool isLess(const T &obj1, const T &obj2) {
    return obj1 < obj2;
}

// сама сортировка
template<class T>
void mySort(T *data, size_t left, size_t right, bool (*isLess)(const T &, const T &)) {
    for(int i = left + 1; i < right; i++) { // с [1] элемента
        T elem = data[i]; // сохраняем текущий элемент
        int j = i - 1;
        while(j >= 0 && isLess(elem, data[j])) {
            // ищем позицию для вставки текущего элемента
            j--;
        }
        // j + 1 => позиция для вставки текущего элемента
        if(i - j > 1) {
            std::memmove(&data[j+2], &data[j+1], sizeof(T) * (i - j - 1));
        }
        data[j + 1] = elem;
    }
}

int main() {
    // кол-во точек
    int n = 0;
    std::cin >> n;
    assert(n > 0);

    // вектор точек
    std::vector<Point> points;
    points.reserve(n);
    Point point;

    // ввод точек
    while(std::cin >> point.x >> point.y && points.size() < n) {
        points.push_back(point);
    }

    // сортировка точек
    mySort(&points[0], 0, points.size(), isLess);

    // вывод отсортированных точек
    for(size_t i = 0; i < points.size(); i++) {
        std::cout << points[i].x << " " << points[i].y << std::endl;
    }

    return 0;
}

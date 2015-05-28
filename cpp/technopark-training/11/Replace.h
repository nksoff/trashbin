#include <iostream>
using namespace std;

/****************************************************************************************/
/**
 * Перегрузка оператора вывода для элемента коллекции (multi)map
 */
template <class keyClass, class valClass>
ostream &operator << (ostream &stream, pair<keyClass,valClass> p) {
    stream << p.first << " => " << p.second << endl;
    return stream;
}

/**
 * Перегруженная функция для получения значения итератора коллекции
 * не важно: из пары (элемент коллекции map) или просто значение
 */
template <class keyClass, class valClass>
valClass& getVal(pair<keyClass, valClass> &p) {
    return p.second;
}
template <class valClass>
valClass& getVal(valClass &p) {
    return p;
}

/**
 * Вывод всех элементов коллекции
 */
template <class iteratorClass>
void show(iteratorClass _begin, iteratorClass _end, const char *name = "") {
    cout << endl << "{{{{---- " << name << " [" << distance(_begin, _end) << "] ----" << endl;
    for(iteratorClass i = _begin; i != _end; i++) {
        cout << " " << *i;
    }
    cout << endl << "---- " << name << " ----}}}}" << endl << endl;
}

/****************************************************************************************/

/**
 * Функтор - меньше чем
 */
template <class valClass>
class LessThan : public unary_function<valClass, bool> {
public:
    LessThan(valClass compareVal = 10) : _compareVal(compareVal) {}
    bool operator ()(valClass val) const {
        return val < _compareVal;
    }
private:
    valClass _compareVal;
};

/**
 * Функтор - больше чем
 */
template <class valClass>
class MoreThan : public unary_function<valClass, bool> {
public:
    MoreThan(valClass compareVal = 10) : _compareVal(compareVal) {}
    bool operator ()(valClass val) const {
        return val > _compareVal;
    }
private:
    valClass _compareVal;
};


/**
 * Функция обработки коллекции
 * Заменяются все элементы, удовлетворяющие предикату, на replaceWith (по умолчанию 0)
 */
template<class valClass, class iteratorClass, class predicatClass>
int f(iteratorClass _begin, iteratorClass _end, predicatClass &predicat, valClass replaceWith = 0) {
    int count = 0;
    for(iteratorClass i = _begin; i != _end; i++) {
        if(predicat(getVal(*i))) {
            getVal(*i) = replaceWith;
            count++;
        }
    }
    return count;
}
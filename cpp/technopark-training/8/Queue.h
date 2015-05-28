#include <iostream>
using namespace std;

#ifndef CLASS_QUEUE
#define CLASS_QUEUE

template <class T>
class Queue {
private:
    T **_elements;
    int _countMax;
    int _count;
public:
    Queue() :
        _elements(NULL),
        _countMax(10),
        _count(0) {
        reinitMemory();
    }
    Queue(const Queue &obj) :
        _elements(NULL),
        _countMax(obj._countMax),
        _count(obj._count) {
        _elements = new T*[_countMax];
        for(int i = 0; i < _count; i++) {
            _elements[i] = copyElement(obj._elements[i]);
        }
    }
    ~Queue() {
        if(_elements) {
            for(int i = 0; i < _count; i++) {
                delete _elements[i];
            }
            delete[] _elements;
        }
    }

    int getCount() const {
        return _count;
    }

    void push(T obj) {
        if(_count == _countMax) {
            reinitMemory();
        }
        _elements[_count++] = copyElement(obj);
    }

    T pop(int n = 0) { // n = 0, 1, 2, 3, ...
        if(n <= _count && n >= 0) {
            T val = *copyElement(_elements[n]);
            delete _elements[n];
            for(int i = n; i < _count-1; i++) {
                _elements[i] = _elements[i+1];
            }
            _count--;
            return val;
        }
        return 0;
    }

    void show(ostream &stream = cout) const {
        for(int i = 0; i < _count; i++) {
            stream << "[" << (i+1) << "] = " <<  *(_elements[i]) << endl;
        }
        if(_count == 0) {
            cout << "[queue is empty]" << endl;
        }
        stream << endl;
    }

    Queue<T> operator =(Queue<T> &q) {
        ~Queue();
        reinitMemory(q._countMax);
        for(int i = 0; i < q._count; i++) {
            _elements[i] = copyElement(q._elements[i]);
        }
    }

    Queue<T> operator +(Queue<T> &q) {
        Queue<T> newQ = *this;
        reinitMemory(_countMax + q._countMax);
        for(int i = 0; i < q._count; i++) {
            newQ.push(*copyElement(q._elements[i]));
        }
        return newQ;
    }

    Queue<T> operator -(Queue<T> &q) {
        Queue<T> newQ = *this;
        for(int i = 0; i < q._count; i++) {
            for(int j = 0; j < newQ._count; j++) {
                if(*(newQ._elements[j]) == *(q._elements[i])) {
                    newQ.pop(j);
                    j--;
                }
            }
        }
        return newQ;
    }

    friend ostream& operator <<(ostream &stream, Queue<T> &obj) {
        obj.show(stream);
        return stream;
    }

protected:
    virtual T* copyElement(T &obj) {
        return new T(obj);
    }
    
    T* copyElement(T *obj) {
        return copyElement(*obj);
    }

private:
    void reinitMemory(int newCountMax = 0) {
        _countMax = (newCountMax > 0) ? newCountMax : _countMax*2;
        T **newMemory = new T*[_countMax];
        for(int i = 0; i < _count; i++) {
            newMemory[i] = _elements[i];
        }
        if(_elements) delete[] _elements;
        _elements = newMemory;
    }

};

template <class T>
void removeByTwo(Queue<T> &obj, bool odd = true) { // odd - нечет
    int from = (odd) ? 0 : 1, to = obj.getCount(), removed = 0;
    for(int i = from; i < to; i+=2) {
        obj.pop(i - (removed++));
    }
}

#endif
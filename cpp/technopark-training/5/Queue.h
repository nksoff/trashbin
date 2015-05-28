#include <iostream>
using namespace std;

#ifndef CLASS_QUEUE
#define CLASS_QUEUE

class Queue {
private:
    int *_numbers;
    int _countMax;
    int _count;
public:
    Queue() :
        _numbers(NULL),
        _countMax(10),
        _count(0) {
        reinitMemory();
    }
    Queue(const Queue &obj) :
        _numbers(NULL),
        _countMax(obj._countMax),
        _count(obj._count) {
        _numbers = new int[_countMax];
        for(int i = 0; i < _count; i++) {
            _numbers[i] = obj._numbers[i];
        }
    }
    ~Queue() {
        if(_numbers) delete[] _numbers;
    }

    int getCount() const {
        return _count;
    }

    void push(int n) {
        if(_count == _countMax) {
            reinitMemory();
        }
        _numbers[_count++] = n;
    }

    int pop(int n = 0) { // n = 0, 1, 2, 3, ...
        if(n <= _count && n >= 0) {
            int val = _numbers[n];
            for(int i = n; i < _count-1; i++) {
                _numbers[i] = _numbers[i+1];
            }
            _count--;
            return val;
        }
        return 0;
    }

    void show() const {
        for(int i = 0; i < _count; i++) {
            cout << "[" << (i+1) << "] = " <<  _numbers[i] << endl;
        }
        cout << endl;
    }

private:
    void reinitMemory() {
        _countMax *= 2;
        int *newMemory = new int[_countMax];
        for(int i = 0; i < _count; i++) {
            newMemory[i] = _numbers[i];
        }
        if(_numbers) delete[] _numbers;
        _numbers = newMemory;
    }
};

#endif
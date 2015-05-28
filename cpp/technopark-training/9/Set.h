#include <iostream>
#include "Sort.h"
using namespace std;

#ifndef CLASS_SET
#define CLASS_SET

namespace intSet {
    class Set {
    public:
        Set() :
            _numbers(NULL),
            _count(0),
            _countMax(5) {
            _initMemory();
        }
        Set(int *numbers, int size) :
            _numbers(NULL),
            _count(0),
            _countMax(size) {

            _initMemory();
            for(int i = 0; i < size; i++) {
                add(numbers[i]);
            }
        }
        Set(const Set &obj):
            _numbers(NULL),
            _count(0),
            _countMax(obj._count) {
            *this = obj;
        }

        ~Set() {
            if(_numbers) delete[] _numbers;
        }

        void show(ostream& = cout) const;

        int length() const;
        int count(int) const;
        bool contains(int) const;

        void add(int);

        void remove(int n, int total = 0);
        void removeByKey(int key);
        void clear();

        Set& operator = (const Set &obj);
        Set& operator + (const Set &obj) const;
        Set& operator - (const Set &obj) const;
        Set& operator * (const Set &obj) const;

        int operator [] (int key) const;

        friend ostream& operator << (ostream &stream, Set &obj);
    private:
        int *_numbers;
        int _count;
        int _countMax;

        void _initMemory(int = 0);
        void _sort();
    };

    Set& uniqueElements(const Set&, const Set&);
}
#endif
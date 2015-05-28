#include "Set.h"
#include <iostream>

using namespace std;
using namespace sort;

namespace intSet {
    void Set::show(ostream &stream) const {
        stream << "----set"
            << " [" << _count << "]" << endl;
        for(int i = 0; i < _count; i++) {
            stream << _numbers[i] << " ";
        }
        stream << endl << "----" << endl;
        stream << endl;
    }

    int Set::length() const {
        return _count;
    }

    bool Set::contains(int n) const {
        for(int i = 0; i < _count; i++) {
            if(_numbers[i] == n) {
                return true;
            }
        }
        return false;
    }

    int Set::count(int n) const {
        int count = 0;
        for(int i = 0; i < _count; i++) {
            if(_numbers[i] == n) {
                count++;
            }
        }
        return count;
    }

    void Set::add(int n) {
        if(_count >= _countMax) {
            _initMemory();
        }
        _numbers[_count++] = n;
        _sort();
    }

    void Set::remove(int n, int total) {
        int count = 0;
        for(int i = _count - 1; i >= 0; i--) {
            if(_numbers[i] == n) {
                removeByKey(i);
                count++;
                if(total > 0 && count >= total) return;
            }
        }
    }

    void Set::removeByKey(int key) {
        if(key >= 0 && key < _count) {
            for(int i = key+1; i < _count; i++) {
                _numbers[i-1] = _numbers[i];
            }
            _count--;
        }
    }

    void Set::clear() {
        _count = 0;
    }

    Set& Set::operator = (const Set &obj) {
        if(_numbers) delete[] _numbers;
        _numbers = NULL;
        _count = 0;
        _initMemory(obj._countMax);

        for(int i = 0; i < obj._count; i++) {
            add(obj._numbers[i]);
        }
        _sort();
        return *this;
    }

    Set& Set::operator + (const Set &obj) const {
        Set *set = new Set(*this);
        for(int i = 0; i < obj._count; i++) {
            set->add(obj[i]);
        }
        return *set;
    }

    Set& Set::operator - (const Set &obj) const {
        Set *set = new Set(*this);
        for(int i = 0; i < obj._count; i++) {
            set->remove(obj[i], 1);
        }
        return *set;
    }

    Set& Set::operator * (const Set &obj) const {
        Set *set = new Set(*this);
        for(int i = 0; i < _count; i++) {
            if(!obj.contains(_numbers[i])) {
                set->remove(_numbers[i], 1);
            }
            else if(set->count(_numbers[i]) > obj.count(_numbers[i])) {
                int diff = set->count(_numbers[i]) - obj.count(_numbers[i]);
                for(int j = 0; j < diff; j++) {
                    set->remove(_numbers[i], 1);
                }
            }
        }

        return *set;
    }

    int Set::operator [] (int key) const {
        if(key >= 0 && key < _count) {
            return _numbers[key];
        }
        return 0;
    }

    ostream& operator << (ostream &stream, Set &obj) {
        obj.show(stream);
        return stream;
    }

    void Set::_initMemory(int newCountMax) {
        _countMax = (newCountMax > 0) ? newCountMax : _countMax*2;
        int *newMemory = new int[_countMax];
        for(int i = 0; i < _count; i++) {
            newMemory[i] = _numbers[i];
        }
        if(_numbers) delete[] _numbers;
        _numbers = newMemory;
    }

    void Set::_sort() {
        quickSort(_numbers, 0, _count - 1);
    }

    Set& uniqueElements(const Set &set1, const Set &set2) {
        return (set1 - set2) + (set2 - set1);
    }
}
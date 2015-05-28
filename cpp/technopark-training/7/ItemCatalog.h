#include <iostream>
#include "Item.h"
#include "Book.h"
#include "Magazine.h"
using namespace std;

#ifndef CLASS_ITEM_CATALOG
#define CLASS_ITEM_CATALOG

class ItemCatalog {
private:
    Item **_collection;
    int _count;
    int _countMax;
public:
    ItemCatalog() :
        _collection(NULL),
        _count(0),
        _countMax(10) {
        reinitMemory();
    }

    ItemCatalog(const ItemCatalog &obj) :
        _collection(NULL),
        _count(obj._count),
        _countMax(obj._countMax) {
        _collection = new Item*[_countMax];
        for(int i = 0; i < _count; i++) {
            _collection[i] = obj._collection[i];
        }
    }

    ~ItemCatalog() {
        delete[] _collection;
    }

    int getCount() const {
        return _count;
    }

    void add(Item *item) {
        if(_count == _countMax) {
            reinitMemory();
        }
        _collection[_count++] = item;
    }

    Item* get(int n = 0) {
        if(n < _count && n >= 0) {
            return _collection[n];
        }
        return NULL;
    }

    Item* operator [](int n) {
        return get(n);
    }

    void show(int mode = 0) { // 0 = all, 1 = available, 2 = unavailable
        for(int i = 0; i < _count; i++) {
            if( (mode == 1 && !_collection[i]->isAvailable())
            ||  (mode == 2 && _collection[i]->isAvailable())) {
                continue;
            }
            cout << "[" << (i) << "] ";
            _collection[i]->show();
        }
    }

private:
    void reinitMemory() {
        _countMax *= 2;
        Item **newMemory = new Item*[_countMax];
        for(int i = 0; i < _count; i++) {
            newMemory[i] = _collection[i];
        }
        if(_collection) delete[] _collection;
        _collection = newMemory;
    }
};

#endif
#include <iostream>
#include "IObject.h"
using namespace std;

#ifndef CLASS_INTOBJECT
#define CLASS_INTOBJECT

class IntObject: public IObject {
private:
    int _val;

public:
    IntObject() : _val(0) {}
    IntObject(int val): _val(val) {}
    IntObject(const IntObject &obj): _val(obj._val) {}
    bool less(IObject *_obj) {
        return _val < dynamic_cast<IntObject*>(_obj)->_val;
    }
    bool equal(IObject *_obj) {
        return _val == dynamic_cast<IntObject*>(_obj)->_val;
    }
    IObject *clone() {
        return new IntObject(_val);
    }
    void show() {
        cout << _val;
    }
};

#endif
#include <iostream>
#include "IObject.h"
#include <string>
using namespace std;

#ifndef CLASS_STRINGOBJECT
#define CLASS_STRINGOBJECT

class StringObject: public IObject {
private:
    char *_val;

public:
    StringObject() {
        _val = new char[1];
        _val[0] = '\0';
    }
    StringObject(char *val) {
        _val = new char[strlen(val) + 1];
        strcpy(_val, val);
    }
    StringObject(const StringObject &obj) {
        _val = new char[strlen(obj._val) + 1];
        strcpy(_val, obj._val);
    }
    ~StringObject() {
        if(_val) delete[] _val;
    }
    bool less(IObject *_obj) {
        return strcmp(_val,
            dynamic_cast<StringObject*>(_obj)->_val) < 0;
    }
    bool equal(IObject *_obj) {
        return strcmp(_val,
            dynamic_cast<StringObject*>(_obj)->_val) == 0;
    }
    IObject *clone() {
        return new StringObject(_val);
    }
    void show() {
        cout << _val;
    }
};

#endif
#include <iostream>
using namespace std;

#ifndef CLASS_IOBJECT
#define CLASS_IOBJECT

class IObject {
public:
    virtual bool less(IObject *) = 0;
    virtual bool equal(IObject *) = 0;
    virtual IObject *clone() = 0;
    virtual void show() = 0;
};

#endif
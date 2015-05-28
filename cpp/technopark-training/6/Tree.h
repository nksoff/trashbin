#include <iostream>
#include "IObject.h"
using namespace std;

#ifndef CLASS_TREE
#define CLASS_TREE

class Tree {
private:
    IObject *_data;
    Tree *_left, *_right;

    const static bool showNULL = !true;

public:
    Tree() : _data(NULL), _left(NULL), _right(NULL) {}
    Tree(IObject *obj) : _data(NULL), _left(NULL), _right(NULL) {
        _data = obj->clone();
    }
    Tree(const Tree &obj) {
        if(obj._data != NULL) {
            _data = obj._data->clone(); 
        }
        
        if(obj._left != NULL) {
            _left = new Tree(*obj._left);
        }
        if(obj._right != NULL) {
            _right = new Tree(*obj._right);
        }
    }

    void setData(IObject *obj) {
        _data = obj->clone();
    }

    void add(IObject *obj) {
        return add(new Tree(obj->clone()));
    }

    void add(Tree *tree) {
        if(tree->_data->less(_data)) {
            if(_left == NULL) {
                _left = tree;
            }
            else {
                return _left->add(tree);
            }
        }
        else
        {
            if(_right == NULL) {
                _right = tree;
            }
            else {
                return _right->add(tree);
            }
        }
    }

    void remove(IObject *obj) {
        if(_left != NULL && obj->equal(_left->_data)) {
            Tree *left = _left->_left;
            Tree *right = _left->_right;

            delete _left;
            _left = NULL;
            if(left != NULL) {
                add(left);
            }
            if(right != NULL) {
                add(right);
            }
        }
        else if(_right != NULL && obj->equal(_right->_data)) {
            Tree *left = _right->_left;
            Tree *right = _right->_right;

            delete _right;
            _right = NULL;
            if(left != NULL) {
                add(left);
            }
            if(right != NULL) {
                add(right);
            }
        }
        else if(_left != NULL && obj->less(_data)) {
            _left->remove(obj);
        }
        else if(_right != NULL) {
            _right->remove(obj);
        }
    }

    IObject *search(IObject *obj) {
        if(obj->equal(_data)) {
            return _data;
        }
        else if(_left != NULL && obj->less(_data)) {
            return _left->search(obj);
        }
        else if(_right != NULL) {
            return _right->search(obj);
        }

        return NULL;
    }

    void show(int indent = 0) {
        for(int i = 0; i < indent; i++) {
            cout << "   ";
        }
        cout << "├--";
        if(_left != NULL || _right != NULL) {
            cout << "┬";
        }
        cout << " ";

        if(_data != NULL) _data->show();
        cout << endl;
        if(_left != NULL) {
            _left->show(indent+1);
        }
        else if(showNULL)
        {
            for(int i = 0; i < indent + 1; i++) {
                cout << "   ";
            }
            cout << "├-- left NULL" << endl;
        }

        if(_right != NULL) {
            _right->show(indent+1);
        }
        else if(showNULL)
        {
            for(int i = 0; i < indent+1; i++) {
                cout << "   ";
            }
            cout << "├-- right NULL" << endl;
        }

        if(indent == 0) cout << endl;
    }
};

#endif
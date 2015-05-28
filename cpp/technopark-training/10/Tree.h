#include <iostream>
#include <fstream>
#include <string>
#include "Debug.h"
using namespace std;

#ifndef CLASS_TREE
#define CLASS_TREE

template <class ElemClass>
class Tree {
public:
    class Error : public exception {
    public:
        Error(const char *err) {
            if(err) {
                _err = new char[strlen(err) + 1];
                strcpy(_err, err);
            }
        }
        ~Error() throw() {
            if(_err) delete[] _err;
        }
        virtual const char *what() const throw() { return _err; }
    protected:
        char *_err;
    };

    Tree(ElemClass elem) : _data(NULL), _left(NULL), _right(NULL) {
        debug(1, "%s", "[Tree] constructor (element)");
        setData(elem);
        debug(1, "%s", "[/Tree] constructor (element)");
    }
    Tree(const char *file) : _data(NULL), _left(NULL), _right(NULL) {
        debug(1, "%s", "[Tree] constructor (file)");
        initFromFile(file);
        debug(1, "%s", "[/Tree] constructor (file)");
    }
    Tree(ElemClass *elements, int count) : _data(NULL), _left(NULL), _right(NULL) {
        debug(1, "%s", "[Tree] constructor (array)");
        for(int i = 0; i < count; i++)
            add(elements[i]);
        debug(1, "%s", "[/Tree] constructor (array)");
    }
    Tree(const Tree<ElemClass> &obj) : _data(NULL), _left(NULL), _right(NULL) {
        debug(1, "%s", "[Tree] constructor (copy)");
        if(obj._data)
            add(*(obj._data));
        add(obj._left);
        add(obj._right);
        debug(1, "%s", "[/Tree] constructor (copy)");
    }
    ~Tree() {
        debug(1, "%s", "[Tree] destructor");
        clearData();
        if(_left)
            delete _left;
        if(_right)
            delete _right;
        debug(1, "%s", "[/Tree] destructor");
    }

    void initFromFile(const char *fileName) throw(Error) {
        fstream f(fileName);
        if(!f) {
            debug(1, "%s %s", "[Tree] error: cannot open file to init ", fileName);
            throw Error("Couldn't open file to init Tree");
        }
        while(!f.eof()) {
            ElemClass num;
            f >> num;
            add(num);
        }

        f.close();
    }

    ElemClass getData() const throw(Error) {
        if(_data) {
            return *_data;
        }
        debug(1, "%s", "[Tree] error: cannot get data of current tree");
        throw Error("Couldn't receive data of current tree");
    }

    void setData(ElemClass elem) {
        if(_data)
            delete _data;
        _data = new ElemClass(elem);
    }

    void clearData() {
        if(_data)
            delete _data;
        _data = NULL;
    }

    void add(ElemClass elem) {
        debug(1, "%s %d", "[Tree] add element", elem);
        if(!_data) {
            debug(1, "%s", "-> set current data");
            setData(elem);
            return;
        }
        if(elem < *(_data)) {
            debug(1, "%s", "-> go to left");
            if(!_left)
                _left = new Tree<ElemClass>(elem);
            else
                _left->add(elem);
        }
        else
        {
            debug(1, "%s", "-> go to right");
            if(!_right)
                _right = new Tree<ElemClass>(elem);
            else
                _right->add(elem);
        }
        debug(1, "%s %d", "[/Tree] add element", elem);
    }

    void add(Tree<ElemClass> *tree) {
        if(!tree) return;
        debug(1, "%s", "[Tree] add tree");

        if(tree->_data)
            add(*(tree->_data));

        if(tree->_left)
            add(tree->_left);
        if(tree->_right)
            add(tree->_right);
        debug(1, "%s", "[/Tree] add tree");
    }

    void remove(ElemClass elem) {
        debug(1, "%s %d", "[Tree] remove element ", elem);
        Tree<ElemClass> *left = _left, *right = _right;
        if(left && left->_data && elem == *(left->_data)) {
            debug(1, "%s", "-> remove left branch");
            left->clearData();
            _left = NULL;
            add(left);

            delete left;
        }
        else if(right && right->_data && elem == *(right->_data)) {
            debug(1, "%s", "-> remove right branch");
            right->clearData();
            _right = NULL;
            add(right);

            delete right;
        }
        else if(_data && elem < *(_data) && left) {
            debug(1, "%s", "-> go to left");
            left->remove(elem);
        }
        else if(_data && elem > *(_data) && right) {
            debug(1, "%s", "-> go to right");
            right->remove(elem);
        }
        else if(_data && elem == *(_data)) {
            debug(1, "%s", "-> remove current element");
            clearData();
            _left = _right = NULL;
            add(left);
            add(right);
            delete left;
            delete right;
        }
        debug(1, "%s %d", "[/Tree] remove element", elem);
    }

    void remove(Tree<ElemClass> *tree) {
        debug(1, "%s", "[Tree] remove tree");
        if(tree->_data != NULL) {
            remove(*(tree->_data));
        }
        if(tree->_left != NULL) {
            remove(tree->_left);
        }
        if(tree->_right != NULL) {
            remove(tree->_right);
        }
        debug(1, "%s", "[/Tree] remove tree");
    }

    Tree<ElemClass> *search(ElemClass elem) {
        debug(1, "%s %d", "[Tree] search for ", elem);
        if(_data) {
            if(elem == *(_data)) {
                return this;
            }
            else if(elem < *(_data) && _left) {
                return _left->search(elem);
            }
            else if(_right) {
                return _right->search(elem);
            }
        }
        debug(1, "%s %d", "[/Tree] search for ", elem);
        return NULL;
    }

    void show(ostream &stream = cout) {
        static int listingLevel = 0;
        static bool listingLast[100] = {};

        int level = listingLevel;

        listingLast[level] = !_left && !_right;

        for(int i = 1; i < level; i++) {
            stream << (!listingLast[i-1] ? "|" : " ") << "  ";
        }

        if(level > 0) stream << (!listingLast[level-1] ? "├" : "└") << "──";
        stream << (_left || _right ? "┬" : "─") << " ";

        if(_data)
            stream << *(_data);
        else
            stream << "[empty]";
        stream << endl;

        if(_left) {
            listingLevel = level + 1;
            listingLast[level] = !_right;
            _left->show(stream);
        }
        if(_right) {
            listingLevel = level + 1;
            listingLast[level] = true;
            _right->show(stream);
        }

        if(level == 0) {
            stream << endl;
            listingLevel = 0;
        }
    }

    void showSorted(ostream &stream = cout, bool reverse = false) {
        Tree<ElemClass> *first = _left, *second = _right;
        if(reverse) {
            first = _right;
            second = _left;
        }

        if(first)
            first->showSorted(stream, reverse);
        if(_data)
            stream << *_data << " ";
        if(second)
            second->showSorted(stream, reverse);
    }

    void showLeaves(ostream &stream = cout, bool reverse = false) {
        Tree<ElemClass> *first = _left, *second = _right;
        if(reverse) {
            first = _right;
            second = _left;
        }

        if(first)
            first->showLeaves(stream, reverse);
        if(_data && !first && !second)
            stream << *_data << " ";
        if(second)
            second->showLeaves(stream, reverse);
    }

    Tree<ElemClass> operator + (Tree<ElemClass> &tree) {
        debug(1, "%s", "[Tree] + Tree");
        Tree<ElemClass> newTree(*this);
        newTree.add(&tree);
        debug(1, "%s", "[/Tree] + Tree");
        return newTree;
    }
    Tree<ElemClass> operator - (Tree<ElemClass> &tree) {
        debug(1, "%s", "[Tree] - Tree");
        Tree<ElemClass> newTree(*this);
        newTree.remove(&tree);
        debug(1, "%s", "[/Tree] - Tree");
        return newTree;
    }

    friend ostream& operator << (ostream &stream, Tree<ElemClass> &tree) {
        tree.show(stream);
        return stream;
    }
protected:
private:
    ElemClass* _data;
    Tree<ElemClass> *_left;
    Tree<ElemClass> *_right;
};

#endif
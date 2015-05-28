#include <iostream>
#include "Tree.h"
#include "IntObject.h"
#include "StringObject.h"
using namespace std;

int main() {
    cout << (23%17+1) << " variant" << endl;

    FILE *integers = fopen("integers.txt", "r");
    int integer;
    bool head = true;

    Tree *tree = new Tree;
    while(fscanf(integers, "%d", &integer) == 1) {
        IntObject iobj(integer);
        if(head) {
            tree->setData(&iobj);
            head = false;
            continue;
        }
        tree->add(&iobj);
    }
    fclose(integers);

    FILE *strings = fopen("strings.txt", "r");
    char str[100];
    head = true;
    Tree *tree1 = new Tree;
    while(fscanf(strings, "%s", str) == 1) {
        StringObject sobj(str);
        if(head) {
            tree1->setData(&sobj);
            head = false;
            continue;
        }
        tree1->add(&sobj);
    }
    fclose(strings);

    while(true) {
        cout << "integers: " << endl;
        tree->show();
        cout << endl << endl;
        cout << "strings: " << endl;
        tree1->show();
        cout << endl << endl;

        cout << "Menu:" << endl;
        cout << "1. + integer" << endl
        << "2. - integer" << endl
        << "3. + string" << endl
        << "4. - string" << endl
        << "0. exit" << endl << endl;
        cout << ">>> ";
        int mode;
        cin >> mode;

        if(mode == 0) {
            break;
        }

        int num;
        char word[100];
        switch(mode) {
            case 1:
                cout << "+ ";
                cin >> num;
                tree->add(new IntObject(num));
            break;
            case 2:
                cout << "- ";
                cin >> num;
                tree->remove(new IntObject(num));
            break;
            case 3:
                cout << "+ ";
                cin >> word;
                tree1->add(new StringObject(word));
            break;
            case 4:
                cout << "- ";
                cin >> word;
                tree1->remove(new StringObject(word));
            break;
        }
    }

    return 0;
}
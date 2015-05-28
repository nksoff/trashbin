#include <iostream>
#include <sstream>
#include "ItemCatalog.h"
#include "Book.h"
#include "Magazine.h"
using namespace std;

int main() {
    ItemCatalog *items = new ItemCatalog;
    for(int i = 0; i < 12; i++) {
        stringstream ss;
        ss << i + 1;
        string s1 = ss.str();
        if(i < 7) {
            items->add(
                new Book(i, (i+1)%3 == 0,
                    string("Book title ") + s1,
                    string("Author name ") + s1,
                    string("Publisher name ") + s1,
                    2008 + i)
                );
        }
        else
        {
            items->add(
                new Magazine(i, (i+1)%2 == 1,
                    string("Magazine"),
                    i-6, i+6, 2015)
                );
        }
    }

    //items->show();

    while(true) {
        cout << "Menu: " << endl
        << "1. list items" << endl
        << "2. list available items" << endl
        << "3. list UNavailable items" << endl
        << "4. borrow (take) item" << endl
        << "5. return (give back) item" << endl
        << "0. exit" << endl << endl;

        cout << ">>> ";
        int mode;
        cin >> mode;

        if(mode == 0) {
            break;
        }
        int itemN;

        switch(mode) {
            case 1: {
                items->show();
                break;
            }
            case 2:
                items->show(1);
                break;
            case 3:
                items->show(2);
                break;
            case 4: {
                cout << ">>> borrow item # ";
                cin >> itemN;
                Item *item = (*items)[itemN];
                if(item == NULL) {
                    cout << "!!! item #" << itemN << " is not found" << endl;
                }
                else if(!item->isAvailable()) {
                    cout << "!!! item # " << itemN << " is not available" << endl;
                }
                else
                {
                    item->take();
                    item->show();
                }
                break;
            }
            case 5: {
                cout << ">>> give back item # ";
                cin >> itemN;
                Item *item = (*items)[itemN];
                if(item == NULL) {
                    cout << "!!! item #" << itemN << " is not found" << endl;
                }
                else if(item->isAvailable()) {
                    cout << "!!! item # " << itemN << " is not borrowed" << endl;
                }
                else
                {
                    item->giveBack();
                    item->show();
                }
                break;
            }
        }
    }
    return 0;
}

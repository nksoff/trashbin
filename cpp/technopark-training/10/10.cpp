#include <iostream>
#define DEBUG 10
#include "Tree.h"

using namespace std;

int main() {
    int numbers1[] = {59, 30, 16, 45, 56, 3, 20, 5, 67, 89, 60},
    numbers2[] = {45, 89, 39, 43, 90, 104, 36, 3};

    Tree <int>  tree1(numbers1, sizeof(numbers1)/sizeof(int)),
    tree2(numbers2, sizeof(numbers2)/sizeof(int));
    cout << tree1 << tree2;

    while(true) {
        cout << endl;
        cout << "1. + to first tree" << endl;
        cout << "2. + to second tree" << endl;
        cout << "3. - from first tree" << endl;
        cout << "4. - from second tree" << endl;
        cout << "5. first + second" << endl;
        cout << "6. first - second" << endl;
        cout << "7. list first sorted (asc)" << endl;
        cout << "8. list second sorted (asc)" << endl;
        cout << "9. list first sorted (desc)" << endl;
        cout << "10. list second sorted (desc)" << endl;
        cout << "11. list first tree leaves (asc)" << endl;
        cout << "12. list second tree leaves (asc)" << endl;
        cout << "13. list first tree leaves (desc)" << endl;
        cout << "14. list second tree leaves (desc)" << endl;
        cout << "15. search by key in first" << endl;
        cout << "16. search by key in second" << endl;
        cout << "17. create new tree from file" << endl;
        cout << "18. try to get data of empty element" << endl;
        cout << "0. exit" << endl;

        cout << ">>>> ";
        int mode;
        cin >> mode;

        if(mode == 0) {
            break;
        }
        cout << endl;

        cout << endl << "1st:" << endl << tree1 << endl << "2nd:" << endl << tree2 << endl;
        bool showEnd = mode > 0 && mode < 5;

        switch(mode) {
            case 1: {
                cout << "Add number to first tree" << endl;
                cout << ">>>> ";
                int num;
                cin >> num;

                tree1.add(num);
                break;
            }
            case 2: {
                cout << "Add number to second tree" << endl;
                cout << ">>>> ";
                int num;
                cin >> num;

                tree2.add(num);
                break;
            }
            case 3: {
                cout << "Remove number from first tree" << endl;
                cout << ">>>> ";
                int num;
                cin >> num;

                tree1.remove(num);
                break;
            }
            case 4: {
                cout << "Remove number from second tree" << endl;
                cout << ">>>> ";
                int num;
                cin >> num;

                tree2.remove(num);
                break;
            }
            case 5: {
                Tree<int> tree3 = (tree1 + tree2);
                cout << tree3;
                break;
            }
            case 6: {
                Tree<int> tree3 = (tree1 - tree2);
                cout << tree3;
                break;
            } 
            case 7: {
                tree1.showSorted(cout);
                break;
            }
            case 8:{
                tree2.showSorted(cout);
                break;
            } 
            case 9: {
                tree1.showSorted(cout, true);
                break;
            }
            case 10: {
                tree2.showSorted(cout, true);
                break;
            }
            case 11: {
                tree1.showLeaves(cout);
                break;
            }
            case 12: {
                tree2.showLeaves(cout);
                break;
            }
            case 13: {
                tree1.showLeaves(cout, true);
                break;
            }
            case 14: {
                tree2.showLeaves(cout, true);
                break;
            }
            case 15: {
                cout << "Search by key in first tree" << endl;
                cout << ">>>> ";
                int num;
                cin >> num;

                Tree<int> *tree3 = tree1.search(num);
                if(tree3)
                    cout << *tree3;
                else
                    cout << "[not found]" << endl;
                break;
            }
            case 16: {
                cout << "Search by key in second tree" << endl;
                cout << ">>>> ";
                int num;
                cin >> num;

                Tree<int> *tree3 = tree2.search(num);
                if(tree3)
                    cout << *tree3;
                else
                    cout << "[not found]" << endl;
                break;
            }
            case 17: {
                cout << "Input filename to init Tree" << endl;
                cout << ">>>> ";
                char file[100];
                cin >> file;

                try {
                    Tree<int> newTree(file);
                    cout << newTree << endl;
                }
                catch(Tree<int>::Error &e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 18: {      
                Tree<int> tree(100);
                tree.clearData();

                try {
                    tree.getData();
                }
                catch(Tree<int>::Error &e) {
                    cout << e.what() << endl;
                }
                break;
            }
        }
        if(showEnd) cout << endl << "1st:" << endl << tree1 << endl << "2nd:" << endl << tree2 << endl;
    }

    return 0;
}
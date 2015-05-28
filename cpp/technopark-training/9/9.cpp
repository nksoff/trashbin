#include <iostream>
#include "Set.h"

using namespace std;
using namespace intSet;

int main() {
    int numbers[] = {4, 7, 1, 3, 3, 0, 8, 10, 3, 0, 5, 15};
    int numbers1[] = {4, 7, 6, 3, 0, 0, 17};

    int size = sizeof(numbers) / sizeof(int);
    int size1 = sizeof(numbers1) / sizeof(int);

    Set s1(numbers, size);
    Set s2(numbers1, size1);

    cout << "#1" << endl << s1
    << "#2" << endl << s2;

    Set s3 = s1+s2;
    cout << "#3 = #1 + #2" << endl << s3;
    Set s4 = s1-s2;
    cout << "#4 = #1 - #2" << endl << s4;
    Set s5 = s1*s2;
    cout << "#5 = #1 * #2" << endl << s5;

    Set s6 = uniqueElements(s1, s2);
    cout << "#6 = (#1 - #2) + (#2 - #1)" << endl << s6;


    return 0;
}
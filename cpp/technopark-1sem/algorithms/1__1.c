/**
Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) максимален, A <= B.
Вывести A и B. Если возможно несколько ответов ­ вывести ответ с минимальным A.
n < 10^7
*/

#include <stdlib.h>
#include <stdio.h>

/**
 * Находит самый маленький делитель числа n
 */
int minDivider(int n) {
    for(int i = 2; i * i < n; i++) { // i: 2 ----> √n
        if(n % i == 0) {
            return i;
        }
    }
    return n;
}

int main() {
    // ввод n
    int n = 0;
    if(scanf("%d", &n) != 1) {
        return 0;
    }

    int minDiv = minDivider(n); // самый маленький делитель
    
    int maxDiv = n - (n/minDiv); // самый большой делитель
    printf("%d %d", n - maxDiv, maxDiv);

    return 0;
}

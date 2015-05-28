#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    struct Node *next;
    struct Node *prev;
};
typedef struct Node* PNode;

int main(int argc, char** argv)
{
    printf("%d variant\n\n", 23%17+1);

    if(argc < 3) {
        printf("[ERROR] expected %d args, %d given \n", 2, argc-1);
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return -1;
    }

    FILE *inputFile, *outputFile;

    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    if(!(inputFile && outputFile)) {
        if(!inputFile) {
            printf("[ERROR] cannot open file %s\n", argv[1]);
        }
        if(!outputFile) {
            printf("[ERROR] cannot open file %s\n", argv[2]);
        }
        return -2;
    }

    printf("---->\n");

    PNode head = NULL, tail = NULL;
    int num;
    while(fscanf(inputFile, "%d", &num) == 1) {
        PNode cur = malloc(sizeof(struct Node));
        cur->val = num;
        cur->prev = tail;
        printf("%d ", cur->val);

        if(tail) {
            tail->next = cur;
        }
        if(!head) {
            head = cur;
        }
        tail = cur;
    }

    printf("\n<----\n");

    PNode last;
    while(tail != NULL) {
        fprintf(outputFile, "%d ", tail->val);
        printf("%d ", tail->val);
        last = tail;
        tail = tail->prev;
        free(last);
    }
    printf("\n");

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
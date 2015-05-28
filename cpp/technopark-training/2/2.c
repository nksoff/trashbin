#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct MatrixVal
{
    int row;
    int column;
    double val;
};
typedef struct MatrixVal* Matrix;

int elements;

double getElem(void *matr, int row, int column) {
    Matrix matrix = (Matrix) matr;
    for(int element = 0; element < elements; element++) {
        if(matrix[element].row == row && matrix[element].column == column) {
            return matrix[element].val;
        }
    }
    return 0;
}

void setElem(void *matr, int row, int column, double newVal) {
    Matrix matrix = (Matrix) matr;
    for(int element = 0; element < elements; element++) {
        if(matrix[element].row == row && matrix[element].column == column) {
            matrix[element].val = newVal;
            return;
        }
        else if(matrix[element].row == 0 && matrix[element].column == 0) {
            matrix[element].row = row;
            matrix[element].column = column;
            matrix[element].val = newVal;
            return;
        }
    }
}

void showMatrix(Matrix matrix) {
    for(int i = 0; i < elements; i++) {
        printf("%d %d %lf\n", matrix[i].row, matrix[i].column, matrix[i].val);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    printf("%d variant\n\n", 23%17+1);

    if(argc < 2) {
        printf("[ERROR] expected %d args, %d given \n", 1, argc-1);
        printf("Usage: %s <word> <file>\n", argv[0]);
        return -1;
    }

    char *path2file = argv[1];
    FILE *file = fopen(path2file, "r");

    if(!file) {
        printf("[ERROR] cannot open file %s\n", path2file);
        return -2;
    }

    int rows, columns;
    fscanf(file, "%d", &rows);
    fscanf(file, "%d", &columns);

    elements = rows * columns;
    Matrix matrix = calloc(elements, sizeof(struct MatrixVal));
    for(int row = 1; row < rows+1; row++) {
        for(int column = 1; column < columns+1; column++) {
            double val;
            fscanf(file, "%lf", &val);
            setElem(matrix, row, column, val);
        }
    }

    double maxSum = -1, curSum = 0;
    for(int row = 1; row < rows+1; row++) {
        curSum = 0;
        for(int column = 1; column < columns+1; column++) {
            curSum += fabs(getElem(matrix, row, column));
        }
        if(curSum > maxSum) {
            maxSum = curSum;
        }
    }
    showMatrix(matrix);
    printf("%lf\n", maxSum);
    free(matrix);
    fclose(file);

    return 0;
}

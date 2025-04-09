#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result){
    if (rows < 1 || columns < 1 || !result) 
        return 1;
    
    result->rows = rows;
    result->columns = columns;
    
    result->matrix = malloc(rows * sizeof(double*));
    if (!result->matrix) 
        return 1;
    
    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (!result->matrix[i]) {
            s21_remove_matrix(result);
            return 1;
        }
    }
    return 0;
}

void s21_remove_matrix(matrix_t *A){
    if (A && A->matrix) {
        for(int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        free(A->matrix);
        A->matrix = NULL; 
        A->rows = 0;
        A->columns = 0;
        }
    }
    
}

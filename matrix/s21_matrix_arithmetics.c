#include "s21_matrix.h"


int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (!A || !B || !result) return 1;

    if( A->rows < 1 || A->columns < 1 || !A->matrix ||
        B->rows < 1 || B->columns < 1 || !B->matrix) {
        return 1; 
    }
    if (A->rows != B->rows || A->columns != B->columns) {
        return 2; 
    }
    int create_status = s21_create_matrix(A->rows, A->columns, result);
    if (create_status != 0) {
        return create_status; 
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
    }
    return 0;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (!A || !B || !result) return 1;

    if( A->rows < 1 || A->columns < 1 || !A->matrix ||
        B->rows < 1 || B->columns < 1 || !B->matrix) {
        return 1; 
    }

    if (A->rows != B->rows || A->columns != B->columns) {
        return 2; 
    }
    int create_status = s21_create_matrix(A->rows, A->columns, result);
    if (create_status != 0) {
        return create_status; 
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
    }
    return 0;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result){
    if (!A || !result) return 1;

    if( A->rows < 1 || A->columns < 1 || !A->matrix) {
        return 1; 
    }
    int create_status = s21_create_matrix(A->rows, A->columns, result);
    if (create_status != 0) {
        return create_status; 
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
        }
    }
    return 0;
}



int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (!A || !B || !result) return 1;
    if (A->columns != B->rows) return 2;

    int create_status = s21_create_matrix(A->rows, B->columns, result);
    if (create_status != 0) {
        return create_status; 
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
    }
    
    }
    return 0;
}


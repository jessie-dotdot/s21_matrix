#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result){
    if(!A || !result) return 1;

    int create_status = s21_create_matrix(A->columns, A->rows, result);
    if (create_status != 0) {
        return create_status;
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[j][i] = A->matrix[i][j];
        }
    }
    return 0;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    if (!A || !result || A->rows < 1 || A->columns < 1 || A->rows != A->columns)
        return 1;

    int size = A->rows;
    int code = s21_create_matrix(size, size, result);
    if (code) return code;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix_t minor;
            s21_create_matrix(size - 1, size - 1, &minor);

            for (int m_i = 0, mi = 0; m_i < size; m_i++) {
                if (m_i == i) continue;
                for (int m_j = 0, mj = 0; m_j < size; m_j++) {
                    if (m_j == j) continue;
                    minor.matrix[mi][mj++] = A->matrix[m_i][m_j];
                }
                mi++;
            }

            double det = 0;
            s21_determinant(&minor, &det);
            result->matrix[i][j] = det * pow(-1, i + j);
            s21_remove_matrix(&minor);
        }
    }
    return 0;
}
int s21_determinant(matrix_t *A, double *result) {
    if (!A || !result || A->rows != A->columns || A->rows < 1)
        return 1;

    int size = A->rows;
    if (size == 1) {
        *result = A->matrix[0][0];
        return 0;
    }

    *result = 0;
    matrix_t minor;
    s21_create_matrix(size - 1, size - 1, &minor);

    for (int j = 0; j < size; j++) {
        for (int mi = 1; mi < size; mi++) {
            for (int mj = 0, col = 0; mj < size; mj++) {
                if (mj == j) continue;
                minor.matrix[mi - 1][col++] = A->matrix[mi][mj];
            }
        }

        double minor_det = 0;
        s21_determinant(&minor, &minor_det);
        *result += A->matrix[0][j] * pow(-1, j) * minor_det;
    }

    s21_remove_matrix(&minor);
    return 0;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    if (!A || !result || A->rows != A->columns || A->rows < 1)
        return 1;

    double det = 0;
    s21_determinant(A, &det);
    if (fabs(det) < 1e-7) return 2;

    matrix_t comps, transposed;
    s21_calc_complements(A, &comps);
    s21_transpose(&comps, &transposed);

    s21_mult_number(&transposed, 1.0 / det, result);

    s21_remove_matrix(&comps);
    s21_remove_matrix(&transposed);
    return 0;
}
/*
 Copyright (C) 2009 by CCTEC ENGINEERING CO., LTD
 Copyright (C) 2009 by Leslie Zhai <xzhai@cctec.net.cn>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* private operation */
static double m_matrix_multiply_entry(matrix_t *m, matrix_t *n, int row, int col);

/* 
 m-by-n matrix

 Ai,j  n columns j changes
  
  m    A1,1 A1,2 A1,3 ...
 rows
       A2,1 A2,2 A2,3 ...
  i
  c    A3,1 A3,2 A3,3 ...
  h
  a    .
  n    .
  g    .
  s
 */
int 
matrix_init(matrix_t *m) 
{
    size_t alloc_len = 0;
    unsigned int i;

    alloc_len = m->row * sizeof(double *);
    m->data = (double **)malloc(alloc_len);
    if (m->data == NULL) 
    {
#if DEBUG
        printf("fail to allocate memory for m->data\n");
#endif 
        return 0;
    }
    memset(m->data, 0, alloc_len);
    for (i = 0; i < m->row; i++) 
    {
        alloc_len = m->col * sizeof(double);
        m->data[i] = (double *)malloc(alloc_len);
        if (m->data[i] == NULL) 
        {
#if DEBUG
            printf("fail to allocate memory for m->data[%d]\n", i);
#endif
            return 0;
        }
        memset(m->data[i], 0, alloc_len);
    }

    return 1;
}

/*
 while consisting of only one column or row are called vectors
 */
int 
matrix_is_vectors(matrix_t *m) 
{
    if (1 == m->row || 1 == m->col) return 1;
    return 0;
}

void 
matrix_transpose(matrix_t *m, matrix_t *ret) 
{
    unsigned int i, j;

    if (m->row != ret->col || m->col != ret->row) 
    {
#if DEBUG
        printf("fail to transpose matrix\n");
#endif
        return ;
    }

    for (i = 0; i < ret->row; i++) 
        for (j = 0; j < ret->col; j++) 
            ret->data[i][j] = m->data[j][i];
}

void 
matrix_add(matrix_t *m, matrix_t *n, matrix_t *ret) 
{
    unsigned int i, j;

    if (m->row != n->row || m->col != n->col || 
        ret->row != m->row || ret->col != m->col) 
    {
#if DEBUG
        printf("fail to add two martices\n");
#endif
        return ;
    }

    for (i = 0, j = 0; i < m->row; i++)
        for (j = 0; j < m->col; j++) 
            ret->data[i][j] = m->data[i][j] + n->data[i][j];
}

void
matrix_minus(matrix_t *m, matrix_t *n, matrix_t *ret)
{
    unsigned int i, j;

    if (m->row != n->row || m->col != n->col ||
        ret->row != m->row || ret->col != m->col)
    {
#if DEBUG
        printf("fail to add two martices\n");
#endif
        return ;
    }

    for (i = 0, j = 0; i < m->row; i++)
        for (j = 0; j < m->col; j++)
            ret->data[i][j] = m->data[i][j] - n->data[i][j];
}

/*
 M0,0 M0,1 M0,2 ...    N0,0 N0,1 N0,2 ...
 M1,0 M1,1 M1,2 ...    N1,0 N1,1 N1,2 ...
 M2,0 M2,1 M2,2 ...    N2,0 N2,1 N2,2 ...
                    X 
 .                     .
 .                     .
 .                     .
 
 M0,0 * N0,0 + M0,1 * N0,1 + M0,2 * N0,2 + ... = ENTRY0,0
 */
static double 
m_matrix_multiply_entry(matrix_t *m, matrix_t *n, int row, int col) 
{
    unsigned int i, j;
    double ret = 0.0;

    for (i = 0, j = 0; i < m->col && j < n->row; i++, j++) 
    {
        ret += m->data[row][i] * n->data[j][col];
    }

    return ret;
}

/*
 If A is an m-by-n matrix and B is an n-by-p matrix, then their matrix 
 product AB is the m-by-p matrix ...
 */
void 
matrix_multiply(matrix_t *m, matrix_t *n, matrix_t *ret) 
{
    unsigned int i, j;

    /*
     Multiplication of two matrices is defined only if the number of columns 
     of the left matrix is the same as the number of rows of the right matrix
     */
    if (m->row != n->col) 
    {
#if DEBUG
        printf("fail to multiply two matrices\n");
#endif
        return ;
    }

    if (ret->row != m->row || ret->col != n->col) 
    {
#if DEBUG
        printf("martix multiplication product is not %d-by-%d martix\n", 
            m->row, n->col);
#endif
        return ;
    }

    for (i = 0; i < m->row; i++) 
    {
        for (j = 0; j < n->col; j++) 
        {
            // i refers to current row, and j to column
            ret->data[i][j] = m_matrix_multiply_entry(m, n, i, j);
        }
    }
}

void 
matrix_cleanup(matrix_t *m) 
{
    unsigned int i;

    if (m && m->data) 
    {
        for (i = 0; i < m->row; i++) 
        {
            free(m->data[i]);
            m->data[i] = NULL;
        }
        free(m->data);
        m->data = NULL;
        free(m);
        m = NULL;
    }
}

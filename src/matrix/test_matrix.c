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

static void m_walk_matrix(matrix_t *m);

static void m_walk_matrix(matrix_t *m) 
{
    unsigned int i, j;

    for (i = 0; i < m->row; i++)
        for (j = 0; j < m->col; j++)
            printf("matrix[%d][%d] = %f\n", i, j, m->data[i][j]);
}

int 
main() 
{
    matrix_t *m = NULL, *n = NULL, *add = NULL, *multi = NULL, *trans = NULL;

    m = (matrix_t *)malloc(sizeof(matrix_t));
    memset(m, 0, sizeof(matrix_t));
    m->row = 2;
    m->col = 3;
    matrix_init(m);
    m->data[0][0] = 1, m->data[0][1] = 0, m->data[0][2] = 2, 
        m->data[1][0] = -1, m->data[1][1] = 3, m->data[1][2] = 1;

    n = (matrix_t *)malloc(sizeof(matrix_t));
    memset(n, 0, sizeof(matrix_t));
    n->row = 3;
    n->col = 2;
    matrix_init(n);
    n->data[0][0] = 3, n->data[0][1] = 1, n->data[1][0] = 2, 
        n->data[1][1] = 1, n->data[2][0] = 1, n->data[2][1] = 0;

    trans = (matrix_t *)malloc(sizeof(matrix_t));
    memset(trans, 0, sizeof(matrix_t));
    trans->row = 3;
    trans->col = 2;
    matrix_init(trans);
    matrix_transpose(m, trans);
    m_walk_matrix(trans);

    add = (matrix_t *)malloc(sizeof(matrix_t));
    memset(add, 0, sizeof(matrix_t));
    add->row = 2;
    add->col = 3;
    matrix_init(add);

    matrix_add(m, m, add);
    m_walk_matrix(add);

    matrix_minus(m, m, add);
    m_walk_matrix(add);
    
    multi = (matrix_t *)malloc(sizeof(matrix_t));
    memset(multi, 0, sizeof(matrix_t));
    multi->row = m->row;
    multi->col = n->col;
    matrix_init(multi);

    matrix_multiply(m, n, multi);
    m_walk_matrix(multi);

    matrix_cleanup(m);
    matrix_cleanup(n);
    matrix_cleanup(add);
    matrix_cleanup(multi);

    return 0;
}

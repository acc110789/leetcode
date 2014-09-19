/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include "cm.h"
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO: Attribute */
static matrix_t *m_amatrix = NULL;      // Augmented Matrix
static matrix_t *m_R = NULL;
static matrix_t *m_A = NULL;            // The A of Augmented Matrix
static matrix_t *m_Y = NULL;
static matrix_t *m_B = NULL;            // The B of Augmented Matrix
static matrix_t *m_X = NULL;            // The root of Augmented Matrix
static int m_order = 0;

/* TODO: Operation */
static int m_cm_set_R();
static double m_cm_set_R_sum(int ri, int rj);
static int m_cm_set_Y();
static double m_cm_set_Y_sum(int yi);
static double m_cm_set_X_sum(int xi);

int 
cm_init() 
{
    return 1;
}

void 
cm_cleanup() 
{
    matrix_cleanup(m_amatrix);
    matrix_cleanup(m_A);
    matrix_cleanup(m_B);
    matrix_cleanup(m_R);
    matrix_cleanup(m_Y);
    matrix_cleanup(m_X);
}

static double 
m_cm_set_R_sum(int ri, int rj) 
{
    int i;
    double ret = 0.0;
        
    for (i = 0; i < ri; i++) 
    {
        ret += (m_R->data[i][ri] / m_R->data[i][i]) * m_R->data[i][rj];
    }
    return ret;
}

static int 
m_cm_set_R() 
{
    int ret, i, j;

    m_R = (matrix_t *)malloc(sizeof(matrix_t));
    if (m_R == NULL) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to allocate memory for m_R\n", __LINE__);
#endif
        return 0;
    }
    memset(m_R, 0, sizeof(matrix_t));
    m_R->row = m_order;
    m_R->col = m_order;
    ret = matrix_init(m_R);
    if (!ret) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to init m_R\n", __LINE__);
#endif
        return 0;
    }
    for (i = 0; i < m_order; i++) 
    {
        for (j = 0; j < m_order; j++) 
        {
            if (i == 0) 
            {
                m_R->data[i][j] = m_A->data[i][j];
            } 
            else if (i > j) 
            {
                m_R->data[i][j] = 0;
            } 
            else 
            {
                m_R->data[i][j] = m_A->data[i][j] - m_cm_set_R_sum(i, j);
            }
        }
    }
#if DEBUG
    printf("\nDEBUG at %d: built R matrix\n", __LINE__);
    for (i = 0; i < m_order; i++) 
    {
        for (j = 0; j < m_order; j++) 
        {
            printf("%f\t", m_R->data[i][j]);
        }
    }
#endif
    return 1;
}

static double 
m_cm_set_Y_sum(int yi) 
{
    int i;
    double ret = 0.0;

    for (i = 0; i < yi; i++) 
    {
        ret += (m_R->data[i][yi] / m_R->data[i][i]) * m_Y->data[i][0];
    }
    return ret;
}

static int 
m_cm_set_Y() 
{
    int ret, i;

    m_Y = (matrix_t *)malloc(sizeof(matrix_t));
    if (m_Y == NULL) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to allocate memory for m_Y\n", __LINE__);
#endif
        return 0;
    }
    memset(m_Y, 0, sizeof(matrix_t));
    m_Y->row = m_order;
    m_Y->col = 1;
    ret = matrix_init(m_Y);
    if (!ret) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to init m_Y\n", __LINE__);
#endif
        return 0;
    }
    for (i = 0; i < m_order; i++) 
    {
        if (i == 0) 
        {
            m_Y->data[i][0] = m_B->data[i][0];
        } 
        else 
        {
            m_Y->data[i][0] = m_B->data[i][0] - m_cm_set_Y_sum(i);
        }
    }
#if DEBUG
    printf("\nDEBUG at %d: built Y matrix\n", __LINE__);
    for (i = 0; i < m_order; i++) 
    {
        printf("%f\t", m_Y->data[i][0]);
    }
#endif
    return 1;
}

void 
cm_set_matrix(double *matrix, int order) 
{
    int i, j = 0, ret;

    m_order = order;
    /* TODO: To build the augmented matrix [order][order + 1] 
     *
     * m_amatrix = m_A * m_B
     *
     * */
    m_amatrix = (matrix_t *)malloc(sizeof(matrix_t));
    if (m_amatrix == NULL) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to allocate memory for m_amatrix\n", __LINE__);
#endif
        return ;
    }
    memset(m_amatrix, 0, sizeof(matrix_t));
    m_amatrix->row = order;
    m_amatrix->col = order + 1;
    ret = matrix_init(m_amatrix);
    if (!ret) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to init m_amatrix\n", __LINE__);
#endif
        return ;
    }
#if DEBUG
    printf("\nDEBUG at %d: built augmented matrix\n", __LINE__);
#endif    
    for (i = 0; i < order; i++) 
    {
        for (j = 0; j < order + 1; j++) 
        {
            m_amatrix->data[i][j] = matrix[i * (order + 1) + j];
#if DEBUG
            printf("%f\t", m_amatrix->data[i][j]);
#endif
        }
    }
   
    /* TODO: To build the A[order][order] of augmented matrix 
     *
     *  A[order][order ] should be a positive-definite matrix
     *
     * */
    m_A = (matrix_t *)malloc(sizeof(matrix_t));
    if (m_A == NULL) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to allocate memory for m_A\n", __LINE__);
#endif
        return ;
    }
    memset(m_A, 0, sizeof(matrix_t));
    m_A->row = m_A->col = order;
    ret = matrix_init(m_A);
    if (!ret) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to init m_A\n", __LINE__);
#endif
        return ;
    }
#if DEBUG
    printf("\nDEBUG at %d: built A matrix\n", __LINE__);
#endif
    for (i = 0; i < order; i++) 
    {
        for (j = 0; j < order; j++) 
        {
            m_A->data[i][j] = m_amatrix->data[i][j];
#if DEBUG
            printf("%f\t", m_A->data[i][j]);
#endif
        }
    }

    ret = m_cm_set_R();
    if (!ret) 
    {
#if DEBUG
        printf("fail to set R matrix\n");
#endif        
        return ;
    }

    /* TODO: To build the B[order][1] of augmented matrix */
    m_B = (matrix_t *)malloc(sizeof(matrix_t));
    if (m_B == NULL) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to allocate memory for m_B\n", __LINE__);
#endif
        return ;
    }
    memset(m_B, 0, sizeof(matrix_t));
    m_B->row = order;
    m_B->col = 1;
    ret = matrix_init(m_B);
    if (!ret) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to init m_B\n", __LINE__);
#endif
        return ;
    }
#if DEBUG
    printf("\nDEBUG at %d: built B matrix\n", __LINE__);
#endif
    for (i = 0; i < order; i++) 
    {
        m_B->data[i][0] = m_amatrix->data[i][j];
#if DEBUG
        printf("%f\t", m_B->data[i][0]);
#endif
    }

    ret = m_cm_set_Y();
    if (!ret) 
    {
#if DEBUG
        printf("fail to set Y matrix\n");
#endif
        return ;
    }
}

static double 
m_cm_set_X_sum(int xi) 
{
    int k;
    double ret = 0.0;

    for (k = xi + 1; k < m_order; k++) 
    {
        ret += m_R->data[xi][k] * m_X->data[k][0];
    }
    return ret;
}

void 
cm_get_root(double *root) 
{
    int ret, i;

    m_X = (matrix_t *)malloc(sizeof(matrix_t));
    if (m_X == NULL) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to allocate memory for m_X\n", __LINE__);
#endif
        return ;
    }
    memset(m_X, 0, sizeof(matrix_t));
    m_X->row = m_order;
    m_X->col = 1;
    ret = matrix_init(m_X);
    if (!ret) 
    {
#if DEBUG
        printf("DEBUG at %d: fail to init m_X\n", __LINE__);
#endif
        return ;
    }
    for (i = m_order - 1; i >= 0; i--) 
    {
        if (i == m_order - 1) 
        {
            m_X->data[i][0] = m_Y->data[i][0] / m_R->data[i][i];
        } 
        else 
        {
            m_X->data[i][0] = (m_Y->data[i][0] - m_cm_set_X_sum(i)) / 
                m_R->data[i][i];
        }
    }
#if DEBUG
    printf("\nDEBUG at %d: built X matrix\n", __LINE__);
#endif
    for (i = 0; i < m_order; i++) 
    {
#if DEBUG
        printf("%f\t", m_X->data[i][0]);
#endif
        root[i] = m_X->data[i][0];
    }
}

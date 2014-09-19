/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <math.h>

#include "lspa.h"
#include "cm.h"

#define M 2

/* TODO: Attribute */
static double m_coefficient[M + 1];

int 
lspa_init() 
{
    return 1;
}

void 
lspa_cleanup() 
{
    cm_cleanup();
}

void 
lspa_set_discrete_data(double *x, double *y, long count) 
{
    double T[M + 1], S[(M + 1) * (M + 1)], 
        A[M + 1][M + 2], matrix[(M + 1) * (M + 2)];
    int i, j;

    for (i = 0; i < M + 1; i++) 
    {
        T[i] = 0;
        for (j = 0; j < count; j++) 
        {
            T[i] += y[j] * pow(x[j], i);
        }
    }
    for (i = 0; i < (M + 1) * (M + 1); i++) 
    {
        S[i] = 0;
        for (j = 0; j < count; j++) 
        {
            S[i] += pow(x[j], i);
        }
    }
#if DEBUG
    printf("\nDEBUG at %d: T[M]\n", __LINE__);
    for (i = 0; i < M + 1; i++) 
    {
        printf("%f\t", T[i]);
    }
    printf("\nDEBUG at %d: S[(M + 1) * (M + 1)]\n", __LINE__);
    for (i = 0; i < (M + 1) * (M + 1); i++) 
    {
        printf("%f\t", S[i]);
    }
#endif
    /* TODO: To build matrix */
    for (i = 0; i < M + 1; i++) 
    {
        for (j = 0; j < M + 2; j++) 
        {
            A[i][j] = S[i + j];
        }
        A[i][M + 1] = T[i];
    }
#if DEBUG
    printf("\nDEBUG at %d: build matrix\n", __LINE__);
#endif
    for (i = 0; i < M + 1; i++) 
    {
        for (j = 0; j < M + 2; j++) 
        {
#if DEBUG
            printf("%f\t", A[i][j]);
#endif
            matrix[i * (M + 2) + j] = A[i][j];
        }
    }
    cm_set_matrix(matrix, M + 1);
    cm_get_root(m_coefficient);
}

double *
lspa_get_coefficient() 
{
#if DEBUG
    int i;

    printf("\nDEBUG at %d: coefficient\n", __LINE__);
    for (i = 0; i < M + 1; i++) 
    {
        printf("%f\t", m_coefficient[i]);
    }
#endif
    return m_coefficient;
}

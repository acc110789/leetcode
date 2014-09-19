/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include "cm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO: Augmented Matrix is the Positive-definite matrix 
 *  such as below:
 *
 * 5 2  1  0 8
 * 2 8  -3 1 19
 * 1 -3 -6 2 -3
 * 0 1  2  7 -14
 *
 * see http://en.wikipedia.org/wiki/Positive-definite_matrix
 *
 * */

int main() 
{
    double matrix[] = {
        5, 10, 30, 8, 
        10, 30, 100, 20, 
        30, 100, 354, 70 
    };
    double *root = NULL;
    int i;

    cm_set_matrix(matrix, 3);
    root = (double *)malloc(3 * sizeof(double));
    if (root == NULL) 
    {
        cm_cleanup();
        return -1;
    }
    cm_get_root(root);
    printf("\nroot:\n");
    for (i = 0; i < 3; i++) 
    {
        printf("%f\t", root[i]);
    }
    printf("\n");

    cm_cleanup();
    if (root) 
    {
        free(root);
        root = NULL;
    }

    return 0;
}

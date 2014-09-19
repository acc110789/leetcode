/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include "lspa.h"

#include <stdio.h>

int 
main() 
{
    double x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 
        13, 14, 15, 16};
    double y[] = {4.00, 6.40, 8.00, 8.80, 9.22, 9.50, 
        9.70, 9.86, 10.00, 10.20, 10.32, 10.42, 10.50, 
        10.55, 10.58, 10.60};
    
    lspa_set_discrete_data(x, y, sizeof(y) / sizeof(double));
    lspa_get_coefficient();
    lspa_cleanup();
        
    return 0;
}

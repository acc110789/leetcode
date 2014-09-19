/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#ifndef __LSPA_H__
#define __LSPA_H__

int lspa_init();
void lspa_cleanup();
void lspa_set_discrete_data(double *x, double *y, long count);
double *lspa_get_coefficient();

#endif /* __LSPA_H__ */

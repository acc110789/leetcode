/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#ifndef __CM_H__
#define __CM_H__

int cm_init();
void cm_cleanup();
void cm_set_matrix(double *matrix, int order);
void cm_get_root(double *root);

#endif /* __CM_H__ */

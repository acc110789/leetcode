/* Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    char *ptr = NULL;

    ptr = malloc(66);
    strncpy(ptr, "Hello world", 66);
    printf("%s\n", ptr);
    
    if (ptr) {
        printf("frees  the  memory  space pointed to by ptr\n");
        free(ptr);
    }

    strncpy(ptr, ";-)", 66);
    printf("%s\n", ptr);
    
    ptr = NULL;

    return 0;
}

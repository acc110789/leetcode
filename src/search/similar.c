/* Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    char *primary[] = {"1280x800", "1024x768", "800x600", "640x480", 
                       "640x400", NULL};
    char *second[] = {"1366x768", "1280x1024", "1280x960", "1280x720", 
                      "1024x768", "800x600", "640x480", "720x400", NULL};
    int i;
    int j;

    printf("primary resolution:\n");
    i = 0;
    while (primary[i]) {
        printf("%s\n", primary[i]);
        i++;
    }

    printf("second resolution: \n");
    i = 0;
    while (second[i]) {
        printf("%s\n", second[i]);
        i++;
    }

    printf("find the best similar resolution: \n");
    i = 0;
    while (primary[i]) {
        j = 0;
        while (second[j]) {
            if (strcmp(primary[i], second[j]) == 0) {
                printf("%s\n", primary[i]);
                goto cleanup;
            }
            j++;
        }
        i++;
    }

cleanup:
    
    return 0;
}

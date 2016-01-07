/* Copyright (C) 2014 Leslie Zhai <xiangzhai83@gmail.com> */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define BUF_SIZE 80

static char* m_oldstr = NULL;

char* LeslieStrtok(char* str, char* delim) 
{
    char*   s       = NULL;
    char*   token   = NULL;
    char*   d       = NULL;
    int     n       = 0;

    if (str != NULL) 
        m_oldstr = str;

    if (*m_oldstr == '\0') 
        return NULL;

    s = m_oldstr;

    token = malloc(BUF_SIZE);
    assert(token);

    while (*m_oldstr != '\0') {
        d = delim;
        while (*d != '\0') {
            if (*m_oldstr == *d) {
                m_oldstr++;
                strncpy(token, s, n);
                return token;
            }
            d++;
        }
        m_oldstr++;
        n++;
    }

    return s;
}

int main(int argc, char *argv[]) 
{
    char str[BUF_SIZE] = {'\0'};    /* memset 0 */
    char delim[3] = ",|";
    char *token = NULL;
    
    if (argv[1]) 
        snprintf(str, sizeof(str) - 1, argv[1]);
    else 
        snprintf(str, sizeof(str) - 1, "hello|world,leslie,zhai");
    printf("strtok %s with %s\n", str, delim);

#if 0
    token = strtok(str, delim);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, delim);
    }
#endif

    token = LeslieStrtok(str, delim);
    while (token != NULL) {
        printf("%s\n", token);
        token = LeslieStrtok(NULL, delim);
    }
    
    return 0;
}

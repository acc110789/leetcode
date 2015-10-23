#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    char *ptr = (char *)malloc(1);
    if (ptr == NULL) {
        printf("ERROR: fail to allocate\n");
        return 0;
    }
    strncpy(ptr, "Hello world", 1);
    free(ptr);
    ptr = NULL;
    return 0;
}

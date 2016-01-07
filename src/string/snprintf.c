#include <stdio.h>

int main(int argc, char *argv[]) 
{
    char buf[8] = { '\0' };
    char *ptr = NULL;

    printf("%d\n", sizeof(buf) - 1);
    snprintf(buf, sizeof(buf) - 1, "%s", argv[1] ? argv[1] : "zhaixiang");
    printf("%s\n", buf);
    ptr = buf;
    while (*ptr) {
        printf("%c\n", *ptr);
        ptr++;
    }

    return 0;
}

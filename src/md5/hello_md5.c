#include <stdio.h>

#include "md5.h"

int main(int argc, char *argv[]) 
{
    unsigned char md5num[16] = { '\0' };
    char md5sum[33] = { '\0' };
    if (md5_from_file(argv[1], md5num) == -1) {
        printf("ERROR: failed to get md5num\n");
    } else {
        md5_num2str(md5num, md5sum);
        printf("md5sum %s: %s\n", argv[1], md5sum);
    }
    return 0;
}

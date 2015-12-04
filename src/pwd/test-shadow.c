#include <stdio.h>
#include <shadow.h>

int main(int argc, char *argv[]) 
{
    struct spwd *sp = NULL;
    sp = getspnam(argv[1] ? argv[1] : "lesliezhai");
    if (sp) {
        printf("%s\n", sp->sp_pwdp);
    } else {
        printf("ERROR: user does not exists\n");
    }
    endspent();
    return 0;
}

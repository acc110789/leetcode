#include <stdio.h>

struct Person
{   
    int height;
    int weight;
    int age;
};

int main(int argc, char *argv[])
{
    struct Person p = { .age = 18 };
    return 0;
}

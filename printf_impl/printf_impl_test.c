#include <stdio.h>

#include "printf_impl.h"

int main()
{
    char c = 'a';
    int x = 10;
    char *str = "tomer alayof";
    print("hello world= %c %d %s", c, x, str);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char a[] = "sajflksa||fasiohfds";
    char *b = strstr(a, "||");

    b[0] = 'a';

    printf("%s\n%s\n", a, b);
}
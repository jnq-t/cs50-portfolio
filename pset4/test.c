#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void)
{
    char *name= malloc(8);
    strcpy(name, "jesse");
    printf("%s", name);
}
//Bug A - Division by zero
#include <stdio.h>

int main()
{
    int a = 10;
    int b = 0;
    int c = a/b;
    printf("c = %d\n", c);
    return 0;
}

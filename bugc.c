#include <stdio.h>
void hello(){
    printf("hello world");
    hello();
}
int main(){
    hello();
    return 1;
}
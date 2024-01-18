//Bug A - Division by zero
#include <stdio.h>

void func() {
    int a = 5;
    int b = 0;

    int c = a / b; // Divide by zero
}

int main() {
    func();
    return 0;
}
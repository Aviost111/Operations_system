#include <stdio.h>

int divide(int a, int b) {
  return a/b; 
}

int main() {
  int result = divide(5, 0);
  printf("Result: %d\n", result);
  
  return 0;
}

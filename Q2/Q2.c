#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;

    // Input side lengths from the user
    printf("Enter the length of side a: ");
    scanf("%lf", &a);

    printf("Enter the length of side b: ");
    scanf("%lf", &b);

    printf("Enter the length of side c: ");
    scanf("%lf", &c);

    // Check if it's a Pythagorean triangle
    if ((a * a + b * b == c * c) || (a * a + c * c == b * b) || (b * b + c * c == a * a)) {
        // Calculate angles in radians using trigonometric functions
        double angleA = asin(a / c);
        double angleB = asin(b / c);
        double angleC = asin(c / c);

        // Print angles in radians
        printf("Angles in radians: A=%.4lf, B=%.4lf, C=%.4lf\n", angleA, angleB, angleC);
    } else {
        // Print an error message if it's not a Pythagorean triangle
        printf("Error\n");
    }

    return 0;
}






//Q2

pifagor3 Program
The pifagor3 program is designed to accept three side lengths from the user and determine whether they form a Pythagorean triple. If the lengths form a Pythagorean triple, the program calculates and prints the angles of the triangle in radians. If not, it prints an error message and exits.

Usage
To run the program, follow these steps:

Compile the program using your preferred C compiler. For example:

Copy code
gcc -o pifagor3 pifagor3.c -lm
Execute the program by running the compiled binary:

bash
Copy code
./pifagor3
Follow the prompts to enter the lengths of the triangle's sides.

Input Requirements
The program expects three positive integer values representing the lengths of the sides of a triangle.
Output
If the input lengths form a Pythagorean triple, the program will print the angles of the triangle in radians.
If the input lengths do not form a Pythagorean triple, the program will print an error message and exit.
Dependencies
The program relies on the standard math library (-lm) to utilize functions like asin() for calculating angles.
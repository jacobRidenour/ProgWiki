#include <stdio.h>

// Source files are read top-to-bottom. If we are going to reference a type or 
// function defined in this file before its definition, we need to declare it.
// Declarations consist of the function's return type, name, parameters (which
// may be optionally replaced with void if none), and a semicolon to end the 
// line. Traditionally, declarations (along with one-liner definitions) are 
// found in header (.h) files, and definitions are found in .c files.
void types(); // equivalent to void types(void);
void fixed_width_integers(); 
void maths();

// Example of a function definition. After the (parameters), the entire function
// is contained between brackets {}.
int main(int argc, char* argv[]) {
    // Each statement (usually a line) ends with a semicolon.
    types();
}

#include <limits.h> // Typically all of your #includes go at the top. limits.h
                    // contains the *_MIN and *_MAX macros used for integral types.
#include <float.h>


// Introduce C's Type system
void types() {
    // C has 4 basic arithmetic types
    //char my_char = 'E'; // Single quotes required for single char literals
    //my_char = 45; // Assigning an int, the ASCII character set is used:
                  // https://en.wikipedia.org/wiki/ASCII#Character_set

    //int my_int = 4;
    //float my_float = 4.1;
    //double my_double = 4.5;

    // The C standard only specifies the _minimum_ size for each arithmetic
    // type, the size itself is determined by the implementation. If the 
    // minimum size of a type could cause issues, you can verify its size
    // (in bytes) with the sizeof() operator, e.g. sizeof(int)

    // Arithmetic type modifiers: signed, unsigned, short, long
    // chars with modifiers all have a minimum size of 8 bits
    printf("Type           Size  [Range]\n");
    printf("------------------------------------------------\n");
    printf("char           %zu     %d to %d\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("signed char    %zu     %d to %d\n", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char  %zu        0 to %d\n\n", sizeof(unsigned char), UCHAR_MAX);

    // These tables illustrate that the actual size of some types may be 
    // different than the minimum size of types prescribed by the standard.
    // Your results will vary depending on the implementation used for
    // compilation.
    printf("------------------------------------------------\n");
    printf("short, short int, signed short, signed short int\n");
    printf("Minimum size: 2 bytes (16 bits)\n");
    printf("Actual size:  %zu bytes (%zu bits)\n", sizeof(short), 8*sizeof(short));
    printf("[Range]:      %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("------------------------------------------------\n");
    printf("unsigned short, unsigned short int\n");
    printf("Minimum size: 2 bytes (16 bits)\n");
    printf("Actual size:  %zu bytes (%zu bits)\n", sizeof(unsigned short), 8*sizeof(unsigned short));
    printf("[Range]:      0 to %u\n\n", USHRT_MAX);

    printf("------------------------------------------------\n");
    printf("int, signed, signed int\n");
    printf("Minimum size: 2 bytes (16 bits)\n");
    printf("Actual size:  %zu bytes (%zu bits)\n", sizeof(int), 8*sizeof(int));
    printf("[Range]:      %d to %d\n", INT_MIN, INT_MAX);
    printf("------------------------------------------------\n");
    printf("unsigned, unsigned int\n");
    printf("Minimum size: 2 bytes (16 bits)\n");
    printf("Actual size:  %zu bytes (%zu bits)\n", sizeof(unsigned), 8*sizeof(unsigned));
    printf("[Range]:      0 to %u\n\n", UINT_MAX);

    printf("----------------------------------------------------------------\n");
    printf("long, long int, signed long, signed long int\n");
    printf("Minimum size: 4 bytes (32 bits)\n");
    printf("Actual size:  %zu bytes (%zu bits)\n", sizeof(long), 8*sizeof(long));
    printf("[Range]:      %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("----------------------------------------------------------------\n");
    printf("unsigned long, unsigned long int\n");
    printf("Minimum size: 4 bytes (32 bits)\n");
    printf("Actual size:  %zu bytes (%zu bits)\n", sizeof(unsigned long), 8*sizeof(unsigned long));
    printf("[Range]:      0 to %lu\n\n", ULONG_MAX);

    printf("----------------------------------------------------------------\n");
    printf("long long, long long int, signed long long, signed long long int\n");
    printf("Minimum size: 8 bytes (64 bits)\n");
    printf("Actual size:  %zu bytes (%zu bits)\n", sizeof(long long), 8*sizeof(long long));
    printf("[Range]:      %lld to %lld\n", LLONG_MIN, LLONG_MAX);
    printf("----------------------------------------------------------------\n");
    printf("unsigned long long, unsigned long long int\n");
    printf("Minimum size: 8 bytes (64 bits)\n");
    printf("Actual size:  %zu bytes (%zu bits)\n", sizeof(unsigned long long), 8*sizeof(unsigned long long));
    printf("[Range]:      0 to %llu\n\n", ULLONG_MAX);

    // Floating types only have their minimum limits specified, but
    // implementations may define them in <float.h>
    printf("----------------------------------------------------------------\n");
    printf("float (IEEE 754 single-precision floating-point number)*\n");
    printf("Size:  %zu bytes (%zu bits)\n", sizeof(float), 8*sizeof(float));
    printf("[Range]:      %e to %e\n", FLT_MIN, FLT_MAX);
    printf("----------------------------------------------------------------\n");
    printf("double (IEEE 754 double-precision floating-point number)*\n");
    printf("Size:  %zu bytes (%zu bits)\n", sizeof(double), 8*sizeof(double));
    printf("[Range]:      %e to %e\n", DBL_MIN, DBL_MAX);
    printf("----------------------------------------------------------------\n");
    printf("double (IEEE 754 extended-precision floating-point number)*\n");
    printf("Size:  %zu bytes (%zu bits)\n", sizeof(long double), 8*sizeof(long double));
    printf("[Range]:      %Le to %Le\n", LDBL_MIN, LDBL_MAX);
    printf("*Usually. Extended is usually 80 bits, with padding to 96 or 128.\n");

    // Complex types were added in C99: float _Complex, double _Complex, long double _Complex
    // Imaginary types were addedin C11: float _Imaginary, double _Imaginary, long double _Imaginary
    // Found in <complex.h>

    fixed_width_integers();
}

#include <inttypes.h> // fixed-width integer types also available in <stdint.h>

void fixed_width_integers() {
    // Fixed-width integer types were added in C99, meant especially for
    // portability on embedded systems. Outside of exact-width variants,
    // least-width, fastest, pointer, and maximum-width variants are also
    // available.


    maths();
}

// Introduce variable declaration and arithmetic in C
void maths() {

    logic_and_conditionals();
}


// Introduce logical operators and conditionals in C


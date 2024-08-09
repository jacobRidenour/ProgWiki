#include <stdio.h>

// Source files are read top-to-bottom. If we are going to reference a type or 
// function defined in this file before its definition, we need to declare it.
// Declarations consist of the function's return type, name, parameters (which
// may be optionally replaced with void if none), and a semicolon to end the 
// line. Traditionally, declarations (along with one-liner definitions) are 
// found in header (.h) files, and definitions are found in .c files.
void types(); // equivalent to void types(void);
void maths(); void pointers(); void arrays();
void operators();
void statements();
void storage_class_specifiers(); void static_demo();

// Example of a function definition. After the (parameters), the entire function
// is contained between brackets {}.
int main(int argc, char* argv[]) {
    // Each statement (usually a line) ends with a semicolon.
    /*types();*/ maths(); pointers(); arrays();
    //operators();
    //statements();
    //storage_class_specifiers();
}

#include <limits.h> // Typically all of your #includes go at the top. limits.h
                    // contains the *_MIN and *_MAX macros used for integral types.
#include <float.h>
#include <inttypes.h> // fixed-width integer types also available in <stdint.h>

// Introduce C's Type system
void types() {
    // C has 4 basic arithmetic types
    // char, int, float, double

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
    printf("[Range]: uses g int, signed long, signed long int\n");
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
    printf("long double (IEEE 754 extended-precision floating-point number)*\n");
    printf("Size:  %zu bytes (%zu bits)\n", sizeof(long double), 8*sizeof(long double));
    printf("[Range]:      %Le to %Le\n", LDBL_MIN, LDBL_MAX);
    printf("*Usually. Extended is usually 80 bits, with padding to 96 or 128.\n");

    // Complex types were added in C99: float _Complex, double _Complex, long double _Complex
    // Imaginary types were addedin C11: float _Imaginary, double _Imaginary, long double _Imaginary
    // Found in <complex.h>

    // Fixed-width integer types were added in C99, meant especially for
    // portability on embedded systems. Outside of exact-width variants,
    // least-width, fastest, pointer, and maximum-width variants are also
    // available.

    // Probably not worth the extra effort to use if you don't require such precision

    printf("----------------------------------------------------------------\n");
    printf("Type      Size (bytes) [Range]\n");
    printf("----------------------------------------------------------------\n");
    printf("int8_t    %zu (%zu bits)  %d to %d\n", sizeof(int8_t), 8*sizeof(int8_t), INT8_MIN, INT8_MAX);
    printf("uint8_t   %zu (%zu bits)     0 to %u\n\n", sizeof(uint8_t), 8*sizeof(uint8_t), UINT8_MAX);

    printf("int16_t    %zu (%zu bits)  %d to %d\n", sizeof(int16_t), 16*sizeof(int16_t), INT16_MIN, INT16_MAX);
    printf("uint16_t   %zu (%zu bits)     0 to %u\n\n", sizeof(uint16_t), 16*sizeof(uint16_t), UINT16_MAX);

    printf("int32_t    %zu (%zu bits)  %d to %d\n", sizeof(int32_t), 32*sizeof(int32_t), INT32_MIN, INT32_MAX);
    printf("uint32_t   %zu (%zu bits)     0 to %u\n\n", sizeof(uint32_t), 32*sizeof(uint32_t), UINT32_MAX);

    printf("int64_t    %zu (%zu bits)  %ld to %ld\n", sizeof(int64_t), 64*sizeof(int64_t), INT64_MIN, INT64_MAX);
    printf("uint64_t   %zu (%zu bits)     0 to %lu\n\n", sizeof(uint64_t), 64*sizeof(uint64_t), UINT64_MAX);
}

// Show off operator precedence/associativity
void operators() {
    // Demonstration of operator precedence for comparison of different languages

    int x = 5;
    float y = 4.4;
    int z = 16;

    printf("x = %d, y = %.2lf, z = %d\n", x, y, z);
    printf("Result = y + x %% z++ * -sizeof y > x ? x : y\n");
    int result = y + x % z++ * -sizeof y > x ? x : y;
    printf("Result = %d\n\n", result);
    printf("x = %d, y = %.2lf, z = %d\n", x, y, z);
}

// Introduce statements
void statements() {
    int x = 1;

    // Compound Statements (aka blocks) - enclosed by braces
    if(x) {
        printf("if(x) block entered");
        printf("\n");
    }
    // Blocks create scopes; local variables that are declared here are not accessible
    // before or after the enclosing braces. Variables in C have block scope in most cases,
    // with some exceptions like extern variables and global variables.

    // Expression Statements
    // Most statements are expressions (assignments, function calls)
    // A line with only a semicolon is a null statement
    x = 4;

    // *******************************************************************
    // Definition Of True: scalar; 0 is false, everything else is true
    // Applies to the controlling expressiom for all selection statements*
    // *for loops are unique
    // *******************************************************************
    // A bool type (_Bool) was added in C99 in <stdbool.h>; may be useful 
    // for additional type safety; under the hood, they are macros with true
    // defined as 1 and false defined as 0.

    // Selection Statement - if, if-else
    if(x) {
        printf("if(x) condition satisfied");
        printf("\n");
    }
    else printf("if(1) condition not satisfied\n");

    // For conditionals/loops, only one following line is executed if not
    // part of a block (enclosed with {braces}). As a result, there is no
    // "elif" in C; else { if {} } is equivalent to else if {}
    if(!x) {
        printf("if(!x) condition satisfied\n");
    }
    else {
        if (x) {
            printf("else { if (x) } condition satisfied\n");
        }
    }

    if(!x);
    else if (x) {
        printf("else if (x) condition satisfied\n");
    }

    // Selection Statement - switch
    int day = 3;  

    printf("\nThe day number is: %d, which corresponds to ", day);

    switch(day) {
        case 1:
            printf("Sunday\n");
            break; 
        case 2:
            printf("Monday\n");
            break;
        case 3:
            printf("Tuesday\n");
            break;
        case 4:
            printf("Wednesday\n");
            break;
        case 5:
            printf("Thursday\n");
            break;
        case 6:
            printf("Friday\n");
            break;
        case 7:
            printf("Saturday\n");
            break;
        default:
            printf("Invalid day\n");
            break;
    }
    // Without a break (exit) following a matched case, the checks for matches continue. 
    // The default block is a catch-all, usually for the default or error handling.

    // Iteration Statements - while, do-while
    int i = 10;
    while(i > 0) {
        if(i == 10) printf("i is %d ", i);
        printf("...%d", i);
        i--;
    }
    // The expression for while() is checked once per iteration. It may not even
    // run once, like an if statement.

    // You can guarantee that a loop runs at least once with a do-while loop,
    // wherein the loop body executes once, and then the condition is checked.
    do {
        i += 10;
    } while(i < 10);
    printf("\ni is %d\n\n", i);

    // Iteration Statements - for
    // for( init-clause ; cond-expression ; iteration-expression ) loop body
    // init-clause is evaluated once; it can be an expression, or declaration(C99)
    // cond-expression is evaluated before the loop body; exit if result is 0
    // iteration-expression evaluated after the loop body, then control is tranferred
    // back to cond-expression
    // *******************************************************************
    // The for loop expressions are all optional!
    // *******************************************************************

    // Jump Statements - break, continue
    // continue - jump to the next iteration - aka, goto the last line of the loop body
    // break - escape the enclosing loop - aka, goto the statement immediately after the loop
    
    int outer_sum = 0;
    int inner_sum = 0;

    for(int h = 0; h < 10; ++h) {
        if(h == 4) continue;
        outer_sum += 1;
        for(int j = 0; j < 10; ++j) {
            if(j==2) break;
            inner_sum += 1;
        }
    }
    printf("Outer sum: %d\nInner sum: %d\n", outer_sum, inner_sum);

    // Jump Statement - goto
    // goto label; a label is an identifier followed by a colon
    // Unconditional jump. Labels have function scope.
    goto tricky; // We haven't defined tricky yet! But this is fine due to function scope.
    outer_sum = 0;
    tricky:
        printf("Outer sum is %d\n\n", outer_sum);
}

void static_demo() {
    static int called = 1;
    printf("This function has been called %d times.\n", called++);
}

// Introduce storage-class specifiers (just static for now)
void storage_class_specifiers() {
    for(int i = 0; i < 3; ++i) static_demo();
    printf("\n");
}

#include <math.h> // Common math operations outside the usual operators
//#include <stdlib.h> // abs found in here, along with others
// Need to add -lm flag if using math.h functions (-LinkMath)

// Introduce variable declaration and arithmetic in C
void maths() {
    char my_char = 'E'; // Single quotes required for single char literals
    my_char = 69; // When assigning an int, the ASCII character set is used:
                  // https://en.wikipedia.org/wiki/ASCII#Character_set

    // Since characters are numeric types, we can do math on them
    // The 4 basic operations are available: addition (+), subtraction (-), 
    // multiplication (*), and division (/), as well as modulo (%)

    printf("my_char    is %c\nmy_char+10 is %c\nmy_char-10 is %c\n\n", my_char, my_char+10, my_char-10);
    
    char myMultipliedChar = my_char * 10;

    char* mystr = "What happens if you multiply over the limit of char?\nmy_char*10 = %d != %c\n\n";
    printf(mystr, myMultipliedChar, myMultipliedChar);
    // ? in a rhombus is called the replacement character;
    // it is used to represent an unrecognized or unrepresentable 
    // character.

    // Note that doing "my_char*10" in an expression is equivalent to multiplying
    // (char * int); this results in an IMPLICIT widening conversion (widening in
    // terms of bytes) of the result; the result of this expression is an int, NOT
    // a char, like one might expect!

    // While we're here, we can try to show off some undefined behavior, such as
    // modifying a string literal; these live in read-only memory, modifying this
    // is undefined behavior; it might work, it might result in a core dump...
    
    // Undefined behavior
    //char* hello = "Hello\n";
    //hello[0] = 'Y'; // Segmentation fault with gcc 13.2 on x86_64 linux

    // Dividing 2 integers results in truncation towards 0 (remove the mantissa)*
    // *This is not guaranteed in C89
    int my_int = 4;
    int div_result = my_int / 3;
    printf("Division of 4/3 = %d\n", div_result);
    // Adding a .0 to one operand causes the result to return a double
    // (No warning for casting to float)
    float div_result_2 = my_int / 3.0;
    printf("Division of 4/3.0 = %lf\n", div_result_2);

    // Casting (explicitly converting one type to another) is done by putting
    // the name of the type in parentheses behind the value.
    my_int = (int) div_result_2;
    printf("Conversion of %lf to int: %d\n\n", div_result_2, my_int);

    // TODO: determine if/how to show off floats vs. doubles (precision) - common gotchas   

    // Increment and decrement operatouses rs are also available
    // Before the variable == pre(in/de)crement -> variable changes BEFORE evaluation
    // After the variable == post(in/de)crement -> variable changes AFTER evaluation

    // Common math operations - floor/ceiling, abs, pow, trig functions
    float my_float = -6.34;
    // Notice ceil(x) always goes towards 0 in terms of magnitude
    printf("ceil(%.2f) = %.2f; floor(%.2f) = %.2f\n", my_float, ceil(my_float), my_float, floor(my_float));
    printf("fabs(%.2f) = %.2f; pow(%.2f, 2) = %.2f\n\n", my_float, fabs(my_float), my_float, pow(my_float, 2));
}

#include <stddef.h>

// Introduce pointers, Dos and Don'ts, gotchas
void pointers() {
    // Pointers hold a memory address. They are declared with a * next to the type.
    // Whitespace doesn't matter, an int pointer would be declared int* x or int * x or int *x.
    // Whatever you do just please be consistent!
    int x = 10;
    int* ptr = &x; // Do: initialize pointers when declared

    // If you want access to the value stored at the address held by the pointer, 
    // you must use the dereference operator (e.g. *x). Before doing anything with
    // a pointer, it's best practice to make sure that the pointer isn't null (more
    // important if memory is being allocated).
    if(ptr != NULL) {
        printf("ptr was not null!");
    }
}

void arrays() {

}


// arrays are not pointers stuff
// https://www.c-faq.com/aryptr/index.html



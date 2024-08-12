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
void memory();
void aggregates(); 
void enums();

// Example of a function definition. After the (parameters), the entire function
// is contained between brackets {}.
int main(int argc, char* argv[]) {
    // Each statement (usually a line) ends with a semicolon.
    types(); maths(); pointers(); arrays();
    operators();
    statements();
    storage_class_specifiers();
    memory();
    aggregates();
    enums();
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
    // Declare a pointer with typename* identifier. Some prefer typename *identifier
    // or even type * identifier. Just be consistent with your project's practices.
    int x = 10;
    printf("x is %d\n", x);

    // What the heck is a pointer anyway? Pointers are just memory addresses!
    // Retrieve what's held at the memory address (the value) with the *dereference operator.
    int* ptr = &x; // Do: initialize pointers when declared
    printf("Created int* that points to x.\n");

    // Good practice to check that a pointer isn't NULL... usually 
    if(ptr != NULL) {
        printf("The value held at %p is %d\n", (void*) ptr, *ptr);
        // Need explicit cast to void* when using %p
    }
    else fprintf(stderr, "Error: ptr is NULL.\n");

    // Don't: try to dereference an uninitialized pointer!
    //int* badPtr;             // warning: unused variable
    //printf("%d\n", *badPtr); // error: badPtr is used uninitialized

    // Since our pointer ptr has the address of x, we can modify x without
    // using the variable x at all.
    *ptr = 20;
    printf("The value held at %p is %d\n", (void*) ptr, *ptr);
    printf("x is %d\n", x); // x was changed to 20
    // We can pass our local variable ptr into further functions if we want and
    // modify it as we please. But ptr's lifetime only exists until the end of 
    // this function. If this function were to return the int* ptr that points
    // to a local variable, it will no longer be pointing to any valid data.
    // This is an example of a dangling pointer.

    // In other words, if we're going to keep adding on to the stack with more
    // functions, ptr's lifetime hasn't ended. But as soon as this function,
    // pointers(), is popped off the stack, ptr will not hold a valid memory
    // location (since x's address is no longer in use)

    // We can create pointers to pointers (as nested as you want)
    int** ptrToPtr = &ptr;

    if (ptrToPtr != NULL && *ptrToPtr != NULL) {
        printf("Value accessed via ptrToPtr: %d\n\n", **ptrToPtr);
    }

    // Pointers are a way to get around C using pass-by-value for functions
}

void arrays() {
    // Arrays are a contiguous block of memory, a sequence of objects with 
    // the same type. An array's size is (usually) fixed.
    
    // Some content here derived from Arrays are not pointers:
    // https://www.c-faq.com/aryptr/index.html
    // It is often useful to think of arrays as simply pointers, and keep
    // in mind the differences when relevant. Remember that C is more or 
    // less an abstraction of Asssembly language :) 
    
    // Arrays may have a constant known size, an unknown size, or a variable size*.
    // *Variable-length arrays (VLAs) were introduced in C99, not covered here.

    // Array indexing done with the subscript operator[]
    // Anything you can do with array subscripting, you can also do with pointers
    // Indexing starts from 0
    // C does no bounds checking; it is your responsibility to prevent this.
    // Most times when going out of bounds it is due to being off by 1;
    // typically the program crashes with a segmentation fault.

    // Several ways to initialize an array:
    char str[] = "hello"; // -> char[6]: 'h', 'e', 'l', 'l', 'o', '\0'
                          // \0 is the null-terminator for strings that
                          // signifies their end. Often need to consider
                          // this character when using strings in functions
    int nums[] = { 2, 4, 8, 16, 32 }; // -> int[5]
    int muns[5] = { 3, 9, 27 }; // Partial initialization is ok too
    int my_nums[10]; // Ok to declare first and initialize later
    
    // Set array values using the subscript operator
    for(int i = 0; i < 10; ++i) {
        my_nums[i] = i*4;
    }

    // See array's contents
    for(int i = 0; i < 6; ++i) printf("%c", str[i]);
    printf(" from char[]\n");
    for(int i = 0; i < 5; ++i) printf("%d ", nums[i]);
    printf(" (nums[5])\n");
    for(int i = 0; i < 5; ++i) printf("%d ", muns[i]);
    printf(" (muns[5])\n");
    // We didn't initialize every value in muns! This is risky, as there
    // could be *anything* at those uninitialized memory addresses; 
    // typically in a debug build, these values are initialized to 0, but
    // this is not guaranteed.
    for(int i = 0; i < 10; ++i) printf("%d ", my_nums[i]);
    printf("\n\n");

    // Arrays are pointers?
    printf("Are arrays pointers?\n");
    int* ptr = nums;
    printf("int* ptr = nums\nptr  == %p\nnums == %p\n", (void*) ptr, (void*) nums);
    // Subscripting appears to be shorthand for pointer arithmetic
    printf("&ptr[2] == %p\n ptr+2  == %p\n\n", (void*) &ptr[2], (void*) (ptr+2));
    printf("nums[2] == *(nums+2): %d == %d\n", nums[2], *(nums+2));
    // Notice how the addresses jump by i * sizeof(int)

    // As formal function parameters, arrays are equivalent to pointers.
    // Arrays can't be formal function parameters per se; they are allowed for
    // convenience/clarity but are turned into pointers by the compiler
    // (But you can still operate on that pointer like an array in the function)
    // This conversion is not recursive, so if you pass an array of arrays
    // to a function expecting a pointer-to-a-pointer, you may run into trouble.

    // 0 is the only case where pointers and integers are interchangeable
    // The constant NULL is implementation-defined, but it is often the integer
    // 0, or (void*) 0. As of C23 (if your compiler supports it), NULL can
    // (and should), where possible, be replaced with nullptr, which is
    // (void*) 0 for all implementations.

    // Arrays are not pointers!
    char message_arr[] = "hello"; // Individual characters can be changed
    char* message_ptr = "hello"; // Points to string constant - chars can't be changed
    printf("message_arr[] == message_ptr: %d\n\n", message_arr == message_ptr); // 0

    // For multi-dimensional arrays, the typical approach is to use arrays of pointers
    // But arrays of arrays are valid too:
    int arrOfArrs[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    // Notice it's [rows][cols] aka row-major; some languages are col-major
    // "Really" this is a 1D array whose elements are also arrays
    // You will want to make sure any functions you pass a 2D array to includes
    // the number of cols to prevent going out of bounds
    printf("Addresses of elements in arrOfArrs:\n");
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 3; ++j) {
            printf("Address of arrOfArrs[%d][%d]: %p\n", i, j, (void*) &arrOfArrs[i][j]);
        }
    }
    printf("\n");

    // Arrays of pointers means each pointer (row) can have a different length,
    // which may be useful.
    int* arrOfPtrs[] = { muns, nums, my_nums };
    int lengths[] = { 3, 5, 10 }; // lengths of ptrs in arrOfPtrs

    // Unlike multi-dimensional arrays, the memory addresses are not contiguous
    printf("Addresses of elements in arrOfPtrs:\n");
    for (int i = 0; i < sizeof(arrOfPtrs) / sizeof(arrOfPtrs[0]); ++i) {
        for (int j = 0; j < lengths[i]; ++j) {
            printf("Address of arrOfPtrs[%d][%d]: %p\n", j, i, (void*) &(arrOfPtrs[i][j]));
        }
    }
    // Notice sizeof(arrOfPtrs) / sizeof(arrOfPtrs[0]) - effectively gets us the
    // length of the array. Only applicable to array types.

    // Arrays are not modifiable lvalues; they can't appear on the lhs of 
    // the assignment operator unless they are members of structs
    //nums = muns; // error: assignment to expression with array type

    // Arrays are not pointers! 
    // Array indexing == pointer arithmetic
    // See this page for more details: https://www.c-faq.com/aryptr/index.html
    // Referencing an array object in an expression implicitly "decays" to a pointer
    // during compilation with 3 exceptions:
    // 1. The array is the operand of sizeof
    // 2. The array is the operand of &
    // 3. The array is a char array initialized by a string literal
}

#include <stdlib.h>

// Introduce memory allocation / freeing
void memory() {
    // The size of the stack is limited by default (limits memory usage).

    // Passing pointers to local variables that are needed after popping off 
    // the stack results in a dangling pointer - what if we need that data?

    // What if we need a very large variable that takes up a lot of space, 
    // or severely limits our free space in the stack?

    // These are perfect opportunities to use dynamically-allocated memory,
    // which is placed on the heap. There are several functions available for 
    // this. We will only cover the basics here.

    // It is crucial that all dynamically-allocated memory is later freed,
    // or else you have created a memory leak. This is most especially a 
    // problem in long-lived programs, where the memory usage grows over time
    // and eventually crashes.

    // Allocate memory - malloc, calloc, realloc
    const int array_size = 1024 * sizeof(int);
    int* nums = malloc(array_size);
    // You may see people cast the result of malloc, since it returns void*.
    // This is not recommended, as it is repetitive and it can cause subtle
    // bugs. It is also not necessary; void* is implicitly promoted to any
    // other pointer type.
    
    // ALWAYS check the result of the requested memory allocation
    if(nums == NULL) {
        fprintf(stderr, "Failed to allocate memory for nums\n");
        exit(1);
    }
    // else not usually done but may be useful in cases of logging/debugging
    else {
        fprintf(stdout, "Successfully allocated %d bytes of memory for nums\n", array_size);
    }

    // Recommended best practice: use the variable you're declaring in the
    // malloc call rather than repeating yourself. Prevents errors for when
    // you refactor down the line.
    int* muns = malloc(sizeof *muns * array_size);
    if(muns == NULL) {
        fprintf(stderr, "Failed to allocate memory for muns\n");
        exit(1);
    }
    else {
        fprintf(stdout, "Successfully allocated %d bytes of memory for muns\n", array_size);
    }

    // Free the memory once we're done with it. Management becomes challenging
    // when heap variables may be needed by other functions, determining when
    // they are no longer needed and where to free them can be difficult.
    free(nums);
    free(muns);

    // calloc - "clean alloc" - separate how many elements from the size of your type;
    // initializes each element to 0.
    nums = calloc(array_size, sizeof(int));
    if(nums == NULL) {
        fprintf(stderr, "Failed to allocate memory for nums\n");
        exit(1);
    }

    // realloc - "reallocate" - free the memory pointed to by the pointer, reallocate
    // a new chunk of memory for the given number of bytes, and return the result.
    // realloc will retain the data in the original pointer where it can; truncates
    // for smaller block sizes. If it fails, it will return NULL and the original
    // pointer will be lost.
    nums = realloc(nums, sizeof *nums * (array_size/2));
    if(nums == NULL) {
        fprintf(stderr, "Failed to allocate memory for nums\n");
        exit(1);
    }
    free(nums);
}

#include <string.h> // for strncpy (String Copy N characters)

// Structs can hold various data types. They are called records in some languages.
// They can be declared within functions to limit their scope as necessary
// Like an array, the data is contiguous in memory (though there may be padding
// as necessary).
// Structs can be forward-declared just like functions.
// Subscripting is not valid for structs, but a pointer to a struct, after conversion,
// is the same as a pointer to its first member
struct Employee {
    int id;
    char name[50];
    float salary;
}; // Don't forget the semicolon (just like array initialization lists)

// Structs are commonly typedef'd to hide implementation details and simplify
// pointer syntax.
typedef struct {
    int id;
    char username[30];
    char password[30];  // Please don't store passwords as plaintext :)
    float balance;
} Account;
void Account_init(Account* account, int id, const char* username, const char* password, float balance);

// With typedef'd structs you get usage syntax that somewhat resembles
// object-oriented programming (OOP), but there are limitations; you cannot
// define functions inside structs (methods) as you would with a class.
// There are no access specifiers - C does not support OOP!

// It's a good idea to follow some kind of naming convention for struct-associated
// functions, since C does not have namespaces or scopes for functions.
void Account_init(Account* account, int id, const char* username, const char* password, float balance) {
    account->id = id;
    strncpy(account->username, username, sizeof(account->username) - 1);
    account->username[sizeof(account->username) - 1] = '\0'; 
    strncpy(account->password, password, sizeof(account->password) - 1);
    account->password[sizeof(account->password) - 1] = '\0';
    account->balance = balance;
}

// Unions are more niche than structs; the idea is, this container can hold ONE
// of its members at a time. They all share the same memory space
// If you assign the float, then the int, the float data is overwritten, since the
// memory space is shared.

// Outside of very memory-constrained situations, unions are useful when you don't
// know the type of some data to be read in advance, or you need a constrained way
// to reinterpret the same data as another type; in the latter case, since C99, 
// when setting one member and reading from another, an implementation-defined
// object reinterpretation (i.e. casting) occurs.

// Subscripting is not valid for unions, but a pointer to a union, after conversion,
// is the same as a pointer to any of its members. 

union Data {
    int anInt;
    float aFloat;
    char aChar;
};

// Introduce structs/unions
void aggregates() {
    // Starting in C99, structs can be initialized much like arrays
    struct Employee emp1 = {
        .id = 1, .name = "John Doe", .salary = 30000.0 
    };

    // Update struct members with the . operator (-> operator for pointers)
    emp1.id = 13;
    //emp1.name = "Jon Dough"; // error: assignment to expression with array type
    printf("Employee emp1 is named %s\n", emp1.name);

    Account acc;
    Account_init(&acc, 16, "Bob", "Password123", 110.110);
    printf("%s's account balance is %.2f\n", acc.username, acc.balance);

    int num = 64;
    union Data myData;
    myData.anInt = num;

    printf("Union Data (int, float, or char) initialized with int: %d; read as char: %c\n\n", num, myData.aChar);
}

// Introduce enums
void enums() {
    // In statements(), we used a switch statement to print the days of the week:
    //switch(day) {
    //     case 1:
    //         printf("Sunday\n");
    //         break; 
    //     case n:
    //         ...
    //     default:
    //         printf("Invalid day\n");
    //         break;
    // }
    // An enum allows us to use user-defined names to use in place of
    // integers (until C23; since C23, enums can be other integral types.
    
    // Starts at 0 by default. Increment by 1 for each entry.
    // Expressions are allowed, and so are duplicate numeric values.
    
    typedef enum {
        SUNDAY = 1,
        MONDAY,     
        TUESDAY,    
        WEDNESDAY,  
        THURSDAY,
        FRIDAY,
        SATURDAY
    } Day;

    Day today = MONDAY;

    printf("Today is ");

    switch(today) {
        case SUNDAY:
            printf("Sunday\n");
            break; 
        case MONDAY:
            printf("Monday\n");
            break;
        case TUESDAY:
            printf("Tuesday\n");
            break;
        case WEDNESDAY:
            printf("Wednesday\n");
            break;
        case THURSDAY:
            printf("Thursday\n");
            break;
        case FRIDAY:
            printf("Friday\n");
            break;
        case SATURDAY:
            printf("Saturday\n");
            break;
        default:
            printf("Invalid day\n");
            break;
    }
}

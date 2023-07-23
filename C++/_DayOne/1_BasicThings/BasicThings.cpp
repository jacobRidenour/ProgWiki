#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

/* Operators: rather than reading L->R, * & / are given higher priority */
/* Number systems: hex, dec, bin */
int decimal = 255;
int binary = 0b111111;
int hexadecimal = 0xff;

/* Boolean data type exists; like C, !0 == true */
/* Logical operators as expected: &&, ||, !; can use in var initialization */
bool flag = 6;  //!0 = true
bool anotherFlag = 10 > 5;

int main() {
    int num = 4;
    int num2 = 5;

    //By default, no protection against over/underflow
    int minValue = numeric_limits<int>::min();
    int maxValue = numeric_limits<int>::max();

    const double pi = 3.14; //doubles are default for FP numbers; force float with f at the end
    float myFloat = 3.14f;

    int x = num * num2;
    double y = x + 0.54;

    /* Explicit casting REQUIRED when downcasting but not upcasting */
    int z = (int) y;                //C-style casting; avoid, errors caught at runtime
    int z2 = static_cast<int>(y);   //C++-style casting; preferred, errors caught at compilation

    /* Arrays, loops, and their secrets */
    int preBuilt[] = {1, 2, 3, 4, 5, 6};
    int nums[10];   //Notice: didn't need to allocate space vs. C
    /* for loop */
    for(int i = 0; i < 10; i++) {
        nums[i] = i+1;
        std::cout << "nums[" << i << "] = " << nums[i] << "\n";
    }
    /* Range-based for loop */
    std::cout << "Contents using for-each loop: " << "";     //***Starts at 1, watch for OOB***
    for(int i : nums) {     //if type can be inferred, use auto
        if(i-1) { //Skip the first element since i-1 == 0
            std::cout << "[" << i-1 << "]: " << nums[i-1] << ", ";
        }
    } //useful for vectors/lists 
    std::cout << "x = " << x << std::endl; //print 'x =' and the value of x
    std::cout << std::endl;
    /* break, continue are legal in loops */

    /* Print the alphabet */
    char c = 'a';           //c = 97 is also valid ('a')
    while(c <= 122) {       //As expected, chars represented as numbers
        std::cout << c;
        c++;
    }
    std::cout << std::endl;
    char d = 65;            //Compilation error if variables are redeclared but no warning in VSCode
    do {
        std::cout << d;
        d++;
    } while (d < 91);
    std::cout << std::endl << std::endl;


    /* Conditional operator example */
    /* Condition: ? (true value) : (false value) */
    int g, h = 10;
    int var{};  //or var = {} ; default constructor
    std::cout << "Classic style; value of var is ";
    if(h < 10) {
        var = 30;
        //std::cout << var << std::endl;
        std::cout << var << "\n";
    }
    else {
        var = 40;
        std::cout << var << std::endl;
    }
    std::cout << "Conditional operator; value of var is ";
    var = (h < 10) ? 30 : 40;

    //const pointer vs. pointer to const
    //const pointer - can't change memory address that ptr points to
    //pointer to const - can't change contents at memory address


    std::cout << var << std::endl;
    return 0;
}

//Stream manipulators: setw, fixed, setprecision, boolalpha, left, right
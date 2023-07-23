#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;
// If not using namespace std, have to call functions with std::funcname e.g. std::cout
// Symbols: classes, functions, variables... use different namespaces to allow two symbols with the same signature
// i.e. namespaces let you use functions with the same name in different contexts
// In C (which has no namespaces), a library's functions may all start with libName_func to prevent potential naming conflicts
// Ideally: keep them in a small scope, NEVER in header files
// Calling a function - namespace1::print() namespace2::print() etc.
// Classes are a bit like namespaces
// Namespace aliases - useful for nested namespaces; i.e. namespace ns = std;

/*  NOTES ABOUT FUNCTIONS

    Like C: pass-by-value (default); pass by reference with & operator
    Like C: function declaration, invocation
    Unlike C: function overloading
    Header files can end with .h or .hpp; recommend the latter for clarity in projects with both languages
    New namespaces may be necessary to prevent name collisions
    
*/

/* DECLARATIONS */
void testing();
void naiveSquare(int x);
void square(int& x);
int circleArea(int& rad);
void incomeTax(int& inc);
void readInput();
void braceMagic();
void numberSystems();
void randomNumbers();
/* END DECLARATIONS */

int main() {
    testing();
    int income = 95000;
    incomeTax(income);
    cout << "\n\n";
    //readInput();
    braceMagic();
    numberSystems();
    randomNumbers();

    return 0;
}

void testing() {
    int x = 2;
    naiveSquare(x);
    cout << "x = " << x << endl;
    square(x);      //Unlike C: don't need to create a pointer or use the & operator when sending to the function
    cout << "x = " << x << endl;
    cout << "Area of a circle with radius " << x << " is " << circleArea(x) << "\n\n";
}

void incomeTax(int& inc) {
    float interestRate = 3.67F;     //always add F at the end for floats or they will be treated as doubles (same situation for long/int)
    auto lastYearIncome = 92000L;   //'auto' keyword - with the L, figures it's a long, otherwise, assumes int.
    const double countyTax = 0.02;
    const double stateTax = 0.05;
    cout << "Taxes owed for yearly income of $" << inc << "\n--------------------------------------" << endl;
    cout << "County tax owed: $" << countyTax * inc << endl;
    cout << "State tax owed: $" << stateTax * inc << endl;
}

void naiveSquare(int x) {
    x *= x;
}

void square(int& x) {
    x *= x;
}

int circleArea(int& rad) {
    const double pi = 3.14159;
    square(rad);
    int result = (int) pi * rad;
    return result;
}

void readInput() {
    cout << "Type something, anything: ";
    string inputVar;
    cin >> inputVar; //assign user's input to inputVar (follow the direction of the >>);
    cout << "You entered: " << inputVar << "\n\n";

    int x, y;
    cout << "Enter values for x and y: ";           //Can enter the number on individual lines or delimit with space
    cin >> x >> y;                                  //Read something, put it in x, read another thing, put it in y.
    int result = x + y;
    cout << "\nThe sum of x and y is " << result;    //NOTE: no errors if you enter garbage data! Always check user input
}

void braceMagic() {
    int num;            //Uninitialized, garbage data
    cout << "\nUninitialized integer: " << num;
    int number {};      //Braces check to make sure the data initialized is compatible; if no value, variable initialized to 0.
    cout << "\nInitialized integer: " << number << endl;
}

void numberSystems() {
    //Use unsigned keyword to disallow negative values; can be a troublemaker, be careful.
    int binNum = 0b11111111;
    int decNum = 255;
    int hexNum = 0xFF; 
    cout << "Binary: " << binNum << ", decimal: " << decNum << ", hex: " << hexNum << endl;

    //Narrowing conversion
    int bigNum = 999'999;
    short smallBox = bigNum;    //Legal but can cause problems
    cout << "Big number: " << bigNum << " in a small container: " << smallBox << endl;

    //Widening conversion - not an issue
    short smallNum = 16535;
    int bigBox = smallNum;
    cout << "Small number: " << smallNum << " in a big container: " << bigBox << endl;
}

void randomNumbers() {   
    srand((unsigned) time(0));                     //random # seeded with time in seconds since 1970-01-01, equivalent to time(0), preps rand() for a random #
    cout << "Random number: " << rand() % 1024 << endl;     //random number 0-1023
}
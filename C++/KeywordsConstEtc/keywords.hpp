/***************************************/
/* Covered Keywords:                   */
/* - func() const                      */
/* - const func()                      */
/* - constexpr (var/func())            */
/* - constinit (var)                   */
/* - consteval (func())                */
/* - inline func()                     */
/* - static (var/func())               */
/*                                     */
/* These terms have distinct but       */
/* easily confused meanings. Meant to  */
/* be a quick reference on what makes  */
/* each term unique                    */
/***************************************/

using uint = unsigned int;

template<typename T>
class Matrix {
private:
    constexpr uint DEFAULT_SIZE = 3;
    /* constexpr var */
    // -> The variable can be evaluated at compile time
    // -> This variable could be static, as only 1 instance of this variable is necessary

    constinit uint MAX_SIZE = 400;
    /* constinit var */
    // -> The variable is initialized at compile-time OR the start of the program if dynamic initialization is not possible
    // -> The variable requests static initialization
    // -> Useful for: achieving deterministic initialization; cases where you want to ensure certain variables are initialized
    //    before any dynamic initialization takes place
    // -> CANNOT be used in function variables
    // -> Using "static constinit var" is redundant
    // -> Using "constinit constexpr var" is redundant

protected:
    uint _size;
    uint _rows;
    uint _cols;
    std::vector<T> _data;
public:
    static uint instance_count;
    /* static var */
    // -> Class variable or global variable
    // -> The variable has internal linkage and is shared among:
    //      -> ALL instances of the class or
    //      -> ALL the functions within the file
    // -> In this instance, we can keep track of how many Matrix objects have been created
    // -> We could have this variable as static constinit too

    Matrix(uint rows, uint cols) : rows(_rows), cols(_cols) { _data.resize(_rows*_cols);  instanceCount++; }

    constexpr uint rows() { return _rows; }
    /* constexpr func() */
    // -> The function can be evaluated at compile time if its args are compile-time constants
    // -> e.g. Matrix<int> m1; constexpr int default_row_numbers = m1.rows(); -> this line would be evaluated at compile time
    // -> Before C++17, function must consist of a single return statement 
    // -> Before C++17, parameters & return type must all be of literal types
    // -> C++20 relaxed some of the function body restrictions & expanded support for STL types/objects as long as requirements are met
    //    and the operations can be evaluated at compile time
    // -> Optimally this function would also be inline and func() const
    
    template<typename U = T>
    consteval Matrix<U> multiply(const Matrix<U>& other) const {
        static_assert(rows == 2 && cols == 2, "Matrix multiplication is supported only for 2x2 matrices.");

        Matrix<U> result(2, 2);
        result[0][0] = data[0] * other[0][0] + data[1] * other[1][0];
        result[0][1] = data[0] * other[0][1] + data[1] * other[1][1];
        result[1][0] = data[2] * other[0][0] + data[3] * other[1][0];
        result[1][1] = data[2] * other[0][1] + data[3] * other[1][1];

        return result;
    }
    /* consteval func() */
    // -> The function must be evaluated at compile-time *whenever possible*
    // -> e.g. Matrix<int> m1, m2; m1.fill() m2.fill(); constexpr Matrix<int> result = m1.multiply(m2); -> this line would be evaluated at compile time
    // -> Enforces that the function is only callable in constant expressions & cannot be called at runtime
    // -> Can be useful for ensuring certain computations are performed at compile-time rather than runtime

    inline uint size() const { return _size; }
    /* func() const */
    // -> ONLY applicable to member functions of a class
    // -> This member function promises NOT to modify the state of the object on which it is called
    
    /* inline func() */
    // -> Compiler HINT for optimization. If approved by compiler:
    // -> When this function is called, instead of adding it to the stack, the calling line is expanded to be the function itself
    // -> Reduces overhead when applied
    // -> Best used with small (~1-2 lines), frequently used functions
    // -> NOTE: does not affect linkage; if a func is defined in a header and used in multiple translation units
    //      -> (translation unit = result of compiling a source file along with the headers it in/directly includes)
    //      -> if a func is defined in a header and used in MULTIPLE translation units, it can result in multiple function definitions
    //      -> ... this violates the One Definition Rule (ODR). In such cases, it may be best to combine inline with static.

    const T& get_element_at(uint row, uint col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Subscript out of range.");
        }

        return data[row * cols + col];
    }
    /* const func() */
    // -> Return value of this function is constant
    // -> Function will not modify the value that it returns
    // -> Not common in practice; generally used with pointer/reference return types

    static Matrix<T> transpose(const Matrix<T>& matrix) {
        uint rows = matrix._rows;
        uint cols = matrix._cols;

        Matrix<T> result(cols, rows);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[j][i] = matrix[i][j];
            }
        }
        return result;
    }
    /* static func() */
    // -> Member function belongs to the class itself rather than a specific instance of the class.
    // -> Can be called without an object
    // -> Best used for utility/helper functions that are related to the class but don't require access to instance-specific data

    void fill(T value) {
        static int fill_count = 0;
        fill_count++;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                (*this)[i][j] = value;
            }
        }
    }
    /* static var */
    // -> Not limited to being used in member functions; can be used in any function
    // -> This variable is only initialized ONCE even if you call the function many times
    // -> This variable is persistent across multiple invocations of the function
    // -> This variable can be used to keep track of how many times the function has been called
};
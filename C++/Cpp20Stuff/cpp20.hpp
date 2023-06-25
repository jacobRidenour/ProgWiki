#include <compare>
#include <string>
#include <coroutine>

namespace cpp20 {

    // Define a concept for even numbers
    template<typename T>
    concept EvenNumber = std::integral<T> && std::is_same_v<decltype(T() % 2), decltype(T())>;
    /* Concept */
    // Specifies some set of requirements that a template type must satisfy to be considered valid
    // In this case, the type must be an integral type (standard integer types like int, long, also char)
    // Other reasons to use Concepts
    // -> Improved readability/expressiveness on templated functions/classes
    // -> Better compile-time error messages
    // -> More robust generic programming

    // Function template constrained by the EvenNumber concept
    template<typename T>
    void printEvenNumber(T number) {
        if constexpr (EvenNumber<T>) {
            if (number % 2 == 0) {
                std::cout << "Even Number: " << number << std::endl;
            }
            else {
                std::cout << "Invalid input: " << number << std::endl;
            }
        }
        else {
            std::cout << "Invalid input: " << number << std::endl;
        }
    }

    template <typename T>
    concept IntegralNumber = std::integral<T>;

    template <IntegralNumber T>
    void performOperation(const T& value) {
        // Define a lambda function with a template parameter list
        auto helperFunction = []<typename U>(U & element) requires IntegralNumber<U> {
            int i = element;
            i+=10;
            std::cout << "\nIncremented element: " << i << std::endl;
        };

        // Call the lambda function with the provided value
        helperFunction(value);
    }

    //Demonstration of the spaceship operator
    class MyClass {
    private:
        int value;
        [[no_unique_address]] int value2;
        bool flag;

        /* no_unique_address */
        // -> this non-static data member of a class/struct does not require a unique address
        // -> allows compiler to optimize the layout by potentially reusing the storage of that
        //    member with other members
        // -> main benefit: reducing memory footprint of the class/struct. especially useful when
        //    dealing with empty classes or when using various forms of type-based optimization,  
        //    such as tag dispatching or type erasure
        // -> cannot be used with base classes or virtual functions
        // -> using incorrectly can lead to undefined behavior


    public:
        MyClass(int val1, int val2) : value(val1), value2(val2), flag(true) {}

        void doSomething() {
            [[likely]] if (flag) {
                // This is the branch most likely to be taken
                std::cout << "Flag is likely true" << std::endl;
            }
            else {
                std::cout << "Flag is unlikely true" << std::endl;
            }
        }
        /* likely, unlikely */
        // -> compiler hints regarding the likelihood of a particular branch being
        //    taken in a conditional statement.
        // -> They can only be applied directly before an "if" or "switch" statement

        auto operator<=>(const MyClass& other) const {
            return value <=> other.value;
        }
        /* Spaceship Operator <=> */
        // -> 3-way comparison operator
        // -> concised/standardized way to compare 2 objects and determine their relative ordering
        // -> returns a std::strong_ordering value that indicates the result of the comparison
        // If op1 == op2 return std::strong_ordering::equal
        // If op1 < op2 return std::strong_ordering::less
        // If op1 > op2 return std::strong_ordering::greater
        // Rust has a similar operator (PartialOrd)
        // Perl also has this same operator, and returns -1, 0, or 1 based on the result
        // Java has a similar concept with compareTo() for classes that implement Comparable

    };


    //Better example of no_unique_address
    struct Person {
        std::string name;
        int age;
    };

    struct Device {
        unsigned int cores;
        unsigned long memory;
        std::string name;
    };

    // Tag types
    struct PersonTag {};
    struct DeviceTag {};

    // Tag erasure (not unique to C++20 but shows a use case of no_unique_address
    class ErasedObject {
    private:
        struct Base {
            virtual ~Base() = default;
            virtual void print() const = 0;
        };

        template <typename T>
        struct Derived : Base {
            // no_unique_address example
            // reduces the size of each Derived object stored inside ErasedObject
            [[no_unique_address]] T data;

            explicit Derived(T value) : data(std::move(value)) {}

            void print() const override {
                if constexpr (std::is_same_v<T, Person>) {
                    std::cout << "Person: " << data.name << " is " << data.age << " years old" << std::endl;
                }
                else if constexpr (std::is_same_v<T, Device>) {
                    std::cout << "Device: " << data.name << "\nCores: " << data.cores
                        << "\nMemory (MB): " << data.memory << std::endl;
                }
                else {
                    std::cout << "Unknown type" << std::endl;
                }
            }
        };


        std::unique_ptr<Base> object;

    public:
        template <typename T>
        ErasedObject(T value) : object(std::make_unique<Derived<T>>(std::move(value))) {}

        void print() const {
            object->print();
        }
    };

    // Coroutine example
    struct CountCoroutine {
        struct promise_type {
            int current;

            CountCoroutine get_return_object() {
                return CountCoroutine{ std::coroutine_handle<promise_type>::from_promise(*this) };
            }

            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }

            std::suspend_always yield_value(int value) {
                current = value;
                return {};
            }

            void return_void() {}

            void unhandled_exception() { std::terminate(); }
        };

        std::coroutine_handle<promise_type> handle;

        explicit CountCoroutine(std::coroutine_handle<promise_type> handle) : handle(handle) {}

        ~CountCoroutine() {
            if (handle) {
                handle.destroy();
            }
        }

        bool move_next() {
            handle.resume();
            return !handle.done();
        }

        int current() const {
            return handle.promise().current;
        }
    };

    CountCoroutine countTo(int number) {
        for (int i = 1; i <= number; ++i) {
            co_yield i;
        }
    }
    /* Coroutines */
    // -> purpose: simlify the development of async tasks by abstracting away
    //    the complexities of callback-based / state-machine-based approaches
    // -> construct that lets you write code that can be suspended and resumed
    //    at specific points
    // -> a way to write async code in a more sequential/readable manner, looks
    //    similar to sequential code
    // -> co_yield lets the coroutine yield a value back to the caller and
    //    suspend execution until the next invocation
    // -> uses a combination of compiler-generated state machines & specialized
    //    functions (promise objects) to manage the suspension / resumption of
    //    execution.
    //  -> promise object encapsulates the state of the coroutine, provides methods
    //     for handling suspension/resumption logic
    //  -> handle represents the state of the coroutine & allows you to control
    //     its execution (resuming, destroying)



}
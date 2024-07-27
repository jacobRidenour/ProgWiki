#include <iostream>
#include <iomanip>
#include <vector>
#include "datastructures.hpp"

/* Function Declarations */
void demoMatricesAndCubes();
void demoIndexedBST();
void demoOpOverload();

int main() {
    // Generic operator overloading showcase
    demoOpOverload();
    std::cout << "\n";

    // More complicated operator overloading showcase [][]
    demoMatricesAndCubes();
    std::cout << "\n";

    // Example of a structure where you might want to use operator overloads on its elements
    demoIndexedBST();

    return 0;
}

void demoMatricesAndCubes() {
    Matrix<float> m(3, 6);
    m.fill(0.4);
    std::cout << "Contents of the Matrix: " << std::endl;
    m.print();

    std::cout << "\n\nContents of the Cube: " << std::endl;
    Cube<float> c(2, 4, 6);
    c.fill(0.3);
    c.print();
}

void demoIndexedBST() {
    IndexedBST<int> bst;
    bst.add(5, 0);
    bst.add(3, 1);
    bst.add(8, 2);
    bst.add(2, 3);
    bst.add(4, 4);
    bst.add(7, 5);
    bst.add(9, 6);
    bst.balance();

    bst.print();

    std::cout << "Smallest element: " << bst.getSmallestElement() << std::endl;
    std::cout << "Largest element: " << bst.getLargestElement() << std::endl;

    std::cout << "Search for index 4: ";
    BSTNode<int>* foundNode = bst.searchByIndex(4);
    if (foundNode != nullptr) {
        std::cout << foundNode->data << std::endl;
    }
    else {
        std::cout << "Not found." << std::endl;
    }

    std::cout << "Search for data 7: ";
    foundNode = bst.searchByIndex(7);
    if (foundNode != nullptr) {
        std::cout << foundNode->index << std::endl;
    }
    else {
        std::cout << "Not found." << std::endl;
    }

    std::vector<int> bstVector = bst.toVector();
    std::cout << "BST as vector: ";
    for (const auto& elem : bstVector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    bst.removeByIndex(3);

    bst.print();
}

void demoOpOverload() {
    OpDemo a(5);
    OpDemo b(3);

    // Unary operators
    OpDemo c = +a;
    OpDemo d = -a;

    std::cout << "+a: " << c << std::endl;
    std::cout << "-a: " << d << std::endl;

    // Binary operators
    OpDemo e = a + b;
    OpDemo f = a - b;
    OpDemo g = a * b;
    OpDemo h = a / b;

    std::cout << "a + b: " << e << std::endl;
    std::cout << "a - b: " << f << std::endl;
    std::cout << "a * b: " << g << std::endl;
    std::cout << "a / b: " << h << std::endl;

    // Relational operators
    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;
    std::cout << "a > b: " << (a > b) << std::endl;
    std::cout << "a <= b: " << (a <= b) << std::endl;
    std::cout << "a >= b: " << (a >= b) << std::endl;

    // Function call operator
    int result = a(3);
    std::cout << "a(3): " << result << std::endl;

    // Subscript operator
    a[0] = 10;
    std::cout << "a[0]: " << a[0] << std::endl;

    // Custom new and delete operators
    OpDemo* ptr = new OpDemo(7);
    delete ptr;

    // Custom new[] and delete[] operators
    OpDemo* arr = new OpDemo[2];
    delete[] arr;

}
#ifndef DATASTRUCTURES_HPP
#define DATASTRUCTURES_HPP

#include <vector>
#include <iostream>
#include <iomanip>
#include <stack>
#include <algorithm>

/*
* Class Matrix: store data linearly but access elements like a 2D array
*/
template<typename T>
class Matrix {
private:
    std::vector<T> data;
    int rows;
    int cols;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows * cols);
    }

    // Proxy class for 2D indexing
    class Proxy {
    private:
        Matrix<T>& matrix;
        int row;

    public:
        Proxy(Matrix<T>& matrix, int row) : matrix(matrix), row(row) {}

        T& operator[](int col) {
            return matrix.data[row * matrix.cols + col];
        }
    };

    Proxy operator[](int row) {
        return Proxy(*this, row);
    }

    inline int numRows() const {
        return rows;
    }

    inline int numCols() const {
        return cols;
    }

    void fill(T value) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                (*this)[i][j] = i * cols + j + value;
            }
        }
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols - 1; j++) {  // Corrected index limit
                std::cout << "[" << i << "][" << j << "]: " << std::setw(4) << (*this)[i][j] << " ";
                std::cout << "[" << i << "][" << j + 1 << "]: " << std::setw(4) << (*this)[i][j + 1] << " ";
            }
            std::cout << std::endl;
        }
    }
};

/*
* Class Cube: store data linearly but access elements like a 3D array
*/
template<typename T>
class Cube {
private:
    std::vector<T> data;
    int rows;
    int cols;
    int slices;

public:
    Cube(int rows, int cols, int slices) : rows(rows), cols(cols), slices(slices) {
        data.resize(rows * cols * slices);
    }

    // Proxy class for 3D indexing
    class Proxy2D {
    private:
        Cube<T>& cube;
        int row;
        int col;

    public:
        Proxy2D(Cube<T>& cube, int row, int col) : cube(cube), row(row), col(col) {}

        T& operator[](int slice) {
            return cube.data[(row * cube.cols + col) * cube.slices + slice];
        }
    };

    class Proxy {
    private:
        Cube<T>& cube;
        int row;

    public:
        Proxy(Cube<T>& cube, int row) : cube(cube), row(row) {}

        Proxy2D operator[](int col) {
            return Proxy2D(cube, row, col);
        }
    };

    Proxy operator[](int row) {
        return Proxy(*this, row);
    }

    inline int numRows() const {
        return rows;
    }

    inline int numCols() const {
        return cols;
    }

    inline int numSlices() const {
        return slices;
    }

    void fill(T value) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int k = 0; k < slices; k++) {
                    (*this)[i][j][k] = i * cols + j * rows + k + value;
                }
            }
        }
    }

    void print() {
        for (int k = 0; k < slices; k++) {
            std::cout << "Slice " << k << ":" << std::endl;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols - 1; j++) {  // Corrected index limit
                    std::cout << "[" << i << "][" << j << "][" << k << "]: " << std::setw(4) << (*this)[i][j][k] << " ";
                    std::cout << "[" << i << "][" << j + 1 << "][" << k << "]: " << std::setw(4) << (*this)[i][j + 1][k] << " ";
                }
                std::cout << std::endl;
            }

            std::cout << std::endl << std::endl;
        }
    }
};

/*
* Class BSTNode: Nodes for class IndexedBST, an indexed Binary Search Tree
*/
#include <iostream>
#include <vector>

template <typename T>
class BSTNode {
public:
    T data;
    int index;
    BSTNode<T>* left;
    BSTNode<T>* right;

    BSTNode(T value, int idx)
        : data(value), index(idx), left(nullptr), right(nullptr) {}
};

/*
* Class IndexedBST: Each node contains an index and a value. Contents are accessible by index.
*/
template <typename T>
class IndexedBST {
private:
    BSTNode<T>* root;
    BSTNode<T>* cursor;
    int size;

public:
    IndexedBST() : root(nullptr), cursor(nullptr), size(0) {}

    int getSize() const {
        return size;
    }

    BSTNode<T>* getRoot() {
        return root;
    }

    void add(T data, int index) {
        if (root == nullptr) {
            root = new BSTNode<T>(data, index);
            cursor = root;
        }
        else {
            addHelper(root, data, index);
        }
        size++;
    }

    void addInOrder(T data, int index) {
        if (root == nullptr) {
            root = new BSTNode<T>(data, index);
            cursor = root;
        }
        else {
            addInOrderHelper(root, data, index);
        }
        size++;
    }

    void addPreOrder(T data, int index) {
        if (root == nullptr) {
            root = new BSTNode<T>(data, index);
            cursor = root;
        }
        else {
            addPreOrderHelper(root, data, index);
        }
        size++;
    }

    void addPostOrder(T data, int index) {
        if (root == nullptr) {
            root = new BSTNode<T>(data, index);
            cursor = root;
        }
        else {
            addPostOrderHelper(root, data, index);
        }
        size++;
    }

    void remove(BSTNode<T>* node) {
        root = removeHelper(root, node);
        size--;
    }

    void removeData(const T& data) {
        root = removeHelper(root, data);
        size--;
    }

    void removeByIndex(int index) {
        root = removeHelperByIndex(root, index);
        size--;
    }

    BSTNode<T>* search(BSTNode<T>* node) {
        return searchHelper(root, node);
    }

    BSTNode<T>* searchData(T data) {
        return searchHelper(root, data);
    }

    BSTNode<T>* searchByIndex(int index) {
        return searchByIndexHelper(root, index);
    }

    std::vector<T> toVector() {
        std::vector<T> result;
        result.reserve(size); // Reserve space to avoid frequent reallocations
        collectElements(root, result); // Collect elements into the vector
        std::sort(result.begin(), result.end()); // Sort the vector

        return result;
    }

    T getSmallestElement() {
        if (root == nullptr)
            throw std::runtime_error("Tree is empty.");

        BSTNode<T>* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }

    T getLargestElement() {
        if (root == nullptr)
            throw std::runtime_error("Tree is empty.");

        BSTNode<T>* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

    bool contains(int index) {
        return containsHelper(root, index);
    }

    void print() {
        printHelper(root, "", 0, false);
    }

    void balance() {
        root = balanceNode(root);
    }

private:
    // Function to perform a right rotation
    BSTNode<T>* rotateRight(BSTNode<T>* node) {
        BSTNode<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    // Function to perform a left rotation
    BSTNode<T>* rotateLeft(BSTNode<T>* node) {
        BSTNode<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    // Function to get the height of a node
    int getHeight(BSTNode<T>* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    // Function to get the balance factor of a node
    int getBalanceFactor(BSTNode<T>* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return leftHeight - rightHeight;
    }

    // Function to recursively balance the tree
    BSTNode<T>* balanceNode(BSTNode<T>* node) {
        if (node == nullptr)
            return nullptr;

        int balanceFactor = getBalanceFactor(node);

        // Left-Left case
        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
            node = rotateRight(node);
        }
        // Right-Right case
        else if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
            node = rotateLeft(node);
        }
        // Left-Right case
        else if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        // Right-Left case
        else if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }

        node->left = balanceNode(node->left);
        node->right = balanceNode(node->right);

        return node;
    }

    void collectElements(BSTNode<T>* node, std::vector<T>& result) {
        if (node == nullptr)
            return;

        collectElements(node->left, result);
        result.push_back(node->data);
        collectElements(node->right, result);
    }

    void addHelper(BSTNode<T>* node, T data, int index) {
        if (index < node->index) {
            if (node->left == nullptr) {
                node->left = new BSTNode<T>(data, index);
            }
            else {
                addHelper(node->left, data, index);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new BSTNode<T>(data, index);
            }
            else {
                addHelper(node->right, data, index);
            }
        }
    }

    void addInOrderHelper(BSTNode<T>* node, T data, int index) {
        if (node->left != nullptr) {
            addInOrderHelper(node->left, data, index);
        }
        else {
            node->left = new BSTNode<T>(data, index);
        }
    }

    void addPreOrderHelper(BSTNode<T>* node, T data, int index) {
        if (node->left == nullptr) {
            node->left = new BSTNode<T>(data, index);
        }
        else {
            addPreOrderHelper(node->left, data, index);
        }
    }

    void addPostOrderHelper(BSTNode<T>* node, T data, int index) {
        if (node->right == nullptr) {
            node->right = new BSTNode<T>(data, index);
        }
        else {
            addPostOrderHelper(node->right, data, index);
        }
    }

    BSTNode<T>* removeHelper(BSTNode<T>* node, BSTNode<T>* target) {
        if (node == nullptr)
            return nullptr;

        if (target->index < node->index) {
            node->left = removeHelper(node->left, target);
        }
        else if (target->index > node->index) {
            node->right = removeHelper(node->right, target);
        }
        else {
            if (node->left == nullptr) {
                BSTNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BSTNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode<T>* minRight = findMin(node->right);
            node->data = minRight->data;
            node->index = minRight->index;
            node->right = removeHelper(node->right, minRight);
        }

        return node;
    }

    BSTNode<T>* removeHelper(BSTNode<T>* node, const T& target) {
        if (node == nullptr)
            return nullptr;

        if (target < node->data) {
            node->left = removeHelper(node->left, target);
        }
        else if (target > node->data) {
            node->right = removeHelper(node->right, target);
        }
        else {
            if (node->left == nullptr) {
                BSTNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BSTNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode<T>* minRight = findMin(node->right);
            node->data = minRight->data;
            node->index = minRight->index;
            node->right = removeHelper(node->right, minRight->data);
        }

        return node;
    }

    BSTNode<T>* removeHelperByIndex(BSTNode<T>* node, int index) {
        if (node == nullptr)
            return nullptr;

        if (index < node->index) {
            node->left = removeHelperByIndex(node->left, index);
        }
        else if (index > node->index) {
            node->right = removeHelperByIndex(node->right, index);
        }
        else {
            if (node->left == nullptr) {
                BSTNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BSTNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode<T>* minRight = findMin(node->right);
            node->data = minRight->data;
            node->index = minRight->index;
            node->right = removeHelperByIndex(node->right, minRight->index);
        }

        return node;
    }

    BSTNode<T>* findMin(BSTNode<T>* node) {
        BSTNode<T>* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    BSTNode<T>* searchHelper(BSTNode<T>* node, BSTNode<T>* target) {
        if (node == nullptr || node == target)
            return node;

        BSTNode<T>* result = searchHelper(node->left, target);
        if (result != nullptr)
            return result;

        return searchHelper(node->right, target);
    }

    BSTNode<T>* searchHelper(BSTNode<T>* node, T data) {
        if (node == nullptr || node->data == data)
            return node;

        BSTNode<T>* result = searchHelper(node->left, data);
        if (result != nullptr)
            return result;

        return searchHelper(node->right, data);
    }

    BSTNode<T>* searchByIndexHelper(BSTNode<T>* node, int index) {
        if (node == nullptr || node->index == index)
            return node;

        BSTNode<T>* result = searchByIndexHelper(node->left, index);
        if (result != nullptr)
            return result;

        return searchByIndexHelper(node->right, index);
    }

    bool containsHelper(BSTNode<T>* node, int index) {
        if (node == nullptr)
            return false;

        if (index == node->index)
            return true;

        if (index < node->index)
            return containsHelper(node->left, index);
        else
            return containsHelper(node->right, index);
    }

    void printHelper(BSTNode<T>* node, const std::string& padding, int level, bool isRight) {
        if (node == nullptr)
            return;

        std::string direction = isRight ? "R" : "L";
        std::string connector = isRight ? "|___" : "|---";

        std::cout << padding << connector << node->data << " [" << node->index << "] " << "(L" << level << ")" << std::endl;

        std::string childPadding = padding + (isRight ? "    " : "|   ");
        int childLevel = level + 1;
        printHelper(node->left, childPadding, childLevel, false);
        printHelper(node->right, childPadding, childLevel, true);
    }
};

/*
* Class OpDemo: dummy class to showcase operator overloads
*/
class OpDemo {
private:
    int value;

public:
    OpDemo() : value(0) {}
    
    OpDemo(int val) : value(val) {}

    // Unary operators
    OpDemo operator+() const {
        return *this;  // Unary plus
    }

    OpDemo operator-() const {
        return OpDemo(-value);  // Unary minus
    }

    // Binary operators
    OpDemo operator+(const OpDemo& other) const {
        return OpDemo(value + other.value);  // Addition
    }

    OpDemo operator-(const OpDemo& other) const {
        return OpDemo(value - other.value);  // Subtraction
    }

    OpDemo operator*(const OpDemo& other) const {
        return OpDemo(value * other.value);  // Multiplication
    }

    OpDemo operator/(const OpDemo& other) const {
        if (other.value == 0)
            throw std::runtime_error("Division by zero!");
        return OpDemo(value / other.value);  // Division
    }

    // Relational operators
    bool operator==(const OpDemo& other) const {
        return value == other.value;  // Equality
    }

    bool operator!=(const OpDemo& other) const {
        return !(*this == other);  // Inequality
    }

    bool operator<(const OpDemo& other) const {
        return value < other.value;  // Less than
    }

    bool operator>(const OpDemo& other) const {
        return value > other.value;  // Greater than
    }

    bool operator<=(const OpDemo& other) const {
        return value <= other.value;  // Less than or equal to
    }

    bool operator>=(const OpDemo& other) const {
        return value >= other.value;  // Greater than or equal to
    }

    // Insertion operator
    friend std::ostream& operator<<(std::ostream& os, const OpDemo& obj) {
        os << obj.value;
        return os;
    }

    // Function call operator
    int operator()(int index) const {
        return value + index;
    }

    // Subscript operator
    int& operator[](int index) {
        static int dummy = -1;
        return dummy;
    }

    // Overloaded new operator
    void* operator new(size_t size) {
        std::cout << "Custom new operator called." << std::endl;
        return ::operator new(size);
    }

    // Overloaded new[] operator
    void* operator new[](size_t size) {
        std::cout << "Custom new[] operator called." << std::endl;
        return ::operator new[](size);
    }

        // Overloaded delete operator
        void operator delete(void* ptr) {
        std::cout << "Custom delete operator called." << std::endl;
        ::operator delete(ptr);
    }

    // Overloaded delete[] operator
    void operator delete[](void* ptr) {
        std::cout << "Custom delete[] operator called." << std::endl;
        ::operator delete[](ptr);
    }
};

#endif /* DATASTRUCTURES_HPP */

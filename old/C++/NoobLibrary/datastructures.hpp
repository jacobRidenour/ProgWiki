#ifndef DATASTRUCTURES_HPP
#define DATASTRUCTURES_HPP

#include <vector>
#include <iostream>
#include <iomanip>
#include <stack>
#include <algorithm>
#include <unordered_map>

using string = std::string;
namespace nl {
/*
* Class Matrix: store data linearly but access elements like a 2D array
*/
template<typename T>
class Matrix {
private:
    std::vector<T> _data;
    int _rows;
    int _cols;

    /* Helper functions */
    // calculate the determinant of a 2x2 matrix
    T determinant2x2(const Matrix<T>& mat) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    // Recursive function to calculate the determinant of a square matrix
    T determinantRecursive(const Matrix<T>& mat) {
        const int size = mat.rows();
        if (size == 1) {
            return mat[0][0];
        }
        else if (size == 2) {
            return determinant2x2(mat);
        }
        else {
            T det = 0;
            for (int j = 0; j < size; ++j) {
                Matrix<T> submatrix(size - 1, size - 1);
                for (int i = 1; i < size; ++i) {
                    for (int k = 0, col = 0; k < size; ++k) {
                        if (k == j) {
                            continue;
                        }
                        submatrix[i - 1][col] = mat[i][k];
                        ++col;
                    }
                }
                T cofactor = mat[0][j] * determinantRecursive(submatrix);
                if (j % 2 == 0) {
                    det += cofactor;
                }
                else {
                    det -= cofactor;
                }
            }
            return det;
        }
    }
public:
    Matrix(int rows, int cols) : _rows(rows), _cols(cols) { _data.resize(rows * cols); }

    Matrix(const Matrix& other) : _rows(other._rows), _cols(other._cols), _data(other._data) {}

    ~Matrix() {}

    // Proxy class for 2D indexing
    class Proxy {
    private:
        Matrix<T>& matrix;
        int row;

    public:
        Proxy(Matrix<T>& matrix, int row) : matrix(matrix), row(row) {}

        T& operator[](int col) {
            return matrix._data[row * matrix._cols + col];
        }
    };

    Proxy operator[](int row) {
        return Proxy(*this, row);
    }

    inline int rows() const { return _rows; }
    inline int cols() const { return _cols; }

    void fill(T value) {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                (*this)[i][j] = i * _cols + j + value;
            }
        }
    }

    void print() {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols - 1; j++) {  // Corrected index limit
                std::cout << "[" << i << "][" << j << "]: " << std::setw(4) << (*this)[i][j] << " ";
                std::cout << "[" << i << "][" << j + 1 << "]: " << std::setw(4) << (*this)[i][j + 1] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Calculate determinant of a square matrix
    T determinant() const {
        if (_rows != _cols) {
            throw std::logic_error("Determinant can only be calculated for a square matrix.");
        }
        return determinantRecursive(*this);
    }

    // Calculate inverse of a square matrix
    Matrix inverse() const {
        if (_rows != _cols) {
            throw std::logic_error("Inverse can only be calculated for a square matrix.");
        }

        const int size = _rows;
        Matrix<T> adjoint(size, size);
        Matrix<T> result(size, size);
        T det = determinantRecursive(*this);

        if (det == 0) {
            throw std::logic_error("Matrix is not invertible.");
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                Matrix<T> submatrix(size - 1, size - 1);
                for (int row = 0, subRow = 0; row < size; ++row) {
                    if (row == i) {
                        continue;
                    }
                    for (int col = 0, subCol = 0; col < size; ++col) {
                        if (col == j) {
                            continue;
                        }
                        submatrix[subRow][subCol] = (*this)[row][col];
                        ++subCol;
                    }
                    ++subRow;
                }
                T cofactor = determinantRecursive(submatrix);
                adjoint[i][j] = (i + j) % 2 == 0 ? cofactor : -cofactor;
            }
        }

        result = adjoint.transpose() * (static_cast<T>(1) / det);
        return result;
    }

    // Transpose a matrix
    Matrix<T> transpose() const {
        Matrix<T> result(_cols, _rows);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result[j][i] = (*this)[i][j];
            }
        }
        return result;
    }

    // Get the trace
    T trace() const {
        if (_rows != _cols) {
            throw std::logic_error("Trace can only be calculated for a square matrix.");
        }

        T sum = 0;
        for (int i = 0; i < _rows; ++i) {
            sum += (*this)[i][i];
        }
        return sum;
    }

    // Operators
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            _rows = other._rows;
            _cols = other._cols;
            _data = other._data;
        }
        return *this;
    }

    bool operator==(const Matrix& other) const {
        return (_rows == other._rows && _cols == other._cols && _data == other._data);
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    Matrix operator+(const Matrix& other) const {
        if (_rows != other._rows || _cols != other._cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        Matrix result(_rows, _cols);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result[i][j] = (*this)[i][j] + other[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (_rows != other._rows || _cols != other._cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }

        Matrix result(_rows, _cols);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result[i][j] = (*this)[i][j] - other[i][j];
            }
        }
        return result;
    }

    // Scalar multiplication
    Matrix operator*(const T& scalar) const {
        Matrix result(_rows, _cols);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result[i][j] = (*this)[i][j] * scalar;
            }
        }
        return result;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (_cols != other._rows) {
            throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
        }

        Matrix result(_rows, other._cols);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < other._cols; ++j) {
                T sum = 0;
                for (int k = 0; k < _cols; ++k) {
                    sum += (*this)[i][k] * other[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    // Iterator
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Matrix<T>& matrix, int index) : matrix(matrix), index(index) {}

        reference operator*() const {
            return matrix.data()[index];
        }

        pointer operator->() const {
            return &(operator*());
        }

        Iterator& operator++() {
            ++index;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return index == other.index;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        Matrix<T>& matrix;
        int index;
    };

    Iterator begin() {
        return Iterator(*this, 0);
    }

    Iterator end() {
        return Iterator(*this, data().size());
    }
};

/*
* Class Cube: store data linearly but access elements like a 3D array
*/
template<typename T>
class Cube {
private:
    std::vector<T> _data;
    int _rows;
    int _cols;
    int _slices;

public:
    Cube(int rows, int cols, int slices) : _rows(rows), _cols(cols), _slices(slices) {
        _data.resize(rows * cols * slices);
    }

    Cube(const Cube& other) : _rows(other._rows), _cols(other._cols), _slices(other._slices), _data(other._data) {}

    ~Cube() {}

    // Proxy class for 3D indexing
    class Proxy2D {
    private:
        Cube<T>& cube;
        int row;
        int col;

    public:
        Proxy2D(Cube<T>& cube, int row, int col) : cube(cube), row(row), col(col) {}

        T& operator[](int slice) {
            return cube._data[(row * cube._cols + col) * cube._slices + slice];
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

    inline int rows() const { return _rows; }
    inline int cols() const { return _cols; }
    inline int slices() const { return _slices; }

    void fill(T value) {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                for (int k = 0; k < _slices; k++) {
                    (*this)[i][j][k] = i * _cols + j * _rows + k + value;
                }
            }
        }
    }

    void print() {
        for (int k = 0; k < _slices; k++) {
            std::cout << "Slice " << k << ":" << std::endl;

            for (int i = 0; i < _rows; i++) {
                for (int j = 0; j < _cols - 1; j++) {  // Corrected index limit
                    std::cout << "[" << i << "][" << j << "][" << k << "]: " << std::setw(4) << (*this)[i][j][k] << " ";
                    std::cout << "[" << i << "][" << j + 1 << "][" << k << "]: " << std::setw(4) << (*this)[i][j + 1][k] << " ";
                }
                std::cout << std::endl;
            }

            std::cout << std::endl << std::endl;
        }
    }

    template<typename T>
    Cube<T> transpose(const Cube<T>& cube) {
        Cube<T> transposed(cube.cols(), cube.rows(), cube.slices());
        for (int i = 0; i < cube.rows(); ++i) {
            for (int j = 0; j < cube.cols(); ++j) {
                for (int k = 0; k < cube.slices(); ++k) {
                    transposed[j][i][k] = cube[i][j][k];
                }
            }
        }
        return transposed;
    }

    template<typename T>
    Cube<T> reshape(const Cube<T>& cube, int newRows, int newCols, int newSlices) {
        const int totalElements = cube.rows() * cube.cols() * cube.slices();
        if (totalElements != newRows * newCols * newSlices) {
            throw std::invalid_argument("Total number of elements must remain the same during reshape.");
        }

        Cube<T> reshaped(newRows, newCols, newSlices);
        int index = 0;
        for (int k = 0; k < newSlices; ++k) {
            for (int i = 0; i < newRows; ++i) {
                for (int j = 0; j < newCols; ++j) {
                    reshaped[i][j][k] = cube[index / (cube.cols() * cube.slices())][index / cube.slices() % cube.cols()][index % cube.slices()];
                    ++index;
                }
            }
        }
        return reshaped;
    }

    template<typename T>
    Matrix<T> slice(const Cube<T>& cube, int sliceIndex, int dimension) {
        if (dimension < 0 || dimension >= 3) {
            throw std::invalid_argument("Invalid dimension for slicing. Dimension must be 0, 1, or 2.");
        }

        int rows, cols;
        if (dimension == 0) {
            rows = cube.cols();
            cols = cube.slices();
        }
        else if (dimension == 1) {
            rows = cube.rows();
            cols = cube.slices();
        }
        else {
            rows = cube.rows();
            cols = cube.cols();
        }

        Matrix<T> slicedMatrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (dimension == 0) {
                    slicedMatrix[i][j] = cube[j][i][sliceIndex];
                }
                else if (dimension == 1) {
                    slicedMatrix[i][j] = cube[i][j][sliceIndex];
                }
                else {
                    slicedMatrix[i][j] = cube[i][sliceIndex][j];
                }
            }
        }

        return slicedMatrix;
    }

    // Operators
    template<typename T>
    bool operator==(const Cube<T>& lhs, const Cube<T>& rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() || lhs.slices() != rhs.slices()) {
            return false;
        }

        for (int i = 0; i < lhs.rows(); ++i) {
            for (int j = 0; j < lhs.cols(); ++j) {
                for (int k = 0; k < lhs.slices(); ++k) {
                    if (lhs[i][j][k] != rhs[i][j][k]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    template<typename T>
    bool operator!=(const Cube<T>& lhs, const Cube<T>& rhs) {
        return !(lhs == rhs);
    }

    template<typename T>
    Cube<T> operator+(const Cube<T>& lhs, const Cube<T>& rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() || lhs.slices() != rhs.slices()) {
            throw std::invalid_argument("Cube dimensions must match for addition.");
        }

        Cube<T> result(lhs.rows(), lhs.cols(), lhs.slices());
        for (int i = 0; i < lhs.rows(); ++i) {
            for (int j = 0; j < lhs.cols(); ++j) {
                for (int k = 0; k < lhs.slices(); ++k) {
                    result[i][j][k] = lhs[i][j][k] + rhs[i][j][k];
                }
            }
        }

        return result;
    }

    template<typename T>
    Cube<T> operator-(const Cube<T>& lhs, const Cube<T>& rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() || lhs.slices() != rhs.slices()) {
            throw std::invalid_argument("Cube dimensions must match for subtraction.");
        }

        Cube<T> result(lhs.rows(), lhs.cols(), lhs.slices());
        for (int i = 0; i < lhs.rows(); ++i) {
            for (int j = 0; j < lhs.cols(); ++j) {
                for (int k = 0; k < lhs.slices(); ++k) {
                    result[i][j][k] = lhs[i][j][k] - rhs[i][j][k];
                }
            }
        }

        return result;
    }

    // Scalar multiplication
    template<typename T>
    Cube<T> operator*(const Cube<T>& cube, const T& scalar) {
        Cube<T> result(cube.rows(), cube.cols(), cube.slices());
        for (int i = 0; i < cube.rows(); ++i) {
            for (int j = 0; j < cube.cols(); ++j) {
                for (int k = 0; k < cube.slices(); ++k) {
                    result[i][j][k] = cube[i][j][k] * scalar;
                }
            }
        }
        return result;
    }

    template<typename T>
    Cube<T> operator*(const T& scalar, const Cube<T>& cube) {
        return cube * scalar;
    }

    // Cube multiplication
    template<typename T>
    Cube<T> operator*(const Cube<T>& lhs, const Cube<T>& rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() || lhs.slices() != rhs.slices()) {
            throw std::invalid_argument("Cube dimensions must match for multiplication.");
        }

        Cube<T> result(lhs.rows(), lhs.cols(), lhs.slices());
        for (int i = 0; i < lhs.rows(); ++i) {
            for (int j = 0; j < lhs.cols(); ++j) {
                for (int k = 0; k < lhs.slices(); ++k) {
                    result[i][j][k] = lhs[i][j][k] * rhs[i][j][k];
                }
            }
        }

        return result;
    }

    // Iterator
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Cube<T>& cube, int index) : cube(cube), index(index) {}

        reference operator*() const {
            return cube.data()[index];
        }

        pointer operator->() const {
            return &(operator*());
        }

        Iterator& operator++() {
            ++index;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return index == other.index;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        Cube<T>& cube;
        int index;
    };

    Iterator begin() {
        return Iterator(*this, 0);
    }

    Iterator end() {
        return Iterator(*this, data().size());
    }
};

/*
* Class BSTNode: Nodes for class IndexedBST, an indexed Binary Search Tree
*/
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
    BSTNode<T>* _root;
    BSTNode<T>* _cursor;
    int _size;

public:
    IndexedBST() : _root(nullptr), _cursor(nullptr), _size(0) {}

    // Copy constructor
    IndexedBST(const IndexedBST& other) : root(nullptr) {
        // Create a deep copy of the other IndexedBST
        if (other.root != nullptr) {
            root = copy_nodes(other.root);
        }
    }

    // Destructor
    ~IndexedBST() {
        // Recursively delete all nodes
        destroy_nodes(root);
    }

    int size() const {
        return _size;
    }

    BSTNode<T>* root() {
        return _root;
    }

    void add(T data, int index) {
        if (_root == nullptr) {
            _root = new BSTNode<T>(data, index);
            _cursor = _root;
        }
        else {
            add_helper(_root, data, index);
        }
        _size++;
    }

    void add_inorder(T data, int index) {
        if (_root == nullptr) {
            _root = new BSTNode<T>(data, index);
            _cursor = _root;
        }
        else {
            add_helper_inorder(_root, data, index);
        }
        _size++;
    }

    void add_preorder(T data, int index) {
        if (_root == nullptr) {
            _root = new BSTNode<T>(data, index);
            _cursor = _root;
        }
        else {
            add_helper_preorder(_root, data, index);
        }
        _size++;
    }

    void add_postorder(T data, int index) {
        if (_root == nullptr) {
            _root = new BSTNode<T>(data, index);
            _cursor = _root;
        }
        else {
            add_helper_postorder(_root, data, index);
        }
        _size++;
    }

    void remove_this_node(BSTNode<T>* node) {
        _root = removeHelper(_root, node);
        _size--;
    }

    void remove_this_data(const T& data) {
        _root = removeHelper(_root, data);
        _size--;
    }

    void remove_this_index(int index) {
        _root = removeHelperByIndex(_root, index);
        _size--;
    }

    BSTNode<T>* search_for_node(BSTNode<T>* node) {
        return searchHelper(_root, node);
    }

    BSTNode<T>* search_for_data(T data) {
        return searchHelper(_root, data);
    }

    BSTNode<T>* search_for_index(int index) {
        return searchByIndexHelper(_root, index);
    }

    std::vector<T> to_vector() {
        std::vector<T> result;
        result.reserve(_size); // Reserve space to avoid frequent reallocations
        collect_elements(_root, result); // Collect elements into the vector
        std::sort(result.begin(), result.end()); // Sort the vector

        return result;
    }

    T min() {
        if (_root == nullptr)
            throw std::runtime_error("Tree is empty.");

        BSTNode<T>* current = _root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }

    T max() {
        if (_root == nullptr)
            throw std::runtime_error("Tree is empty.");

        BSTNode<T>* current = _root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

    bool contains(int index) {
        return containsHelper(_root, index);
    }

    void print() {
        print_helper(_root, "", 0, false);
    }

    void balance() {
        _root = balance_node(_root);
    }

    // Operators
    bool operator==(const IndexedBST& other) const {
        // Compare the size of the IndexedBST
        if (size() != other.size()) {
            return false;
        }

        // Compare the elements in the same order using iterators
        auto it1 = begin();
        auto it2 = other.begin();
        auto endIt = end();

        while (it1 != endIt && it2 != other.end()) {
            if (*it1 != *it2) {
                return false;
            }

            ++it1;
            ++it2;
        }

        return true;
    }

    bool operator!=(const IndexedBST& other) const {
        return !(*this == other);
    }

    // Element-wise addition
    IndexedBST& operator+=(const IndexedBST& other) {
        // Check if the objects have the same type
        static_assert(std::is_same_v<T, typename IndexedBST::value_type>,
            "IndexedBST types do not match for element-wise addition.");

        // Perform element-wise addition
        if (other.root != nullptr) {
            add_nodes(root, other.root);
        }

        return *this;
    }

    // Element-wise subtraction
    IndexedBST& operator-=(const IndexedBST& other) {
        // Check if the objects have the same type
        static_assert(std::is_same_v<T, typename IndexedBST::value_type>,
            "IndexedBST types do not match for element-wise subtraction.");

        // Perform element-wise subtraction
        if (other.root != nullptr) {
            subtract_nodes(root, other.root);
        }

        return *this;
    }

    // Overloaded + operator for element-wise addition
    IndexedBST operator+(const IndexedBST& other) const {
        // Check if the objects have the same type
        static_assert(std::is_same_v<T, typename IndexedBST::value_type>,
            "IndexedBST types do not match for element-wise addition.");

        IndexedBST result(*this);  // Create a copy of the current IndexedBST
        result += other;           // Perform element-wise addition
        return result;
    }

    // Overloaded - operator for element-wise subtraction
    IndexedBST operator-(const IndexedBST& other) const {
        // Check if the objects have the same type
        static_assert(std::is_same_v<T, typename IndexedBST::value_type>,
            "IndexedBST types do not match for element-wise subtraction.");

        IndexedBST result(*this);  // Create a copy of the current IndexedBST
        result -= other;           // Perform element-wise subtraction
        return result;
    }

    // Iterator
    class Iterator {
    private:
        BSTNode<T>* current;
        std::stack<BSTNode<T>*> stack;

        void pushLeft(BSTNode<T>* node) {
            while (node != nullptr) {
                stack.push(node);
                node = node->left;
            }
        }

    public:
        Iterator(BSTNode<T>* root) : current(nullptr) {
            pushLeft(root);
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
        }

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            if (current == nullptr && stack.empty()) {
                return *this;
            }

            if (current->right != nullptr) {
                pushLeft(current->right);
            }

            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
            else {
                current = nullptr;
            }

            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(root());
    }

    Iterator end() {
        return Iterator(nullptr);
    }

private:
    // Recursive function to add nodes
    void add_nodes(BSTNode<T>* node1, const BSTNode<T>* node2) {
        if (node2 == nullptr) {
            return;
        }

        node1->data += node2->data;

        add_nodes(node1->left, node2->left);
        add_nodes(node1->right, node2->right);
    }

    // Recursive function to subtract nodes
    void subtract_nodes(BSTNode<T>* node1, const BSTNode<T>* node2) {
        if (node2 == nullptr) {
            return;
        }

        node1->data -= node2->data;

        subtract_nodes(node1->left, node2->left);
        subtract_nodes(node1->right, node2->right);
    }

    // Recursive function to copy nodes
    BSTNode<T>* copy_nodes(BSTNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }

        BSTNode<T>* newNode = new BSTNode<T>(node->data, node->index);
        newNode->left = copy_nodes(node->left);
        newNode->right = copy_nodes(node->right);
        return newNode;
    }

    // Recursive function to destroy nodes
    void destroy_nodes(BSTNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        destroy_nodes(node->left);
        destroy_nodes(node->right);
        delete node;
    }

    // Function to perform a right rotation
    BSTNode<T>* rotate_right(BSTNode<T>* node) {
        BSTNode<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    // Function to perform a left rotation
    BSTNode<T>* rotate_left(BSTNode<T>* node) {
        BSTNode<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    // Function to get the height of a node
    int get_node_height(BSTNode<T>* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = get_node_height(node->left);
        int rightHeight = get_node_height(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    // Function to get the balance factor of a node
    int get_balance_factor(BSTNode<T>* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = get_node_height(node->left);
        int rightHeight = get_node_height(node->right);

        return leftHeight - rightHeight;
    }

    // Function to recursively balance the tree
    BSTNode<T>* balance_node(BSTNode<T>* node) {
        if (node == nullptr)
            return nullptr;

        int balanceFactor = get_balance_factor(node);

        // Left-Left case
        if (balanceFactor > 1 && get_balance_factor(node->left) >= 0) {
            node = rotate_right(node);
        }
        // Right-Right case
        else if (balanceFactor < -1 && get_balance_factor(node->right) <= 0) {
            node = rotate_left(node);
        }
        // Left-Right case
        else if (balanceFactor > 1 && get_balance_factor(node->left) < 0) {
            node->left = rotate_left(node->left);
            node = rotate_right(node);
        }
        // Right-Left case
        else if (balanceFactor < -1 && get_balance_factor(node->right) > 0) {
            node->right = rotate_right(node->right);
            node = rotate_left(node);
        }

        node->left = balance_node(node->left);
        node->right = balance_node(node->right);

        return node;
    }

    void collect_elements(BSTNode<T>* node, std::vector<T>& result) {
        if (node == nullptr)
            return;

        collect_elements(node->left, result);
        result.push_back(node->data);
        collect_elements(node->right, result);
    }

    void add_helper(BSTNode<T>* node, T data, int index) {
        if (index < node->index) {
            if (node->left == nullptr) {
                node->left = new BSTNode<T>(data, index);
            }
            else {
                add_helper(node->left, data, index);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new BSTNode<T>(data, index);
            }
            else {
                add_helper(node->right, data, index);
            }
        }
    }

    void add_helper_inorder(BSTNode<T>* node, T data, int index) {
        if (node->left != nullptr) {
            add_helper_inorder(node->left, data, index);
        }
        else {
            node->left = new BSTNode<T>(data, index);
        }
    }

    void add_helper_preorder(BSTNode<T>* node, T data, int index) {
        if (node->left == nullptr) {
            node->left = new BSTNode<T>(data, index);
        }
        else {
            add_helper_preorder(node->left, data, index);
        }
    }

    void add_helper_postorder(BSTNode<T>* node, T data, int index) {
        if (node->right == nullptr) {
            node->right = new BSTNode<T>(data, index);
        }
        else {
            add_helper_postorder(node->right, data, index);
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

    void print_helper(BSTNode<T>* node, const std::string& padding, int level, bool isRight) {
        if (node == nullptr)
            return;

        std::string direction = isRight ? "R" : "L";
        std::string connector = isRight ? "|___" : "|---";

        std::cout << padding << connector << node->data << " [" << node->index << "] " << "(L" << level << ")" << std::endl;

        std::string childPadding = padding + (isRight ? "    " : "|   ");
        int childLevel = level + 1;
        print_helper(node->left, childPadding, childLevel, false);
        print_helper(node->right, childPadding, childLevel, true);
    }
};

/*
* Class TrieNode: Nodes for class Trie, a traditional Trie
*/
class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool is_leaf;

    TrieNode() {
        is_leaf = false;
    }
};

/*
* Class Trie: tree for locating specific keys within a set (strings in this case)
*/
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the Trie
    void insert(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }

            current = current->children[c];
        }

        current->is_leaf = true;
    }

    // Searches for a word in the Trie
    bool search(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }

            current = current->children[c];
        }

        return current->is_leaf;
    }

    // Checks if a given prefix exists in the Trie
    bool starts_with(const string& prefix) {
        TrieNode* current = root;

        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }

            current = current->children[c];
        }

        return true;
    }

    // Removes a word from the Trie
    void remove(const string& word) {
        if (!search(word))
            return;

        TrieNode* current = root;
        TrieNode* previous = nullptr;

        string wordCopy = word;  // Make a copy of the word

        for (char c : wordCopy) {
            previous = current;
            current = current->children[c];
        }

        current->is_leaf = false;

        // Remove nodes with no other children
        while (previous != nullptr && !current->is_leaf && current->children.empty()) {
            previous->children.erase(wordCopy.back());
            delete current;
            current = previous;
            wordCopy.pop_back();
        }
    }

    // Counts the number of words with a given prefix
    int count_words_with_prefix(const string& prefix) {
        TrieNode* current = root;

        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return 0;
            }

            current = current->children[c];
        }

        return count_words(current);
    }

    // Recursive helper function to count words from a given TrieNode
    int count_words(TrieNode* node) {
        int count = 0;

        if (node->is_leaf)
            count++;

        for (const auto& child : node->children) {
            count += count_words(child.second);
        }

        return count;
    }

    // Returns all words in the Trie with a given prefix
    std::vector<string> get_words_with_prefix(const string& prefix) {
        TrieNode* current = root;

        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return {};
            }

            current = current->children[c];
        }

        std::vector<string> words;
        string prefixWord = prefix;
        get_words(current, prefixWord, words);

        return words;
    }

    // Recursive helper function to retrieve words from a given TrieNode
    void get_words(TrieNode* node, string& currentWord, std::vector<string>& words) {
        if (node->is_leaf) {
            words.push_back(currentWord);
        }

        for (const auto& child : node->children) {
            currentWord.push_back(child.first);
            get_words(child.second, currentWord, words);
            currentWord.pop_back();
        }
    }
};
}
#endif /* DATASTRUCTURES_HPP */

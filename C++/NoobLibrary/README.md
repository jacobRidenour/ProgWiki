# Noob Library

Personal project. Amateur attempt at creating some reusable data structures and utility functions so I don't have to keep coming up with this same code. Feel free to use and modify them yourself. Lots of things are tested, but quite a few things still are not. You're welcome to try yourself. Everything can be accessed via ```namespace nl```.

## Data Structures

File: ```datastructures.hpp```

class Matrix - stores data linearly but elements can be accessed like a 2D array.
```
Matrix(int rows, int cols)
Matrix(const Matrix& other)
~Matrix()
inline int rows()
inline int cols()
void fill(T value)
void print()
T determinant const
Matrix inverse() const
Matrix<T> transpose() const
T trace() const
Matrix& operator=(const Matrix& other)
bool operator==(const Matrix& other) const
bool operator!=(const Matrix& other) const
Matrix operator+(const Matrix& other) const
Matrix operator-(const Matrix& other) const
Matrix operator*(const T& scalar) const
Matrix operator*(const Matrix& other) const
class Iterator{};
Iterator begin()
Iterator end()
```

class Cube - stores data linearly but elements can be accessed like a 3D array.
```
Cube(int rows, int cols, int slices)
Cube(const Cube& other)
~Cube()
inline int rows()
inline int cols()
inline int slices()
void fill(T value)
void print()
Cube<T> transpose(const Cube<T>& cube)
Cube<T> reshape(const Cube<T>& cube, int newRows, int newCols, int newSlices)
Matrix<T> slice(const Cube<T>& cube, int sliceIndex, int dimension)
bool operator==(const Cube<T>& lhs, const Cube<T>& rhs)
bool operator!=(const Cube<T>& lhs, const Cube<T>& rhs)
Cube<T> operator+(const Cube<T>& lhs, const Cube<T>& rhs)
Cube<T> operator-(const Cube<T>& lhs, const Cube<T>& rhs)
Cube<T> operator*(const Cube<T>& cube, const T& scalar)
Cube<T> operator*(const T& scalar, const Cube<T>& cube)
Cube<T> operator*(const Cube<T>& lhs, const Cube<T>& rhs)
class Iterator{};
Iterator begin()
Iterator end()
```

class BSTNode - node of an Indexed Binary Search Tree
class IndexedBST - indexed Binary Search Tree. Includes printing and (basic) balancing.
```
IndexedBST()
IndexedBST(const IndexedBST& other)
~IndexedBST
int size() const
BSTNode<T>* root()
void add(T data, int index)
void add_inorder(T data, int index)
void add_preorder(T data, int index)
void add_postorder(T data, int index)
void remove_this_node(BSTNode<T>* node)
void remove_this_data(const T& data)
void remove_this_index(int index)
BSTNode<T>* search_for_node(BSTNode<T>* node)
BSTNode<T>* search_for_data(T data)
BSTNode<T>* search_for_index(int index)
std::vector<T> to_vector()
T min()
T max()
bool contains(int index)
void print()
void balance()
bool operator==(const IndexedBST& other) const
bool operator!=(const IndexedBST& other) const
IndexedBST& operator+=(const IndexedBST& other)
IndexedBST& operator-=(const IndexedBST& other)
IndexedBST operator+(const IndexedBST& other) const
IndexedBST operator-(const IndexedBST& other) const
class Iterator{};
Iterator begin()
Iterator end()
```

class TrieNode - node of a Trie
class Trie - classic character-node based tree structure
```
Trie()
void insert(const string& word)
bool search(const string& word)
bool starts_with(const string& prefix)
void remove(const string& word)
int count_words_with_prefix(const string& prefix)
int count_words(TrieNode* node)
std::vector<string> get_words_with_prefix(const string& prefix)
void get_words(TrieNode* node, string& currentWord, std::vector<string>& words)
```

## Utilities

namespace string
```
std::string get_after(const std::string& str, char c)
bool contains(const string& str, char c)
bool is_numeric(const std::string& str)
```

namespace files
```
string read_file_to_string(const string& filename)
string read_file_to_string(const string& directory, const string& filename)
```

namespace debug - need to link against additional libraries (depending on MSVC or Linux)
```
void printStackTrace()
```

namespace sort - Goal is to implement various sorting algorithms such that they work on any iterable. Largely untested for now.
```
void quickSort(T& iterable)
void mergeSort(T& iterable)
void heapSort(T& iterable)
void insertionSort(T& iterable)
void blockSort(T& iterable, int min_value, int max_value)
void selectionSort(T& iterable)
void shellSort(T& iterable)
void bubbleSort(T& iterable)
void convertCubeToArray(const T& cube, OutputIterator output)
void cubeSort(RandomAccessIterator first, RandomAccessIterator last)
void cubeSort(T& iterable)
```
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <filesystem>
#include <functional>
#include <regex>
#include <algorithm>

using string = std::string;

namespace nl {
    namespace strings {
        // Returns a substring of string str starting after the first instance of char c.
        std::string get_after(const std::string& str, char c) {
            size_t pos = str.find(c);
            if (pos != std::string::npos)
                return str.substr(pos);
            else
                return "";
        }

        // Returns bool indicating whether the string str contains the specified char c.
        bool contains(const string& str, char c) {
            return str.find(c) != std::string::npos;
        }

        // Returns bool indicating whether the string only contains the characters 0-9, e/E, +/-
        bool is_numeric(const std::string& str) {
            std::regex pattern("^[0-9.eE+-]+$");
            return std::regex_match(str, pattern);
        }


    }
    namespace files {
        // Searches cwd for given filename, returns its contents as a string.
        string read_file_to_string(const string& filename) {
            std::ifstream file(filename);
            if (!file) {
                std::cerr << "Error opening file: " << filename << std::endl;
                return "";
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }

        // Searches directory/filename for given filename, returns its contents as a string.
        string read_file_to_string(const string& directory, const string& filename) {
            string filePath;
            //Verify that directory to search ends in a /, add it if not
            if (directory.at(directory.length() - 1) != '/') {
                filePath = directory + "/" + filename;
            }
            else filePath = directory + filename;

            std::ifstream file(filePath);
            if (!file) {
                std::cerr << "Error opening file: " << filePath << std::endl;
                return "";
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }


    }

    /* Untested */
    namespace debug {
        #ifdef _WIN32
        //Make sure to link against the Dbghelp.lib library when compiling.
        #include <windows.h>
        #include <DbgHelp.h>
        void printStackTrace()
        {
            const int max_frames = 64;
            void* stack_trace[max_frames];
            HANDLE process = GetCurrentProcess();
            SymInitialize(process, nullptr, TRUE);
            WORD num_frames = CaptureStackBackTrace(0, max_frames, stack_trace, nullptr);

            SYMBOL_INFO* symbol_info = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
            symbol_info->MaxNameLen = 255;
            symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);

            for (int i = 0; i < num_frames; ++i)
            {
                SymFromAddr(process, (DWORD64)(stack_trace[i]), 0, symbol_info);
                std::cout << i << ": " << symbol_info->Name << std::endl;
            }

            free(symbol_info);
        }
        #else
        #include <execinfo.h>
        //Make sure to link against the execinfo library using the -rdynamic flag when compiling.
        void printStackTrace()
        {
            const int max_frames = 64;
            void* stack_trace[max_frames];
            int num_frames = backtrace(stack_trace, max_frames);
            char** symbols = backtrace_symbols(stack_trace, num_frames);

            if (symbols)
            {
                for (int i = 0; i < num_frames; ++i)
                    std::cout << symbols[i] << std::endl;
            }

            free(symbols);
        }
        #endif
    }

    /* Untested */
    namespace sort {
            /********************************************************************/
            /*  Iteratable object Sorting Algorithms                            */
            /*&&*****************************************************************/
            /*  Name             Best        Worst        Average       Memory  */
            /*  --------------------------------------------------------------  */
            /*  Quicksort        n*log(n)    n^2          n*log(n)      log(n)  */
            /*  Merge sort       n*log(n)    n*log(n)     n*log(n)      n       */
            /*  Heapsort         n*log(n)    n*log(n)     n*log(n)      1       */
            /*  Insertion sort   n           n^2          n^2           1       */
            /*  Block sort       n           n*log(n)     n*log(n)      1       */
            /*  Selection sort   n^2         n^2          n^2           1       */
            /*  Shellsort        n*log(n)    n^(3/2)      n^(4/3)       1       */
            /*  Bubble sort      n           n^2          n^2           1       */
            /*  Cubesort         n           n*log(n)     n*log(n)      n       */
            /********************************************************************/

            // Quicksort
            template <typename T>
            void quickSort(T& iterable) {
                // Base case: return if iterable has zero or one element
                if (std::distance(std::begin(iterable), std::end(iterable)) <= 1) {
                    return;
                }

                // Choose pivot (e.g., first element)
                auto pivot = *std::begin(iterable);

                // Partition the iterable
                auto partition_point = std::partition(std::begin(iterable), std::end(iterable), [&](const auto& element) {
                    return element < pivot;
                    });

                // Recursively call quickSort on sub-arrays
                T left_subarray(std::begin(iterable), partition_point);
                quickSort(left_subarray);

                T right_subarray(partition_point, std::end(iterable));
                quickSort(right_subarray);

                // Combine the sorted sub-arrays
                std::copy(std::begin(left_subarray), std::end(left_subarray), std::begin(iterable));
                std::copy(std::begin(right_subarray), std::end(right_subarray), partition_point);
            }

            // Merge Sort
            template <typename T>
            void mergeSort(T& iterable) {
                // Base case: return if iterable has zero or one element
                if (std::distance(std::begin(iterable), std::end(iterable)) <= 1) {
                    return;
                }

                // Split the iterable into two halves
                auto mid = std::next(std::begin(iterable), std::distance(std::begin(iterable), std::end(iterable)) / 2);
                T left_subarray(std::begin(iterable), mid);
                T right_subarray(mid, std::end(iterable));

                // Recursively call mergeSort on sub-arrays
                mergeSort(left_subarray);
                mergeSort(right_subarray);

                // Merge the sorted sub-arrays
                auto left_it = std::begin(left_subarray);
                auto right_it = std::begin(right_subarray);
                auto result_it = std::begin(iterable);

                while (left_it != std::end(left_subarray) && right_it != std::end(right_subarray)) {
                    if (*left_it <= *right_it) {
                        *result_it = *left_it;
                        ++left_it;
                    }
                    else {
                        *result_it = *right_it;
                        ++right_it;
                    }
                    ++result_it;
                }

                // Copy the remaining elements, if any
                std::copy(left_it, std::end(left_subarray), result_it);
                std::copy(right_it, std::end(right_subarray), result_it);
            }

            // Heapsort
            template <typename T>
            void heapSort(T& iterable) {
                // Build max-heap
                std::make_heap(std::begin(iterable), std::end(iterable));

                // Perform sorting
                for (auto it = std::end(iterable); it != std::begin(iterable); --it) {
                    std::pop_heap(std::begin(iterable), it);
                }
            }

            // Insertion Sort
            template <typename T>
            void insertionSort(T& iterable) {
                for (auto i = std::next(std::begin(iterable)); i != std::end(iterable); ++i) {
                    auto key = *i;
                    auto j = std::prev(i);

                    while (j != std::prev(std::begin(iterable)) && *j > key) {
                        *(std::next(j)) = *j;
                        --j;
                    }

                    *(std::next(j)) = key;
                }
            }

            // Block Sort
            template <typename T>
            void blockSort(T& iterable, int min_value, int max_value) {
                const int num_buckets = max_value - min_value + 1;
                std::vector<std::vector<typename T::value_type>> buckets(num_buckets);

                // Distribute elements into buckets
                for (const auto& element : iterable) {
                    int bucket_index = element - min_value;
                    buckets[bucket_index].push_back(element);
                }

                // Sort each bucket individually (using a sorting algorithm of your choice)
                for (auto& bucket : buckets) {
                    // Apply a suitable sorting algorithm (e.g., std::sort())
                    std::sort(std::begin(bucket), std::end(bucket));
                }

                // Concatenate the sorted buckets
                auto iter = std::begin(iterable);
                for (const auto& bucket : buckets) {
                    iter = std::copy(std::begin(bucket), std::end(bucket), iter);
                }
            }

            // Selection Sort
            template <typename T>
            void selectionSort(T& iterable) {
                for (auto i = std::begin(iterable); i != std::end(iterable); ++i) {
                    auto min_it = i;

                    for (auto j = std::next(i); j != std::end(iterable); ++j) {
                        if (*j < *min_it) {
                            min_it = j;
                        }
                    }

                    std::iter_swap(i, min_it);
                }
            }

            // Shellsort
            template <typename T>
            void shellSort(T& iterable) {
                int size = std::distance(std::begin(iterable), std::end(iterable));

                // Determine the gap sequence
                int gap = 1;
                while (gap < size / 3) {
                    gap = 3 * gap + 1;
                }

                while (gap >= 1) {
                    // Perform insertion sort with the current gap value
                    for (auto i = std::next(std::begin(iterable), gap); i != std::end(iterable); ++i) {
                        auto key = *i;
                        auto j = i;

                        while (j != std::next(std::begin(iterable), gap - 1) && *std::prev(j, gap) > key) {
                            *j = *std::prev(j, gap);
                            j = std::prev(j, gap);
                        }

                        *j = key;
                    }

                    gap /= 3;
                }
            }

            // Bubble Sort
            template <typename T>
            void bubbleSort(T& iterable) {
                int size = std::distance(std::begin(iterable), std::end(iterable));

                for (int i = 0; i < size - 1; ++i) {
                    bool swapped = false;

                    for (int j = 0; j < size - i - 1; ++j) {
                        if (*(std::next(std::begin(iterable), j)) > *(std::next(std::begin(iterable), j + 1))) {
                            std::iter_swap(std::next(std::begin(iterable), j), std::next(std::begin(iterable), j + 1));
                            swapped = true;
                        }
                    }

                    if (!swapped) {
                        // No swaps made in this pass, the iterable is already sorted
                        break;
                    }
                }
            }

            // Cubesort helper function to convert the cube to an array
            template <typename T, typename OutputIterator>
            void convertCubeToArray(const T& cube, OutputIterator output) {
                for (const auto& element : cube) {
                    std::copy(element.begin(), element.end(), output);
                }
            }

            // Cubesort implementation
            template <typename RandomAccessIterator>
            void cubeSort(RandomAccessIterator first, RandomAccessIterator last) {
                using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;

                if (std::distance(first, last) > 1) {
                    // Choose a pivot element
                    RandomAccessIterator pivot = first + (std::distance(first, last) / 2);

                    // Partition the array
                    RandomAccessIterator i = first;
                    RandomAccessIterator j = last - 1;
                    while (i <= j) {
                        while (*i < *pivot)
                            ++i;

                        while (*j > *pivot)
                            --j;

                        if (i <= j) {
                            std::iter_swap(i, j);
                            ++i;
                            --j;
                        }
                    }

                    // Sort the sub-arrays
                    cubeSort(first, j + 1);
                    cubeSort(i, last);
                }
            }

            // Public function to call Cubesort
            template <typename T>
            void cubeSort(T& iterable) {
                // Create and manipulate the cube structure using the iterable
                // Call the recursive cubeSort function
                cubeSort(std::begin(iterable), std::end(iterable));
            }
    }
}

#endif /* UTILITIES_HPP */
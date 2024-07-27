import numpy as np

def npStuff():
    # Basic Functions
    #################
    arr = np.zeros((3,3))   # Empty 3x3 array with all 0s
    arr[:] = 2              # Assign 2 to all values in arr
    arr.fill(2)             # Or use fill() instead (assign changes in place)
    arr += 3                # Add 3 to each element (also works with -= *=); only legal to do /= on float types
    print(arr.dtype)        # float
    print(arr)
    
    # Initialize it with ints instead of floats with:
    arr = np.zeros((3,3), dtype=np.int64)
    
    arr2 = np.arange(1, 10).reshape((3,3))  # 3x3 array with range from 1 to 10 exclusive
    print(arr2.dtype)                       # int
    print(arr2)
    
    total = arr2.sum()              # sum of all elements in the array
    total_cols = arr2.sum(axis=0)   # array with sum of all elements in axis 0 (cols)
    total_rows = arr2.sum(axis=1)   # array with sum of all elements in axis 1 (rows)
    internal_product = arr.prod()   # multiply each element of the array together
    average = arr2.mean()           # average of the array
    max = arr2.max()                # get max value in array
    min = arr2.min()                # get min value in array
    max_index = arr2.argmax()       # get index of max value in array
    min_index = arr2.argmin()       # get index of min value in array
    peak_to_peak = arr2.ptp()       # == arr2.max() - arr2.min()
    
    print(total)
    print(total_cols)
    print(total_rows)
    print('Internal product:', internal_product)
    print('Average:', average)
    print('Min:', min, 'at', min_index)
    print('Max:', max, 'at', max_index)
    
    arr2_1d = arr2.reshape(arr2.size)   # Convert higher dimension arrays into 1D
    arr2_1d = arr2.flatten()            # Same as above but more obvious what's happening; makes copy of original array
    arr2_1d = arr2.ravel()              # Same as above...; creates a view of the original array
                                        #; any modifications also affect original array
                                        
    array_repeat = np.repeat(arr2, 3, axis=1)           # arg1 = value, arg2 = number of repetitions; nice alternative to np.zeroes / np.ones
                                                        # main purpose; repeat entire arrays. Does repetitions in place, doesn't append to end
    array_unrepeat = np.unique(array_repeat, axis=1)    # only keep unique values (convert to Set of sorts)
    array_diag = np.diagonal(arr2, offset=0)            # array of only the diagonals; offset is above and below
    
    arr3 = np.swapaxes(arr2, 0, 1)      # swap axis 0 with axis 1
    arr3 = arr2.transpose(1, 0)         # exact same thing
    arr3 = arr2.T                       # yet another way to transpose
    
    # Conversion and Storage
    ########################
    
    my_list = arr2.tolist()                             # turn array into list
    my_file = arr2.tofile("my_array.txt", sep=",")      # turn array into file, each element separated with commas

    # Matrix+ operations
    ####################
    simple_matrix_ops = (arr + arr2 - 2 * arr)  # arr * arr2 would do element-wise multiplication
    matrix_modulo = arr2 % arr          # modulo
    floor_division = arr2 // arr        # do division but round down to the nearest integer; results are ints
    floor_division = np.floor(arr2/arr) # do it but with numpy; results are floats instead of ints
    multiplied_matrices = np.matmul(arr, arr2)  # matrix multiplication
    
    
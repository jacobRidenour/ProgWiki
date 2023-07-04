# Python is dynamically typed, but not actually "typeless"

# Major built-in types:
# 1. Numerics
# 2. Sequences
# 3. Mappings
# 4. Classes
# 5. Instances
# 6. Exceptions

# Functions showed off here are not exhaustive, meant to be a straightforward reference/demonstration

################
# 1. Numerics
################

# 3 types: ints, floats, complex
# booleans are an int subtype
# convert floats to ints with float(int) and vice versa with int(float)
# exponentials: x to the power of y: pow(x, y) or x**y
# truncate a float: math.trunc(x)
# round a number to n digits: round(x[, n])
# check if a decimal place on a float is .0: (x).is_integer()


def numerics_showcase():
    x = 1
    x += 4
    return x


################
# 2. Sequences
################

# 3 types: lists, tuples, and ranges
# Additional sequence types for processing binary data & text strings
# Sequences can be mutable or immutable.
# Strings, sequences declared with (), or inline sequences are generally immutable

def sequences_showcase():
    print('The following represents common functions that can be done on sequences: typically lists, tuples, and ranges\n')
    
    list_showcase()
    tuple_showcase()
    range_showcase()
    str_showcase()
    
    print('Tuples and ranges are immutable. Mutable sequences like lists, however, are mutable, and support additional functions:')
    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]   # List
    composites = [4, 6, 8, 9, 10, 14, 18, 22, 24, 25, 26, 27, 28] # List
    x = 400
    i = 4
    # print('',)
    print('Assignment: primes[i] = x')
    print('Insert element: primes.insert(i, x)')
    print('Replace slice[i:j] with iterable t: primes[i:j] = t')
    print('Replace slice[i:j:k] with iterable t: primes[i:j:k] = t; NOTE t must have the same length as the slice it\'s replacing')
    print('Delete a slice: del primes[i:j]; equivalent to primes[i:j] = []')
    print('Delete a slice by steps: del primes[i:j:k]')
    print('Append to the end: primes.append(x)')
    print('Append this list to itself n times: primes *=  n')
    print('Remove first occurence of a specific item: primes.remove(x)')
    print('Remove all items: primes.clear(); equivalent to del primes[:]')
    print('Create a shallow copy: primes.copy()')
    print('Extend list with another list: primes.extend(composites); equivalent to primes += composites')
    print('Retrieve the item from the end (or at index i) and remove from the list: primes.pop() or primes.pop(i)')
    print('Reverse the order of the list: primes.reverse()')
    print()
    
    print('Additional functions supported by Lists:')
    print('list.sort(*, key, reverse=False) - sort list in place using only < comparisons')

def list_showcase():
    my_list = [2, 4, 6, 8, 10]
    my_other_list = [3, 7, 9]
    x = 4
    n = 2
    
    print('LISTS IN PYTHON\n---------------')
    
    # You can print a list like so:
    # print('list my_list:', my_list)
    
    # You can also just do:
    # print(s)
    
    # But if you want say commas separating all the values, you can do:
    print('list my_list:', ', '.join(str(i) for i in my_list))
    # ', '.join(str(x)) joins strings of elements in s, using , as a separator
    
    print('list my_other_list:', ', '.join(str(i) for i in my_other_list))
    
    print('x is', x)
    print('n is', n)

    print()
    print('List functions:')
    print('x in my_list:', x in my_list)            # True
    print('x not in my_list:', x not in my_list)    # False
    print('my_list + my_other_list; add my_other_list to the end of my_list:', my_list + my_other_list)     # [2, 4, 6, 8, 10, 3, 7, 9]
    print('my_list * n; add list my_list to itself n times; equivalent to my_list *= n:', my_list * n)      # [2, 4, 6, 8, 10, 2, 4, 6, 8, 10]
    print('my_list[2]; third element in my_list: ', my_list[2])             # 6
    print('my_list[1:4]; slice of my_list from index 1 to 4 (exlusive):', my_list[1:4])         # [4, 6, 8]
    print('my_list[1:5:2]; slice of my_list from index 1 to 5 with step 2:', my_list[1:5:2])    # [4, 8]
    print('len(my_list):', len(my_list))    # 5
    print('min(my_list):', min(my_list))    # 2
    print('max(my_list):',max(my_list))     # 10
    print('my_list.index(4):', my_list.index(4))       # 1 (index of 4)
    print('my_list.count(2):', my_list.count(2))       # 1 (number of occurences of 2)
    print()

def tuple_showcase():
    # Commas are the magic that makes tuples, not the parentheses
    my_tuple = (1, 2, 3, 4, 5)
    my_other_tuple = (6, 7, 8)
    x = 3
    n = 2

    print('TUPLES IN PYTHON\n----------------')

    print('tuple my_tuple:', ', '.join(str(i) for i in my_tuple))
    print('tuple my_other_tuple:', ', '.join(str(i) for i in my_other_tuple))
    
    print('x is', x)
    print('n is', n)
    
    print()
    print('Tuple functions:')
    print('x in my_tuple:', x in my_tuple)              # True
    print('x not in my_tuple:', x not in my_tuple)      # False
    print('my_tuple + my_other_tuple:', my_tuple + my_other_tuple)  # (1, 2, 3, 4, 5, 6, 7, 8)
    print('my_tuple * n:', my_tuple * n)            # (1, 2, 3, 4, 5, 1, 2, 3, 4, 5)
    print('my_tuple[2]:', my_tuple[2])              # 3
    print('my_tuple[1:4]:', my_tuple[1:4])          # (2, 3, 4)
    print('my_tuple[1:5:2]:', my_tuple[1:5:2])      # (2, 4)
    print('len(my_tuple):', len(my_tuple))          # 5
    print('min(my_tuple):', min(my_tuple))          # 1
    print('max(my_tuple):', max(my_tuple))          # 5
    print('my_tuple.index(4):', my_tuple.index(4))  # 3
    print('my_tuple.count(2):', my_tuple.count(2))  # 1
    print()

def range_showcase():
    # Ranges are most commonly used in for loops
    my_range = range(1, 6)
    my_other_range = range(6, 9)
    my_one_parameter_range = range(4) # Range that stops at 4
    my_stepped_range = range(0, 10, 2) # From 0 to 10, increment by 2 each time
    x = 3
    n = 2

    print('RANGES IN PYTHON\n----------------')

    print('range my_range:', ', '.join(str(i) for i in my_range))
    print('range my_other_range:', ', '.join(str(i) for i in my_other_range))
    
    print('x is', x)
    print('n is', n)

    print()
    print('Range functions:')
    print('x in my_range:', x in my_range)          # True
    print('x not in my_range:', x not in my_range)  # False
    print('list(my_range + my_other_range: ERROR - operator + not supported for ranges', )
    print('list(my_range * my_other_range: ERROR - operator * not supported for ranges', )
    print('my_range[2]:', my_range[2])                  # 3
    print('my_range[1:4]:', list(my_range[1:4]))        # [2, 3, 4]
    print('my_range[1:5:2]:', list(my_range[1:5:2]))    # [2, 4]
    print('len(my_range):', len(my_range))
    print()

def str_showcase():
    # No separate char type in Python
    # Strings are immutable
        # However you can construct strings from fragments with str.join() or io.StringIO
    # Declare with '' - free embedded "" allowed (vice versa for those declared with "")
    # If there is only whitespace between two strings on the same line they will be implicitly combined
    
    # Implicitly construct a string object
    my_str = ""
    
    # Explicitly construct a string object
    my_str = str(4)
    my_str = str(b"RedGlockenspiel", 'utf-8', 'strict')
    # b prefix is necessary; middle parameter is encoding, last is errors (both optional)
    # if neither encoding/errors provided, str(object) returns type(object).__str__(object)
    # implicitly exists for all objects but should be overriden if you want your object convertible to string
    # The most common encodings will be utf-8 or ascii
    
    print('Original value of my_str:', my_str)
    
    print('String functions:')
    print('Set first word to capital and the rest lowercase; my_str.capitalize():', my_str.capitalize())
    print('Adjust casing of the whole string with my_str.upper() or my_str.lower():', my_str.upper(), my_str.lower())
    print('Get casefolded string; my_str.casefold():', my_str.casefold())
    print('Swap upper and lowercase characters; my_str.swapcase():', my_str.swapcase())
    print('Set Your String to Title Case with my_str.title() or my_str.capwords() if it has apostrophes:', my_str.title())
    print('Center your string to a specified width and (optional) fill character; my_str.center(width, fillchar):', my_str.center(12, ','))
    print('Count occurences of character with optional start/end; my_str.count(char, start, end):', my_str.count('e', 0, -1))
    print('Change encoding; my_str.encode(encoding='', errors=''):', my_str.encode('utf-8'))
    print('Check if string ends with specified character, optional start/end; my_str.endswith(char, start, end)', my_str.endswith('s'))
    print('Find first occurrence of character with optional start/end; my_str.find(substr, start, end):', my_str.find('e', 1, -1))
    # print('You can do the same with my_str.index(sub, start, end), but it returns ValueError if substr not found:', my_str.index('x')) # Returns ValueError substring not found
    print('Find last occurrence of character with optional start/end; my_str.rfind(substr, start, end):', my_str.rfind('e', 1, -1))
    # print('You can do the same with my_str.rindex(sub, start, end), but it returns ValueError if substr not found:', my_str.index('x')) # Returns ValueError substring not found
    print('Strip x leading/trailing char(s) with my_str.lstrip() / my_str.rstrip(); removes whitespace if no arg provided:', my_str.lstrip('r'), my_str.rstrip('l'))
    print('Remove prefix or suffix with my_str.removeprefix('') or my_str.removesuffix(''):', my_str.removeprefix('red'), my_str.removesuffix('piel'))
    print('Adjust justification with optional fill character; my_str.ljust(width, fillchar), my_str.rjust(width, fillchar), my_str.center(width, fillchar):')
    print(my_str.ljust(20))
    print(my_str.center(20))
    print(my_str.rjust(20))
    
    
    print()
    print('strings support several "is x" functions:')
    print('isalnum(), isalpha(), isascii(), isdecimal(), isdigit(), isidentifier(), iskeyword(), islower(), isnumeric(),' )
    print('isprintable(), isspace(), istitle(), isupper()', )
    
    print()
    # print('printf() style string formatting is possible but should prefer to use my_str.format():')
    # Create placeholders in your string with {} {} or with position {0} {1}
    # May expand on this later...
    
################
# 3. Mappings
################

def mappings_showcase():
    print('mappings:')
    dict_showcase()
    
def dict_showcase():
    # Creation:
        # comma separated K-V pairs in braces
        # dict comprehension {}, {x: x ** 2 for x in range(10)}
        # type constructor
    d = {'one': 1, 'two': 2, 'four': 4}
    other_d = {'eight': 8,'twelve': 12, 'eleven': 11}
    
    print('dict functions: ')
    print('List of all keys; list(d):', list(d))
    print('# items in the dict; len(d):', len(d))
    print('Find an element; d[\'four\']:', d['four']) # Can also do assignment this way
    del d["four"]
    print('Delete an element; del d[\'four\']')
    iter(d) # iterator
    reversed(d) # reverse iterator
    d.clear() # remove all items
    d.get('one') # get the value for a key
    d.pop('one') # remove a specific item (arg required)
    d.popitem() # remove item (LIFO order)
    e = d | other_d # create new dict merging keys of dict and other; values of other_d take priority when both share keys
    # Can just update 'd' as follows: d |= other_d
    

################
# 4. Classes
################

# Automatic functions you can override
# str() - convert object to a string (implicitly called by print())
# __hash__ - hash calculation

# iterators are supported for objects in Python
# Object need container.__iter()__ defined, which returns an iterator object
# Multiple types of iterators are supported
# Iterator objects must support the following methods
    # iterator.__iter__() - needed for both containers & iterators to be used with the "for" and "in" statements
    # iterator.__next__() - returns the next item from the iterator; returns StopIteration exception at the end
# Easily/conveniently implement iterator protocol with __generator__() method


################
# 5. Instances
################


################
# 6. Exceptions
################





# List Comprehensions (instead of loops)
# Generators
# Decorators
# Context managers
# Magic methods
# metaclasses

# Immutable Sequences
## Strings vs. Unicode vs. Tuples

# Mutable sequences
## Lists

# Mappings -> Dictionaries
## Mappings are not ordered

# Use of ellipses ...

# Modules (large libraries etc.)
# Files data types called with open()/close()
# Internal Types (used by interpreter)


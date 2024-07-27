
# hash function
def hash_prime(k, m):
    return k % m

def hash_h1(k, m):
    return hash_prime(k, m)

def hash_h2(k, m_prime):
    return 1 + (k % m_prime)

# Initialize the hash table with None values
table_size = 13
hash_table = [None] * table_size

# List of random numbers (keys)
keys = [369, 119, 287, 712, 141, 503, 186, 295, 528, 625]

# linear probing
def linear_probing(key, table, m):
    i = 0
    while True:
        index = (hash_prime(key, m) + i) % m
        if table[index] is None:
            table[index] = key
            print(f'h\'({key}) = ({hash_prime(key, table_size)} + {i}) mod {table_size} = {index}')
            return index, i
        else:
            print(f'Collision: h\'({key}) = ({hash_prime(key, table_size)} + {i}) mod {table_size} = {index}; try index ({index} + 1) mod {table_size} = {(index+1) % 13}')
            i += 1
            #print(f'Index {index} is occupied by {hash_table[i]}. Trying next index mod 13.')
            #print(f"Collision detected for key {key} at position {index}. Trying next position.")

def quadratic_probing(key, table, m, c1, c2):
    i = 0
    while True:
        index = (hash_prime(key, m) + c1 * i + c2 * i) % m
        if table[index] is None:
            table[index] = key
            print(f'index({key}) = ({hash_prime(key, table_size)} + {c1} * {i} + {c2} * {i}) mod {table_size} = {index}')
            return index, i
        else:
            print(f'Collision: index({key}) = ({hash_prime(key, table_size)} + {c1} * {i} + {c2} * {i}) mod {table_size} = {index}; try index ({index} + 1) mod {table_size} = {(index+1) % 13}')
            i += 1
            #print(f'Index {index} is occupied by {hash_table[i]}. Trying next index mod 13.')
            #print(f"Collision detected for key {key} at position {index}. Trying next position.")

def double_hashing(key, table, m, m_prime):
    i = 0
    while True:
        h1 = hash_h1(key, m)
        h2 = hash_h2(key, m_prime)
        index = (h1 + i * h2) % m
        if table[index] is None:
            table[index] = key
            print(f'index({key}) = (({key} mod {m}) + {i} * (1 + ({key} mod {m_prime}))) mod {m} = {index}')
                  #h1({key}) = ({h1}) + {i} * h2({key}) = {h2}) mod {m} = {index}')
            return index, i
        else:
            print(f'Collision: index({key}) = (({key} mod {m}) + {i} * (1 + ({key} mod {m_prime}))) mod {m} = {index}'
                  + f'\n try index (({key} mod {m}) + {i+1} * (1 + ({key} mod {m_prime}))) mod {m} = {(h1 + (i+1) * h2) % m}'
                  )
            
            #print(f'Collision: h1({key}) = {h1} + {i} * h2({key}) = {h2} mod {m} = {index}; try index ({index} + 1) mod {m} = {(index+1) % m}')

            i += 1

for key in keys:
    print(f'{hash_prime(key, table_size)} + ')

# Insert keys into the hash table using linear probing
for key in keys:
    #index, i = linear_probing(key, hash_table, table_size)
    #index, i = quadratic_probing(key, hash_table, table_size, 11, 17)
    index, i = double_hashing(key, hash_table, table_size, table_size-1)

# Print the final hash table
print("Final Hash Table:", hash_table)
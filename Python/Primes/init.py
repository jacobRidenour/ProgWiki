from math import sqrt
import sys
import random

def redirect_output_to_file(file_name):
    sys.stdout = open(file_name, 'w')
    
def restore_stdout():
    sys.stdout.close()
    sys.stdout = sys.__stdout__

def sieve_of_eratosthenes(stop_point):
    is_prime = [True] * (stop_point + 1)
    is_prime[0] = is_prime[1] = False

    current_prime = 2
    print('current prime is', current_prime)

    while current_prime <= stop_point:
        if is_prime[current_prime]:
            # mark all multiples as composite
            for multiple in range(current_prime * 2, stop_point + 1, current_prime):
                if (is_prime[multiple] == True):
                    print(multiple, end=' ')
                is_prime[multiple] = False
        current_prime += 1
        print('\ncurrent prime is', current_prime)

    primes = [i for i in range(2, stop_point + 1) if is_prime[i]]
    
    return primes

def is_prime_fermat(N, k=16):
    if N <= 1:
        return False

    # Check for small values of N
    if N <= 3:
        return True

    for _ in range(k):
        a = random.randint(2, N - 2)  # Pick a random integer between 2 and N - 2
        print('random number is', a)
        power = pow(a, N-1)
        result = pow(a, N - 1, N)
        #print(f'a^(N-1) mod N =', a, '^(', N-1, ') mod', N, '=', result)
        print(f'a^(N-1) mod N = {a}^({N-1}) mod {N} = {result}')
        if result != 1 % N:
            return False

    return True

def int_to_powers_of_two(N, expand=False):
    powers = []
    exponent = 0

    while N > 0:
        if N % 2 == 1:
            powers.append(exponent)
        N //= 2
        exponent += 1

    if expand:
        for i in range(len(powers)):
            powers[i] = pow(2, powers[i])
        return powers
    else:
        return powers

def extended_gcd(a, b):
    if b == 0:
        return (1, 0, a)
    else:
        print(f'gcd({b}, {a} mod {b})')
        x, y, d = extended_gcd(b, a % b)
        print(f'returning {y}, {x-(a//b)*y}, {d}')
        return (y, x - (a // b) * y, d)

def mod_inverse(g, phi_n):
    x, y, d = extended_gcd(g, phi_n)
    print(f'(x,y,d) = {x}, {y}, {d}')
    
    if d == 1:
        # Ensure the result is positive and less than phi(n)
        print(f'the inverse is ({x} % {phi_n} + {phi_n}) % {phi_n}')
        inverse = (x % phi_n + phi_n) % phi_n
        return inverse, x, y
    else:
        raise ValueError("The modular inverse does not exist.")

def init():
    redirect_output_to_file("out.txt")
    
    N = 59
    
    #prime_numbers = sieve_of_eratosthenes(N)
    
    #result = is_prime_fermat(N)
    #print(f"{N} is prime: {result}")
    
    # twos = int_to_powers_of_two(N)
    # print(twos)
    # twos = int_to_powers_of_two(N, True)
    # print(twos)
    
    # for k in range(len(twos)):
    #     exp = pow(2, twos[k])
    #     result = pow(776, exp, 997)
    #     print(f'{result}')
    
    phi = 986040
    g = 59
    inverse, x, y = mod_inverse(g, phi)
    print(f"Linear combination: {g}*({x}) + {phi}*({y}) = {g*x + phi*y}")
    print(f"The modular multiplicative inverse of {g} mod {phi} is {inverse}")
    
    C = 506574
    h = 584939
    n = 998027
    M = pow(C, h, n)
    
    
    restore_stdout()
    
    
    

init()
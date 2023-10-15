from math import sqrt
import sys
import random
import sympy

def modexp(a, b, c):
    result = 1  # Initialize the result

    while b > 0:
        if b % 2 == 1:
            # If b is odd, multiply result by a modulo c
            result = (result * a) % c

        # Square a modulo c and halve b
        a = (a * a) % c
        b //= 2

        # Print the current step
        #print(f"a^b mod c = {a}^{b} mod {c} = {result}")

    return result


def init():
    # givens
    g = 59
    p = 991
    q = 997
    M = 506574
    h = 584939
    
    n = p*q
    phi_n = (p-1)*(q-1)
    
    #final_result = modexp(M, g, n)
    #result_pow = pow(M, g, n)
    
    a = 506574
    b = 916874
    c = 985584
    d = 40087
    e = 435667
    modulus = 988027
    
    C = modexp(M, g, n)    
    print(f"Ciphertext C (modexp) = {M}^{g} mod {n} = {C}")
    
    M = 1
    
    steps = []

    while h > 0:
        if h % 2 == 1:
            steps.append(f'h is not even; h = {h}')
            M = (M * C) % n
            steps.append(f"M = ({M} * {C}) mod {n} = {M}")
        steps.append(f"C = ({C} * {C}) mod {n} = {C}")
        C = (C * C) % n
        steps.append(f'floor(h/2) = {h // 2}')
        h = h // 2
        
        

    # Display each step
    for step in steps:
        print(step)

    # The final result is in M
    print("Decrypted Message (M):", M)
    
    # Split the string into a list of decimal values
    
    
    
    # assuming M is an int
    M = str(M)
    M_dec = [int(char) for char in str(M)]
    message = ''.join(chr(value) for value in M_dec)
    print(message)
    
    # Convert each decimal value to its ASCII character and join them to form the plaintext
    #plaintext = ''.join(chr(value) for value in decimal_values)
    # Print the decoded plaintext
    #print('Decoded text:', plaintext)
    
init()
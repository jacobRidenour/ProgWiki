from BuiltInTypes import *
from src.py1 import *
from src.ContextManagers import *

def __init__():
    """Describe what your function does here"""
    numerics_showcase()
    sequences_showcase()
    
    # Like in C, we can call other "naked" functions we include without any
    # prefix signifying that they're from another file
    context_managers_showcase()
    
    
__init__()
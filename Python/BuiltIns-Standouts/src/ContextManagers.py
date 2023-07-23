# Context managers - the with keyword
# - Properly manage certain types of resources (files, network connections, locks, database connections)
# - Ensure that resources are acquired & released in a controlled mannger

import threading
import sqlite3
import queue

# This whole class is redundant, Python's queue class is thread-safe
class ThreadSafeQueue:
    def __init__(self):
        self.queue = queue.Queue()
        self.lock = threading.Lock()

    def __enter__(self):
        self.lock.acquire()
        return self.queue

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.lock.release()
        
    def put(self, item):
        with self.lock:
            self.queue.put(item)

    def get(self):
        with self.lock:
            return self.queue.get()

    def empty(self):
        with self.lock:
            return self.queue.empty()

    def size(self):
        with self.lock:
            return self.queue.qsize()

    def clear(self):
        with self.lock:
            self.queue.queue.clear()

    def peek(self):
        with self.lock:
            if not self.queue.empty():
                return self.queue.queue[0]

    def contains(self, item):
        with self.lock:
            return item in self.queue.queue

    def get_all(self):
        with self.lock:
            return list(self.queue.queue)

def context_managers_showcase():
    print()
    # cm_file()
    cm_threading()
    cm_db()
    
    
    # User-defined classes can implement context managers by implementing __enter__() and __exit__(), e.g.
    with ThreadSafeQueue() as queue:
        # queue can be operated in a thread safe manner
        queue.put(10)
        item = queue.get()
        print(item)
        
    print('queue lock has been released\n')
        
        
    
    
def cm_file():
    with open("file.txt") as file:
        print('doing stuff to a file')
    # Do file operations
    # File automatically closed at the end of this block
    print('context left, file has been closed\n')
    
def cm_threading():
    # Create a lock for the thread
    lock = threading.Lock()
    
    with lock:
        # Do critical thing
        print('ha ha, thread is locked')
        # lock acquired & released automatically at end of block
        
    # now we're outside of the thread
    print('lock released')
    
def cm_db():
    with sqlite3.connect("database.db") as connection:
        print('doing database operations...')
        
    # connection has been automatically closed
    print('done doing database things. connection closed\n')

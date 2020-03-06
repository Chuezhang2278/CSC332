import math
import timeit
import time
import threading
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import Process, Queue 
import os

class Multi(): 
    def __init__(self):
        self.end = 2500
        self.start = 0
        self.Integer = 0
        self.Big = 0
        self.Count = 1
    
    def getBig(self):
        return self.Big
    
    def getInt(self):
        return self.Integer
    
    def setInt(self, n):
        self.Integer = n

    def countDivisors(self, n) :
        count = 0
        for i in range(1, (int)(math.sqrt(n)) + 1) : 
            if (n % i == 0) : 
                if (n / i == i) : 
                    count = count + 1
                else : 
                    count = count + 2        
        return count 

    def func(self, start, end, q):
        for i in range(start, end):
            if(self.getBig() <= self.countDivisors(i)):
                self.Big = self.countDivisors(i)
                self.Integer = i
            
        if(q.qsize() > 0):
            q.get()       
        q.put(self.Integer)
        
    def Threaded(self):
        processes = []
        q = Queue()
        for i in range(0,2):
            print("Process:", i+1)
            self.end = 5000 * self.Count
            self.start = 5000 * (self.Count-1)
            self.Count += 1 
            p = Process(target=self.func, args=(self.start,self.end, q))
            processes.append(p)
        
        for p in processes:
            p.start()
        
        for p in processes:
            p.join()
        
        while not q.empty():
            print(q.get())
        
if __name__ == '__main__':
    start = timeit.default_timer()
    test = Multi()
    test.Threaded()
    
    stop = timeit.default_timer()
    execution_time = stop - start
    print("Program Executed in", execution_time, "Seconds")
import math
import timeit
import threading
from concurrent.futures import ThreadPoolExecutor

class Multi(): 
    def __init__(self):
        self.end = 100000
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

    def func(self, start, end):
        for i in range(start, end):
            if(self.getBig() <= self.countDivisors(i)):
                self.Big = self.countDivisors(i)
                self.setInt(i)

    def Threaded(self):
        threads = 1
        jobs = []
        for i in range(0, threads):
            print("Thread:", i+1, "Initializing")
            thread = threading.Thread(target=self.func, args = (self.start, self.end))
            jobs.append(thread)
        
        for j in jobs:
            j.start()
            
        for j in jobs:
            j.join()
        
        
start = timeit.default_timer()
test = Multi()
test.Threaded()
print(test.getInt())
stop = timeit.default_timer()
execution_time = stop - start
print("Program Executed in", execution_time, "Seconds")
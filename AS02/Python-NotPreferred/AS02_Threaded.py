import math
import timeit
import threading
from concurrent.futures import ThreadPoolExecutor

class Multi(): 
    def __init__(self):
        self.end = 0
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
                
    def Threaded(self,amount):
        threads = amount
        partition = 200000//amount
        jobs = []
        for i in range(0, threads):
            print("Thread:", i+1, "Initializing")
            self.end = partition * self.Count
            self.start = partition * (self.Count-1)
            self.Count += 1
            thread = threading.Thread(target=self.func, args=(self.start, self.end))
            jobs.append(thread)
        
        for j in jobs:
            j.start()
            
        for j in jobs:
            j.join()
        
test = Multi()
test2 = Multi()
test3 = Multi()
test4 = Multi()

start = timeit.default_timer() #1 threads
test.Threaded(1)
print(test.getInt(), "with", test.getBig(), "Divisors")
stop = timeit.default_timer()
execution_time = stop - start
print("Program Executed in", execution_time, "Seconds")      
        
start2 = timeit.default_timer() #2 threads
test2.Threaded(2)
print(test.getInt(), "with", test.getBig(), "Divisors")
stop2 = timeit.default_timer()
execution_time = stop2 - start2
print("Program Executed in", execution_time, "Seconds")
        
start3 = timeit.default_timer() #3 threads
test3.Threaded(3)
print(test.getInt(), "with", test.getBig(), "Divisors")
stop3 = timeit.default_timer()
execution_time = stop3 - start3
print("Program Executed in", execution_time, "Seconds")

start4 = timeit.default_timer() #4 threads
test4.Threaded(4)
print(test.getInt(), "with", test.getBig(), "Divisors")
stop4 = timeit.default_timer()
execution_time = stop4 - start4
print("Program Executed in", execution_time, "Seconds")
# SOURCES #
# a lot of stuff from geeksforgeeks, not necessarily for the code but for pictures
# friend helped for SSTF so code is different from the rest

import numpy as np
import random

size = 1000;
res = []
def FCFS(q , head): # no sort, just do 
    count = 0;
    for i in range(size):
        count += abs(q[i] - head)
        head = q[i]
    
    print("FCFS:", count)
    res.append(count)

def SSTF(q, head): #sort a and b, head pos -> min, traverse from min -> max
    count = 0
    temp = 0
    near = 0
    pos = head
    for i in range(size):
        near = abs(pos - q[i])
        temp = i
        for j in range(i, size):
            if(near > abs(pos - q[j])):
                temp = j
                near = abs(pos - q[j])
        count += near
        pos = q[temp]
        q[temp] = q[i]
        q[i] = pos
    
    print("SSTF:", count)
    res.append(count)

def SCAN(q,head): #basically SSTF but we append a 0 
    a = []
    b = []
    count = 0
    for i in range(size):
        if(q[i] < head):
            a.append(q[i])
        else:
            b.append(q[i])
    a.append(0)
    a.sort(reverse=True)
    b.sort()      
    c = a+b
    for i in range(len(c)):
        count += abs(head - c[i])
        head = c[i]
    
    print("SCAN:", count)
    res.append(count)

def SEESCAN(q,head): #opposite direction of SCAN, head pos -> largest -> go to 0 -> go up until some number < headpos
    a = []
    b = []
    count = 0
    for i in range(size):
        if(q[i] < head):
            a.append(q[i])
        else:
            b.append(q[i])
    b.sort() 
    b.append(0)
    a.sort()     
    c = b+a
    
    for i in range(len(c)):
        count += abs(head - c[i])
        head = c[i]
    
    print("C SCAN:", count)
    res.append(count)
 
def LOOK(q,fourhead): #opposite of SSTF
    head = fourhead
    a = []
    b = []
    count = 0
    for i in range(size):
        if(q[i] < head):
            a.append(q[i])
        else:
            b.append(q[i])
    b.sort() 
    a.sort(reverse = True)     
    c = b+a
    
    for i in range(len(c)):
        count += abs(head - c[i])
        head = c[i]
    
    print("LOOK:", count)
    res.append(count)
        
x = np.zeros(size, dtype = int) #allocating array space ahead of time
for i in range(size):
    x[i] = random.randint(0,9999)

print("enter head pos")
val = int(input())
print("head starting pos:", val, "\n")
FCFS(x,val)
SSTF(x,val)
SCAN(x,val)
SEESCAN(x,val)
LOOK(x,val)

if(res[0] == min(res)):
    print("\nFCFS is min:", res[0])
elif(res[1] == min(res)):
    print("\nSSTF is min:", res[1])
elif(res[2] == min(res)):
    print("\nSCAN is min:", res[2])
elif(res[3] == min(res)):
    print("\nC SCAN is min:", res[3])
elif(res[4] == min(res)):
    print("\nLOOK is min:", res[4])
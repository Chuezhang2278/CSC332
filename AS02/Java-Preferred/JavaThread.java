// #####Sources#####
// StackOverFlow
// JiaMingMa fellow student: https://github.com/jma8774/CSC332
// Geeks for Geeks

class JavaThread implements Runnable
{
    // Declaring my variables //
    private int end;
    private int start;
    private int Integer;
    private int Big;
    private int Count;

    public JavaThread()
    {
        this.end = 0;
        this.start = 0;
        this.Integer = 0;
        this.Big = 0;
        this.Count = 1;
    }
    // Done setting my variables //
    
    public int getInt() // lol i dont think i used getint func
    {
        return this.Integer;
    }

    public static int countDivisors(int n) // func for finding a numbers # of divisors
    {
        int count = 0;
        for(int i = 1; i <= Math.sqrt(n); i++)
        {
            if(n % i == 0)
            {
                if(n/i == i)
                {
                    count++;
                }
                else
                {
                    count = count + 2;
                }
            }
        }
        return count;
    }

    public void func(int start, int end) //Basically runs a for loop from a given start to end using divisor func
    {
        for(int i = start; i < end; i++)
        {
            if(this.Big <= countDivisors(i))
            {
                this.Big = countDivisors(i);
                this.Integer = i;
            }
        }
    }

    public void run(){ // Java yelled at me for not having this, i have no clue what this does. Thinks its to specify func to thread
        func(this.start, this.end);
    }

    public void Threads(int amount) throws InterruptedException // Java yelled at me for not having exception
    {
        int partition = 100000/amount;                          // HW specifies 100k numbers so 100k/thread amount
        Thread thread[] = new Thread[amount];                   // Initializing array for threads 
        for(int i = 0; i < threads;i++)                         // How many threads we gonna run
        {
            System.out.println("Thread " + (i+1) + " Initializing");
            this.end = partition * this.Count;                  // We giving a end and a start to work with using our function
            this.start = partition * (this.Count-1);            // 25k * 1 = end, 25k* 0 = start; 25k*2 = end, 25*1 = start; etc;
            this.Count++;                                       // count increment
            thread[i] = new Thread(this);                       // throwing jobs into array
            thread[i].start();                                  // starting thread
        }
        for(int j = 1; j <= amount;j++)
        {
            thread[j-1].join();                                 // closing thread
        }

        System.out.println(this.Integer + " Is the largest Divisor with " + this.Big + " Divisors");
        
    }
    public static void main(String args[]) throws InterruptedException // Java yelled at me again for not having exception here
    {
        long startTime1 = System.nanoTime();
        JavaThread solo = new JavaThread();
        solo.Threads(1);
        long endTime1 = System.nanoTime();
        System.out.println("Program executed in "+(endTime1-startTime1)/1000000 + " milliseconds\n");

        long startTime2 = System.nanoTime();
        JavaThread quad = new JavaThread();
        quad.Threads(4);
        long endTime2 = System.nanoTime();
        System.out.println("Program executed in "+(endTime2-startTime2)/1000000 + " milliseconds");
    }
}

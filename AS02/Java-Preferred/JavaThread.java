// #####Sources#####
// StackOverFlow
// JiaMingMa fellow student: https://github.com/jma8774/CSC332
// Geeks for Geeks

class JavaThread implements Runnable
{
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

    public int getInt()
    {
        return this.Integer;
    }

    public static int countDivisors(int n)
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

    public void func(int start, int end)
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

    public void run(){
        func(this.start, this.end);
    }

    public void Threads(int amount) throws InterruptedException
    {
        int threads = amount;
        int partition = 100000/amount;
        Thread thread[] = new Thread[amount];
        for(int i = 0; i < threads;i++)
        {
            System.out.println("Thread " + (i+1) + " Initializing");
            this.end = partition * this.Count;
            this.start = partition * (this.Count-1);
            this.Count++;
            thread[i] = new Thread(this);
            thread[i].start();
        }
        for(int j = 1; j <= amount;j++)
        {
            thread[j-1].join();
        }

        System.out.println(this.Integer + " Is the largest Divisor with " + this.Big + " Divisors");
        
    }
    public static void main(String args[]) throws InterruptedException
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
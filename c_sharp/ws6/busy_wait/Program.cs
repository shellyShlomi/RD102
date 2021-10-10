using System;
using System.Threading;
using System.Threading.Channels;
using System.Threading.Tasks;

namespace busy_wait
{

    class Program
    {
        static int globalDS = 0;
        static void Main(string[] args)
        {
            Thread producer_thread = new Thread(new ThreadStart(Producer));
            Thread consumer_thread = new Thread(new ThreadStart(Consumer));
            producer_thread.Start();
            consumer_thread.Start();

            Console.ReadKey();
        }

        static public void Consumer()
        {
            for (int i = 0; i < 100; ++i)
            {
                Thread.Sleep(100);
                while (0 == globalDS)
                {
                    Console.WriteLine("[CONSUMER] : waiting");
                }
                globalDS = 0;
                Console.WriteLine("[CONSUMER] : " + globalDS);
            }
        }

        static public void Producer()
        {
            for (int i = 0; i < 100; ++i)
            {
                while (globalDS == 1)
                {
                    Console.WriteLine("[PRODUCER] : waiting");
                }

                globalDS = 1;
                Console.WriteLine("[PRODUCER] : " + globalDS);
                Thread.Sleep(100);

            }
        }
    }
    
}


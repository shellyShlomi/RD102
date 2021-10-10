using System;
using System.Threading;

namespace LL_monitor
{
    class Program
    {

        static private ws2.List list = new ws2.List();
        static void Main(string[] args)
        {
            Thread consumer_thread = new Thread(Consumer);
            Thread consumer_thread1 = new Thread(Consumer);
            Thread consumer_thread2 = new Thread(Consumer);
            Thread producer_thread = new Thread(Producer);
            Thread producer_thread1 = new Thread(Producer);
            Thread producer_thread2 = new Thread(Producer);
            //Thread[] consumers = new Thread[4];
            //for (int i = 0; i < consumers.Length; ++i)
            //{
            //    consumers[i] = new Thread(r.Consumer); 
            //}

            producer_thread.Start();
            producer_thread1.Start();
            producer_thread2.Start();
            consumer_thread.Start();
            consumer_thread1.Start();
            consumer_thread2.Start();

            producer_thread.Join();
            producer_thread1.Join();
            producer_thread2.Join();
            consumer_thread.Start();
            consumer_thread1.Start();
            consumer_thread2.Start();
            Console.ReadKey();

        }



        static public void Producer()
        {
            for (int i = 0; i < 100; ++i)
            {
                Monitor.Enter(list);
                list.Push((string)("[PRODUCER] msg: " + i));
                Monitor.PulseAll(list);
                Monitor.Exit(list);

            }
            return;

        }

        static public void Consumer()
        {
            bool lockTaken;

            for (int i = 0; i < 100; ++i)
            {
                if (list.IsEmpty())
                {
                    //_ = Monitor.Wait(globalList);
                }
                try
                {
                    Monitor.TryEnter(list);
                    if (lockTaken)
                    {
                        Thread.Sleep(100);
                        Console.WriteLine($"[CONSUMER] {0}: {1}", i, list.Pop());
                        //Monitor.Exit(globalList);
                    }
                    else
                    {
                        Console.WriteLine("[CONSUMER] : waiting");
                    }
                }
                finally
                {
                    if (lockTaken)
                    {
                        lockTaken = false;
                        Monitor.Exit(list);
                    }
                }
            }
            return;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace LL_monitor
{
    public class Reader
    {

        private ws2.List globalList;
        private bool lockTaken;
        public Reader(ref ws2.List programGlobalVal)
        {
            this.globalList = programGlobalVal;
            lockTaken = false;
        }

        public void Consumer()
        {
            for (int i = 0; i < 100; ++i)
            {
                if (globalList.IsEmpty())
                {
                    //_ = Monitor.Wait(globalList);
                }
                try
                {
                    Monitor.TryEnter(globalList, ref lockTaken);
                    if (lockTaken)
                    {
                        Thread.Sleep(100);
                        Console.WriteLine($"[CONSUMER] {0}: {1}", i, globalList.Pop());
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
                        Monitor.Exit(globalList);
                    }
                }
            }
            return;
        }
    }
}

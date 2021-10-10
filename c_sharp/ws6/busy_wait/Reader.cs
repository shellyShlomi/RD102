using System;
using System.Threading;

namespace busy_wait
{
    public class Reader
    {
        private int globalVal;

        public Reader(in int globalDS)
        {
            globalVal = globalDS;
        }

        public void Consumer()
        {
            for (int i = 0; i < 100; ++i)
            {
                Thread.Sleep(100);
                while (0 == globalVal)
                {
                    Console.WriteLine("[CONSUMER] : waiting");
                }
                globalVal = 0;
                Console.WriteLine("[CONSUMER] : " + globalVal);
            }
        }

    }
}

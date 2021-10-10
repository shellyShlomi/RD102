using System;
using System.Threading;

namespace busy_wait
{
    public class Writer
    {
        private int globalVal;

        public Writer(in int globalDS)
        {
            this.globalVal = globalDS;
        }

        public void Producer()
        {
            for (int i = 0; i < 100; ++i)
            {
                while (globalVal == 1)
                {
                    Console.WriteLine("[PRODUCER] : waiting");
                }

                globalVal = 1;
                Console.WriteLine("[PRODUCER] : " + globalVal);
                Thread.Sleep(100);

            }
        }
    }
}

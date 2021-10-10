using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace LL_monitor
{
    public class Writer
    {
        private ws2.List globalList;

        public Writer(ref ws2.List programGlobalVal)
        {
            this.globalList = programGlobalVal;
        }

        public void Producer()
        {
            for (int i = 0; i < 100; ++i)
            {
                Monitor.Enter(globalList);
                globalList.Push((string)("[PRODUCER] msg: " + i));
                Monitor.PulseAll(globalList);
                Monitor.Exit(globalList);

            }
            return;

        }
    }
}

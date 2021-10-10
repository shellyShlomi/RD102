using System;
using System.IO;
using System.IO.Pipes;
using System.Threading;

namespace AnonymuspipeClientI
{
    class PipeClient
    {
        static void Main(string[] args)
        {
            if (args.Length > 1)
            {

                using PipeStream pipeClientI =
                    new AnonymousPipeClientStream(PipeDirection.In, args[0]);
                using PipeStream pipeClientO =
                     new AnonymousPipeClientStream(PipeDirection.Out, args[1]);
                using StreamReader sr = new StreamReader(pipeClientI);
                using StreamWriter sw = new StreamWriter(pipeClientO);
                sw.AutoFlush = true;

                // Display the read text to the console
                string temp = "";

                // Read the server data and echo to the console.
                int i = 0;
                while ((temp = sr.ReadLine()) != null && i < 10)
                {
                    Console.WriteLine("[CLIENT] recv:\t" + temp);
                    sw.WriteLine("pong");
                    ++i;
                }
            }
            Console.Write("[CLIENT] end...");
        }
    }
}

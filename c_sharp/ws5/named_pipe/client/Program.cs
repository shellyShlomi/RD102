using System;
using System.IO;
using System.IO.Pipes;
using System.Threading;

namespace client
{
    class Program

    {
        static void Main(string[] args)
        {
            ReceiveByteAndRespond();
        }

        private static void ReceiveByteAndRespond()
        {
            using (NamedPipeClientStream namedPipeClient = new NamedPipeClientStream("test-pipe"))
            {
                namedPipeClient.Connect();

                int todofor = 10;

                while (todofor != 0)
                {
                    StreamWriter writer = new StreamWriter(namedPipeClient);
                    writer.WriteLine("PING ");
                    writer.Flush();
                    Thread.Sleep(100);

                    StreamReader reader = new StreamReader(namedPipeClient);
                    string FromClient = reader.ReadLine();
                    Console.WriteLine(FromClient + (10 - todofor));

                    --todofor;

                }


            }
        }
    }
}

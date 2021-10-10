using System;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Threading;

namespace Server
{
    class Program
    {
        static void Main(string[] args)
        {
            SendByteAndReceiveResponse();
        }
        private static void SendByteAndReceiveResponse()
        {


            using (NamedPipeServerStream namedPipeServer = new NamedPipeServerStream("test-pipe"))
            {
                namedPipeServer.WaitForConnection();
                int todofor = 10;

                while (todofor != 0)
                {
                    Thread.Sleep(10);
                    StreamReader reader = new StreamReader(namedPipeServer);
                    string FromClient = reader.ReadLine();
                    Console.WriteLine(FromClient + (10 - todofor));
                    Thread.Sleep(1000);
                    StreamWriter writer = new StreamWriter(namedPipeServer);
                    writer.WriteLine("PONG ");
                    writer.Flush();
                    --todofor;

                }
            }
        }
    }
}

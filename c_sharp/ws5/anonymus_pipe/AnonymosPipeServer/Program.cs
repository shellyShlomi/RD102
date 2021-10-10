using System;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
using System.Threading;

namespace AnonymosPipeServer
{
    class PipeServer
    {
        static void Main(string[] args)
        {
            Process pipeClient = GeneratClientProcess(out AnonymousPipeServerStream pipeServerO,
                                                    out AnonymousPipeServerStream pipeServerI,
                "..\\..\\..\\..\\AnonymusPipeClient\\bin\\Debug\\netcoreapp3.1\\AnonymusPipeClient.exe");

            try
            {
                // Read user input and send that to the client process.
                using StreamWriter sw = new StreamWriter(pipeServerO);
                sw.AutoFlush = true;
                using StreamReader sr = new StreamReader(pipeServerI);
                // Send a 'sync message' and wait for client to receive it.

                string temp = "";

                while (temp != null)
                {
                    sw.WriteLine("ping");
                    // Send the console input to the client process.
                    temp = sr.ReadLine();
                    Console.WriteLine("[SERVER] recv:\t" + temp);
                    Thread.Sleep(1000);
                }
            }
            // Catch the IOException that is raised if the pipe is broken
            // or disconnected.
            catch (IOException e)
            {
                Console.WriteLine("[SERVER]" +
                    " Error: {0},{1}", e.Message, 1);
            }

            pipeClient.WaitForExit();
            pipeClient.Close();
            Console.Write("[SERVER] end...");
        }

        static public Process GeneratClientProcess(out AnonymousPipeServerStream pipeServerO, out AnonymousPipeServerStream pipeServerI, string fileName)
        {
            Process pipeClient = new Process();

            pipeClient.StartInfo.FileName = fileName;
            pipeServerO = new AnonymousPipeServerStream(PipeDirection.Out, HandleInheritability.Inheritable);

            pipeServerI = new AnonymousPipeServerStream(PipeDirection.In, HandleInheritability.Inheritable);
           
            // Pass the client process a handle to the server.
            pipeClient.StartInfo.Arguments = pipeServerO.GetClientHandleAsString();
            pipeClient.StartInfo.Arguments += " ";
            pipeClient.StartInfo.Arguments += pipeServerI.GetClientHandleAsString();

            pipeClient.StartInfo.UseShellExecute = false;
            pipeClient.Start();

            pipeServerO.DisposeLocalCopyOfClientHandle();
            pipeServerI.DisposeLocalCopyOfClientHandle();

            return pipeClient;
        }
    }
}
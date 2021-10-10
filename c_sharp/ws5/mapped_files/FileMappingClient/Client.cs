
using System;
using System.IO.MemoryMappedFiles;
using System.Threading;
using System.IO;

namespace FileMappingClient
{
    public class Client
    {

        private int num;

        private Semaphore semServer;
        private Semaphore semClient;
        private Semaphore semClientStart;
        private Semaphore semClientConecteToServer;

        private MemoryMappedFile file;
        private MemoryMappedViewStream stream;
        public Client()
        {
            this.num = 10;
            this.semServer = Semaphore.OpenExisting("sem_server");
            this.semClient = Semaphore.OpenExisting("sem_client");
            this.semClientStart = Semaphore.OpenExisting("semClientStart");
            this.semClientConecteToServer = Semaphore.OpenExisting("semServerConection");
        }

        public void OpenFile()
        {
            file = MemoryMappedFile.OpenExisting("../../../../ping-pong");
            return;
        }

        public void CreateStream()
        {
            stream = file.CreateViewStream();
            return;
        }

        public void ConectClientToServer()
        {
            semClientConecteToServer.Release();
            Console.WriteLine("Client is conected");

            semClientStart.WaitOne();

            OpenFile();
            CreateStream();
            return;
        }
        public void RunClient()
        {
            ConectClientToServer();

            for (int i = 0; i < num; ++i)
            {
                semClient.WaitOne();

                BinaryWriter writer = new BinaryWriter(stream);
                string text = "ping " + i;
                writer.Write(text);

                semServer.Release();
                semClient.WaitOne();

                BinaryReader reader = new BinaryReader(stream);
                Console.WriteLine(reader.ReadString());

            }


            Console.WriteLine("RunClient done...");
            Console.ReadKey();
            return;

        }
    }
}

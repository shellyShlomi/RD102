using System;
using System.IO.MemoryMappedFiles;
using System.Threading;
using System.IO;

namespace FileMappingServer
{
    public class Server
    {

        private int num;
        private Semaphore semServer;
        private Semaphore semClientIsConecteToServer;
        private Semaphore semClient;
        private Semaphore semClientStart;
        private MemoryMappedFile file;
        private MemoryMappedViewStream stream;
        public Server()
        {
            num = 10;
            this.semClientStart = new Semaphore(initialCount: 0, maximumCount: 1, name: "semClientStart");
            this.semClientIsConecteToServer = new Semaphore(initialCount: 0, maximumCount: 1, name: "semServerConection");
            this.semServer = new Semaphore(initialCount: 0, maximumCount: 1, name: "sem_server");
            this.semClient = new Semaphore(initialCount: 0, maximumCount: 1, name: "sem_client");
        }

        public void OpenFile()
        {
            file = MemoryMappedFile.CreateNew("../../../../ping-pong", 10000);
            return;
        }

        public void CreateStream()
        {
            stream = file.CreateViewStream();
            return;
        }
        public void InitialSenClose()
        {

            semClientIsConecteToServer.Close();
            semClientStart.Close();
            return;
        }

        public void ConectServerToClient()
        {
            Console.WriteLine("Server wait for conection");
            semClientIsConecteToServer.WaitOne();

            OpenFile();

            Thread.Sleep(2000);
            semClientStart.Release();

            CreateStream();
            InitialSenClose();
            return;
        }

        public void RunServer()
        {
            ConectServerToClient();
         
            for (int i = 0; i < num; ++i)
            {
                semClient.Release();
                semServer.WaitOne();

                BinaryReader reader = new BinaryReader(stream);
                Console.WriteLine(reader.ReadString());
                Thread.Sleep(2000);

                BinaryWriter writer = new BinaryWriter(stream);
                string text = "pong " + i;
                writer.Write(text);

                semClient.Release();

            }

            Console.WriteLine("RunServer done...");
            Console.ReadKey();
            return;

        }
    }
}

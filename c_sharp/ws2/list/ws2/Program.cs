using System;

namespace ws2
{
    class Program
    {
        static void Main()
        {
            TestList t1 = new TestList();
            t1.TestPushAndPopList();
            return;
        }
    }
    class TestList
    {
        const int SIZE = 10;

        public void TestPushAndPopList()
        {
            List list = new List();
            object[] arr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            Console.WriteLine("\nTestPushList\n");

            Console.WriteLine(value: list.IsEmpty());

            Console.WriteLine(value: list.Count());


            Console.WriteLine("\nPush\n");
            for (int i = 0; i < SIZE; ++i)
            {
                list.Push(arr[i]);
                Console.WriteLine("i is :" + i + " val is : {0} ", arr[i] + " Count() is : " + list.Count());

            }

            Console.WriteLine("\nPop\n");
            for (int i = 0; i < SIZE; ++i)
            {
                Console.WriteLine("Item pop from List : {0}", list.Pop());
                Console.WriteLine("Count() is : " + list.Count() );
            }

            for (int i = 0; i < SIZE; ++i)
            {
                list.Push(arr[i]);
            }


            Console.WriteLine("\nClear\n");

            list.Clear();
            Console.WriteLine("Item peek after Clear : {0}", list.Peek());
            Console.WriteLine("Item pop after Clear : {0}", list.Pop());


            Console.WriteLine("\nmaking list for foreach\n");

            for (int i = 0; i < SIZE; ++i)
            {
                list.Push(arr[i]);
                Console.WriteLine("i is :" + i + " val is : {0} ", arr[i] + " Count() is : " + list.Count());
            }

            Console.WriteLine("\nforeach print\n");
            foreach (int n in list)
            {
                Console.WriteLine(n);
            }
            return;
        }
    }
}



namespace ws2
{
    class Program
    {
        static void Main()
        {
            // TestStack t1 = new TestStack();
            //t1.TestCreatStack();
            //t1.TestPushAndPopStack();
            Tests.ComplexShapeTests t1 = new Tests.ComplexShapeTests();
            //TestShape t2_shape = new TestShape();
            //Console.WriteLine("\nshapes collection\n");

            //t2_shape.TestComplexShape();
            //Console.WriteLine("\nRectangle\n");
            //t2_shape.TestRec();
            //Console.WriteLine("\nCircle\n");
            //t2_shape.TestCir();
        }
    }

    /*
    class TestStack
    {
        const int SIZE = 10;

        public void TestCreatStack()
        {
            Stack s = new Stack();

            Console.WriteLine("defult values :");
            Console.WriteLine(value: s.StackCapacity());
            Console.WriteLine(value: s.StackSize());
            Console.WriteLine(value: s.StackIsEmpty());

            Stack s1 = new Stack(100);
            Console.WriteLine("size 100 values :");

            Console.WriteLine(value: s1.StackCapacity());
            Console.WriteLine(value: s1.StackSize());
            Console.WriteLine(value: s1.StackIsEmpty());
        }


        public void TestPushAndPopStack()
        {
            Stack s = new Stack();
            object[] arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            Console.WriteLine("TestPushStack");

            Console.WriteLine(value: s.StackIsEmpty());

            Console.WriteLine(value: s.StackSize());


            for (int i = 0; i < SIZE; ++i)
            {
                s.StackPush(arr[i]);
                Console.WriteLine("Item peek from Stack : {0}",s.StackPeek());
                Console.WriteLine("StackSize() is : " + s.StackSize() + " i is :" + i);
            }

            s.StackClear();
            Console.WriteLine("Item peek from Stack : {0}", s.StackPeek());

            for (int i = 0; i < SIZE; ++i)
            {
                s.StackPush(arr[i]);
                Console.WriteLine("Item peek from Stack : {0}", s.StackPeek());
                Console.WriteLine("StackSize() is : " + s.StackSize() + " i is :" + i);
            }



        }
    }*/
}

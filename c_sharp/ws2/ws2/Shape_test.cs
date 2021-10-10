using System;

namespace ws2
{
    class TestShape
    {
        const int SIZE = 10;

        public void TestRec()
        {
            Rectangle r = new ws2.Rectangle();
            Rectangle r1 = new ws2.Rectangle(2.2, 2.2);
            Rectangle r2 = new ws2.Rectangle("red",false,2.2, 2.2);

            Console.WriteLine("r" + r.ToString());
            Console.WriteLine("r1" + r1.ToString());
            Console.WriteLine("r2" + r2.ToString());

        }

        public void TestCir()
        {
            Circle c = new ws2.Circle();
            Circle c1 = new ws2.Circle(4);
            Circle c2 = new ws2.Circle(3,"blue",false);

            Console.WriteLine("c" + c.ToString());
            Console.WriteLine("c1" + c1.ToString());
            Console.WriteLine("c2" + c2.ToString());
        }


        public void TestComplexShape()
        {
            ComplexShape cs = new ws2.ComplexShape();
            Circle c = new ws2.Circle();
            Circle c1 = new ws2.Circle(4);
            Circle c2 = new ws2.Circle(3, "blue", false);
            Rectangle r = new ws2.Rectangle();
            Rectangle r1 = new ws2.Rectangle(2.2, 2.2);
            Rectangle r2 = new ws2.Rectangle("red", false, 2.2, 2.2);
            Console.WriteLine("collection " + nameof(cs) + " perimeter: " + cs.Perimeter() + ", area: " + cs.Area());
            cs.Add(c1);
            cs.Count();
            Console.WriteLine("collection " + nameof(cs) + " perimeter: " + cs.Perimeter() + ", area: " + cs.Area());
            Console.WriteLine(nameof(c1) + " perimeter: " + c1.Perimeter() + ", area: " + c1.Area());
            cs.Add(c1);
            cs.Add(c2);
            cs.Add(r1);
            cs.Add(r2);
            cs.Count();
            Console.WriteLine("collection " + nameof(cs) + " perimeter: " + cs.Perimeter() + ", area: " + cs.Area());
        }
    }
}

using System;
using ws2;

namespace ws2
{
    public class Rectangle : Shape
    {

        static Rectangle()
        {
            Console.WriteLine("A Rectangle class initialized!");
        }
        public Rectangle(double width = 1.0, double length = 1.0) : this("Green", true, width, length)
        {
        }
        public Rectangle(string color, bool is_filled, double width, double length) : base(is_filled, color) 
        {
            Width = width;
            Length = length;
        }
        public override string ToString()
        {
            return "A Rectangle with width = " + Width + " and length = " + Length + ", which is derived class of " + base.ToString();
        }
        public override double Area() { return Width * Length; }
        public override double Perimeter() { return (Width + Length) * 2; }
        private double Width;
        private double Length;


    }
}

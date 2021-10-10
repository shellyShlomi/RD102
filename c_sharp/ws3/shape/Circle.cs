using System;

namespace ws2
{

    public class Circle : Shape
    {

        public Circle(double radius = 1.0) : this(radius, "Green", true)
        {
        }

        public Circle(double radius, string color, bool is_filled) : base(is_filled, color)
        {
            Radius = radius;
        }

        public new string ToString()
        {
            return "A Circle with radius = " + Radius + ", which is derived class of " + base.ToString();
        }
        public override double Area() { return Math.Pow(Radius, 2) * Math.PI; }
        public override double Perimeter() { return ((Radius * 2) * Math.PI); }
        private double Radius;

    }

}

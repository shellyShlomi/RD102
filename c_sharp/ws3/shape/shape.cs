using System;

namespace ws2
{
    public abstract class Shape
    {
        public abstract double Area();
        public abstract double Perimeter();
        public override string ToString()
        {
            string filled = _IsFilled ? "filled" : "not filled";
            return ($"A Shape with the color {_Color} and is {filled}");
        }

        protected Shape() : this(true, "Green")
        {
        }

        protected Shape(bool isFilled, string color)
        {
            _IsFilled = isFilled;
            _Color = color;
        }
        private bool _IsFilled;
        private string _Color;
    }

}

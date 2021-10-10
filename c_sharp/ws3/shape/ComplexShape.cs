using System;
using System.Collections.Generic;


namespace ws2
{
    public class ComplexShape : Shape
    {
        private List<Shape> shapes_collection;

        public ComplexShape() : base()
        {
            shapes_collection = new List<Shape>();
        }


        public void Add(Shape shp)
        {
            shapes_collection.Add(shp);
        }

        public int Count()
        {
            return shapes_collection.Count;
        }
        public override double Area()
        {
            double area_sum = 0;

            foreach (Shape sh in shapes_collection)
            {
                area_sum += sh.Area();
            }

            return area_sum;
        }
        public override double Perimeter()
        {
            double perimeter_sum = 0;

            foreach (Shape sh in shapes_collection)
            {
                perimeter_sum += sh.Perimeter();
            }

            return perimeter_sum;
        }
    }
}

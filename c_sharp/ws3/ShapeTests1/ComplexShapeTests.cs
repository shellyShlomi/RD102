using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Text;
using ws2;
namespace ws2.Tests
{
    [TestClass()]
    public class ComplexShapeTests
    {
        [TestMethod()]
        public void ComplexShapeTest()
        {


            // act
            ComplexShape actual = new ComplexShape();

            Shape circle = new Circle();
            Type Circle = circle.GetType().BaseType;
            // assert
            Assert.AreEqual(circle.GetType().BaseType, actual.GetType().BaseType);

        }

        [TestMethod()]
        public void AddTest()
        {
            // arrange
            double expected = 3;
            ComplexShape cs = new ComplexShape();
            bool is_full = false;
            double radius = 1.0;
            double width = 1.2;
            double length = 2.0;
            string color = "Red";
            Circle c = new Circle(radius, color, is_full);
            Circle c1 = new Circle(radius, color, is_full);
            Rectangle r = new Rectangle(width, length);

            // act
            cs.Add(c);
            cs.Add(c1);
            cs.Add(r);
            // assert
            Assert.AreEqual(expected, ((double)cs.Count()));

        }

        [TestMethod()]
        public void CountTest()
        {
            // arrange
            double expected = 0;
            // act
            ComplexShape cs = new ComplexShape();
            // assert
            Assert.AreEqual(expected, ((double)cs.Count()));
        }

        [TestMethod()]
        public void AreaTest()
        {
            ComplexShape cs = new ComplexShape();
            bool is_full = false;
            double radius = 1.0;
            double width = 1.2;
            double length = 2.0;
            string color = "Red";

            int circle_num = 2;

            Circle c = new Circle(radius, color, is_full);
            Circle c1 = new Circle(radius, color, is_full);
            Rectangle r = new Rectangle(width, length);

            double area_r = r.Area();
            double expected = (c.Area() * circle_num) + r.Area();

            // act
            cs.Add(c);
            cs.Add(c1);
            cs.Add(r);
            double actual = cs.Area();
            // assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod()]
        public void PerimeterTest()
        {
            ComplexShape cs = new ComplexShape();
            bool is_full = false;
            double radius = 1.0;
            double width = 1.2;
            double length = 2.0;
            string color = "Red";

            int circle_num = 2;

            Circle c = new Circle(radius, color, is_full);
            Circle c1 = new Circle(radius, color, is_full);
            Rectangle r = new Rectangle(width, length);

            double area_r = r.Perimeter();
            double expected = (c.Perimeter() * circle_num) + r.Perimeter();

            // act
            cs.Add(c);
            cs.Add(c1);
            cs.Add(r);
            double actual = cs.Perimeter();
            // assert
            Assert.AreEqual(expected, actual);
        }
    }
}


using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Text;
using ws2;

namespace ws2.Tests
{
    [TestClass()]
    public class CircleTests
    {
        [TestMethod()]
        public void CircleTest()
        {
            // arrange
            bool is_full= false;
            double radius = 1.0;
            string color = "Red";
            double expected = 1.0;

            // act
            Circle c = new Circle(radius, color, is_full);
            double actual = c.Perimeter() /( Math.PI * 2);

            // assert
            Assert.AreEqual(expected, actual);

        }

        [TestMethod()]
        public void CircleTest1()
        {
            // arrange
            double radius = 1.0;
            double expected = 1.0;

            // act
            Circle c = new Circle(radius);
            double actual = c.Perimeter() / (Math.PI * 2);

            // assert
            Assert.AreEqual(expected, actual);
        }

        [TestMethod()]
        public void ToStringTest()
        {
            // arrange
            bool is_full = false;
            string is_full_str = is_full ? "filled" : "not filled" ;
            string color = "Red";
            double radius = 1;
            string expected = $"A Circle with radius = {radius}, which is derived class of A Shape with the color {color} and is {is_full_str}";

            // act
            Circle c = new Circle(radius, color, is_full);

            // assert
            Assert.AreEqual(expected, c.ToString());
        }

        [TestMethod()]
        public void ToStringTest1()
        {
            // arrange
            bool is_full = true;
            string is_full_str = is_full ? "filled" : "not filled";
            string color = "Green";
            double radius = 1;
            string expected = $"A Circle with radius = {radius}, which is derived class of A Shape with the color {color} and is {is_full_str}";

            // act
            Circle c = new Circle(radius);

            // assert
            Assert.AreEqual(expected, c.ToString());
        }
        [TestMethod()]
        public void AreaTest()
        {
            // arrange
            bool is_full = false;
            double radius = 1.0;
            string color = "Red";
            double expected = 3.14159265;
            double expected1 = 3.14159265;
            int precision = 3;
            
            // act
            expected = Math.Round(expected, precision);
            expected1 = Math.Round(expected1, precision);

            Circle c = new Circle(radius, color, is_full);
            double actual = Math.Round(c.Area(), precision);
            Circle c1 = new Circle(radius);
            double actual1 = Math.Round(c1.Area(), precision);

            // assert
            Assert.AreEqual(expected, actual);
            Assert.AreEqual(expected1, actual1);
        }

        [TestMethod()]
        public void PerimeterTest()
        {
            bool is_full = false;
            double radius = 1.0;
            string color = "Red";
            double expected = 6.2831853;
            double expected1 = 6.2831853;
            int precision = 3;

            // act
            expected = Math.Round(expected, precision);
            expected1 = Math.Round(expected1, precision);

            Circle c = new Circle(radius, color, is_full);
            double actual = Math.Round(c.Perimeter(), precision);
            Circle c1 = new Circle(radius);
            double actual1 = Math.Round(c1.Perimeter(), precision);

            // assert
            Assert.AreEqual(expected, actual);
            Assert.AreEqual(expected1, actual1);
        }
    }
}
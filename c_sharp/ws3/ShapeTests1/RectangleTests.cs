using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace ws2.Tests
{
    [TestClass()]
    public class RectangleTests
    {
        [TestMethod()]
        public void RectangleTest()
        {
            // arrange
            bool is_full = false;
            double width = 1.2;
            double length = 2.0;
            string color = "Red";
            double expected = 2;
            double expected1 = 1.2;

            // act
            Rectangle r = new Rectangle(color, is_full, width, length);
            double actual_w = r.Area() / length;
            double actual_l = r.Area() / width;

            // assert
            Assert.AreEqual(expected1, actual_w);
            Assert.AreEqual(expected, actual_l);
        }

        [TestMethod()]
        public void RectangleTest1()
        {
            // arrange
            double width = 1.2;
            double length = 2.0;
            double expected = 2;
            double expected1 = 1.2;

            // act
            Rectangle r = new Rectangle(width, length);
            double actual_w = r.Area() / length;
            double actual_l = r.Area() / width;

            // assert
            Assert.AreEqual(expected1, actual_w);
            Assert.AreEqual(expected, actual_l);
        }


        [TestMethod()]
        public void ToStringTest()
        {
            // arrange
            bool is_full = false;
            string is_full_str = is_full ? "filled" : "not filled";
            string color = "Red";
            double width = 1.0;
            double length = 2.0;
            string expected = $"A Rectangle with width = { width } and length = { length}, which is derived class of A Shape with the color {color} and is {is_full_str}";

            // act
            Rectangle r = new Rectangle(color, is_full, width, length);

            // assert
            Assert.AreEqual(expected, r.ToString());
        }

        [TestMethod()]
        public void ToStringTest1()
        {
            // arrange
            bool is_full = true;
            string is_full_str = is_full ? "filled" : "not filled";
            string color = "Green";
            double width = 1.0;
            double length = 2.0;
            string expected = $"A Rectangle with width = { width } and length = { length}, which is derived class of A Shape with the color {color} and is {is_full_str}";

            // act
            Rectangle r = new Rectangle(width, length);

            // assert
            Assert.AreEqual(expected, r.ToString());
        }
        [TestMethod()]
        public void AreaTest()
        {
            // arrange
            bool is_full = false;
            double width = 1.0;
            double length = 2.0;
            string color = "Red";
            double expected = 2;
            double expected1 = 2;
            int precision = 3;

            // act
            expected = Math.Round(expected, precision);
            expected1 = Math.Round(expected1, precision);

            Rectangle r = new Rectangle(width, length);
            double actual = Math.Round(r.Area(), precision);
            Rectangle r1 = new Rectangle(color, is_full, width, length);
            double actual1 = Math.Round(r1.Area(), precision);

            // assert
            Assert.AreEqual(expected, actual);
            Assert.AreEqual(expected1, actual1);
        }

        [TestMethod()]
        public void PerimeterTest()
        {
            // arrange
            bool is_full = false;
            double width = 1.0;
            double length = 2.0;
            string color = "Red";
            double expected = 6;
            double expected1 = 6;
            int precision = 3;

            // act
            expected = Math.Round(expected, precision);
            expected1 = Math.Round(expected1, precision);

            Rectangle r = new Rectangle(width, length);
            double actual = Math.Round(r.Perimeter(), precision);
            Rectangle r1 = new Rectangle(color, is_full,width, length);
            double actual1 = Math.Round(r1.Perimeter(), precision);

            // assert
            Assert.AreEqual(expected, actual);
            Assert.AreEqual(expected1, actual1);
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace natural_reservation_park
{
    public class Family : Group
    {
        public Family(int size): base(size, Traveler.FAMILY)
        {
           
        }

        public override void Behave(int degree)
        {
            StormDegree _degree = (StormDegree)degree;

            if (StormDegree.RISKY <= _degree)
            {
                Console.WriteLine("We as a family can't take the risk.");
            }
            else
            {
                Console.WriteLine("Strong family strong country!");
            }
        }
    }
}

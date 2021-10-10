using System;
using System.Collections.Generic;
using System.Text;

namespace natural_reservation_park
{

    public class Single : ParkTraveler
    {
        public Single() : base(Traveler.SINGLE)
        {
            ;//empty
        }

        public override void Behave(int degree)
        {
            StormDegree _degree = (StormDegree)degree;

            if (StormDegree.VERY_STRONG <= _degree)
            {
                Console.WriteLine("Single traveler quits only at 10!.");
            }
            else
            {
                Console.WriteLine("Single traveler will never yield!");
            }
          
        }

    }
}

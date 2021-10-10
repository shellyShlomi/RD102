using System;
using System.Collections.Generic;
using System.Text;

namespace natural_reservation_park
{
    public abstract class ParkTraveler
    {
        public enum StormDegree
        {
            VERY_STRONG = 10,
            STRONG = 7,
            RISKY = 6,
            MIDEUM = 5,
            EZAY = 4
        }


        private Traveler type;

        protected ParkTraveler(Traveler _type)
        {
            type = _type;
        }

        public abstract void Behave(int degree);
    }
}

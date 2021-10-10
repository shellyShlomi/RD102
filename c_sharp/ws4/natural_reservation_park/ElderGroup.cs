using System;
using System.Collections.Generic;
using System.Text;

namespace natural_reservation_park
{
    class ElderGroup : Group
    {

        public ElderGroup(int size): base(size, Traveler.ELDERGROUP)
        {

        }
        public override void Behave(int degree)
        {
            StormDegree _degree = (StormDegree)degree;

            if (StormDegree.VERY_STRONG == _degree)
            {
                Console.WriteLine("This group is gonna die!!");
            }
            else if (StormDegree.STRONG <= _degree)
            {
                Console.WriteLine("Some of us are not gonna make it!");
            }
            else if (StormDegree.MIDEUM <= _degree)
            {
                Console.WriteLine("only Suzan will suffer!");
            }
            else
            {
                Console.WriteLine("That's nothing for this group!!");
            }
        }
    }
}

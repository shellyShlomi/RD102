using System;
using System.Threading;

namespace natural_reservation_park
{
    class Program
    {
        static void Main(string[] args)
        {
            Park park = new Park();

            Single t1 = new Single();
            Single t2 = new Single();
            Single t3 = new Single();
            Single t4 = new Single();

            Family f1 = new Family(3);
            Family f2 = new Family(5);

            ElderGroup g1 = new ElderGroup(10);
            ElderGroup g2 = new ElderGroup(30);

            park.CheckIn(t1);
            park.CheckIn(t2);
            park.CheckIn(t3);
            park.CheckIn(t4);
            park.CheckIn(f1);
            park.CheckIn(f2);
            park.CheckIn(g1);
            park.CheckIn(g2);

            for (int i = 0; i < 100; ++i)
            {
                park.CheckWeather();
                Console.WriteLine("-----------------------------------------------");

                Thread.Sleep(5000);
            }

        }
    }
}


//public int GetWeather()
//{
//    Random rand = new Random();
//    int storm_intensity = rand.Next(0, 10);

//    return storm_intensity;
//}
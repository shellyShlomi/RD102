using System;
using System.Collections.Generic;
using System.Text;

namespace natural_reservation_park
{
    class Park
    {
        private WeatherCenter weather_center;
        private List<ParkTraveler> travelers_collection;
        int degree;

        Del alert;

        public Park()
        {
            this.weather_center = new WeatherCenter(); 
            this.travelers_collection = new List<ParkTraveler>(); ;
            this.degree = 0;
        }

        public void CheckWeather()
        {
            if (weather_center.GetWeather(out degree).Equals("STORM"))
            {
                Alert();
            }
        }

        public void CheckIn(ParkTraveler t)
        {
            alert += t.Behave;
            travelers_collection.Add(t);
        }

        public void CheckOut(ParkTraveler t)
        {
            travelers_collection.Remove(t);
            alert -= t.Behave;
        }
        private void Alert()
        {
            alert(degree);
        }

        public delegate void Del(int degree);


    }
}

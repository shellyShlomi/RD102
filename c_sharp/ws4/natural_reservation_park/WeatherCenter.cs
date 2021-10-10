using System;
using System.Collections.Generic;
using System.Text;

namespace natural_reservation_park
{
    public class WeatherCenter : IWeather
    {
        Weather w;

        public WeatherCenter()
        {
            w = new Weather();
        }

        public string GetWeather(out int degree)
        {
            return w.GetWeather(out degree);
        }
    }
}

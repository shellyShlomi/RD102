using System;
using System.Collections.Generic;
using System.Text;

namespace natural_reservation_park
{
    public enum WeatherTypes
    {
        STORM,
        NICE
    }
    interface IWeather
    {
        public string GetWeather(out int degree);
    }
}

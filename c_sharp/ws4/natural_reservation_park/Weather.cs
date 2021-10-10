using System;

namespace natural_reservation_park
{
    class Weather : IWeather
    {
        private static WeatherTypes[] _weathers = { WeatherTypes.STORM, WeatherTypes.NICE };
        private static string[] convert_weather_type = { "STORM", "NICE" };

        public Weather()
        {
            this.weather_str = null;
            this.level = 0;
        }

        private string weather_str;
        private int level;

        private void GeneratWeather()
        {

            Random rand = new Random();
            level = rand.Next(0, 10);
            int weather_type = rand.Next(0, _weathers.Length);

            weather_str = convert_weather_type[(int)_weathers[weather_type]];

            return;
        }
        public string GetWeather(out int degree)
        {
            GeneratWeather();
            degree = level;
            return weather_str;
        }
    }
}

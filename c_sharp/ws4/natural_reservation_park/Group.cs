using System;
using System.Collections.Generic;
using System.Text;

namespace natural_reservation_park
{
    public abstract class Group : ParkTraveler
    {
        private List<ParkTraveler> Travelers_collection;

        protected Group(int size, Traveler type) : base(type)
        {
            Travelers_collection = new List<ParkTraveler>();
            for (int i = 0; i < size; ++i)
            {
                Travelers_collection.Add(new Single());
            }
        }
    }
}

using System;
using System.Collections.Generic;

namespace BrakelWeb.Models
{
    public partial class DataPoint
    {

        public int Id { get; set; }
        public int Time { get; set; }
        public Nullable<int> Temperature { get; set; }
        public Nullable<int> CO2 { get; set; }
        public Nullable<int> Humidity { get; set; }
        public Nullable<int> Light { get; set; }
        public string NodeAdress { get; set; }
    }
}

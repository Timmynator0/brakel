using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace BrakelWeb.Models
{
    public class XbeeData
    {
        //public long Id { get; set; }
        public long Time { get; set; }
        public Nullable<int> Temperature { get; set; }
        public Nullable<int> CO2 { get; set; }
        public Nullable<int> Humidity { get; set; }
        public Nullable<int> Light { get; set; }
        public string NodeAdressLow { get; set; }
        public string NodeAdressHigh { get; set; }
        //public virtual Node Node { get; set; }
    }
}
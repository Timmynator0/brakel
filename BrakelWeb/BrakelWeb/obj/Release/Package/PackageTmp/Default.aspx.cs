using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;
using System.Web.UI.HtmlControls;
using System.Web.UI.DataVisualization.Charting;
using BrakelWeb.DAL;
using BrakelWeb.Models;

namespace BrakelWeb
{
    public partial class Temperature : System.Web.UI.Page
    {
        DAL.StorageProvider dal = new StorageProvider();

        private void Page_Load(object sender, System.EventArgs e)
        {


            List<XbeeData> temperatureList = dal.getDataPointsTemperature();

            foreach (XbeeData temperature in temperatureList)
            {
                // yValue = yValue + (random.NextDouble() * 10.0 - 5.0);
                Chart1.Series["Temperature"].Points.AddY(temperature.Temperature);
                Chart1.Series["CO2"].Points.AddY(temperature.CO2);
                Chart1.Series["Humidity"].Points.AddY(temperature.Humidity);
                Chart1.Series["Light Intensity"].Points.AddY(temperature.Light);
            }

        }

    }
}
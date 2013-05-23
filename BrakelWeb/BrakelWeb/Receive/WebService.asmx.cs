using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.Script.Services;
using System.Web.Script.Serialization;
using BrakelWeb.Models;
using BrakelWeb.DAL;
namespace BrakelWeb.Receive
{
    /// <summary>
    /// stores data!
    /// </summary>
    [WebService(Namespace = "localhost/Receive/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]

    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
   //[System.Web.Script.Services.ScriptService]
    public class WebService : System.Web.Services.WebService
    {
        DAL.StorageProvider dal = new StorageProvider(); // initialize data acces layer


        [WebMethod]    
        public Boolean storedata(List<XbeeData> XbeeDataPoints)
        {
           List<DataPoint> dataPointList = new List<DataPoint>();
            foreach(XbeeData data in XbeeDataPoints)
            {

                //data.Id;
                //data.Time;
                //data.Temperature;
                //data.CO2;
                //data.Humidity;
                //data.Light;
                //data.NodeAdressHigh;
                //data.NodeAdressLow;
               
                dataPointList.Add( new DataPoint { Time = data.Time, Temperature = data.Temperature,
                                CO2 = data.CO2 , Humidity = data.Humidity, Light = data.Light, 
                                NodeAdress = data.NodeAdressHigh + data.NodeAdressLow });
            }

            return dal.storeDataList(dataPointList);
        }
    }
}

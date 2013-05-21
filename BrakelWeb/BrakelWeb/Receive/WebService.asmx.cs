using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.Script.Services;
using System.Web.Script.Serialization;
using BrakelWeb.Models;
namespace BrakelWeb.Receive
{
    /// <summary>
    /// Summary description for WebService
    /// </summary>
    [WebService(Namespace = "localhost/Receive/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
   //[System.Web.Script.Services.ScriptService]
    public class WebService : System.Web.Services.WebService
    {

        [WebMethod]
  //      [ScriptMethod(ResponseFormat = ResponseFormat.Json, XmlSerializeString = false)]
        public Boolean storedata(object json)
        {
            

            return true;
        }
    }
}

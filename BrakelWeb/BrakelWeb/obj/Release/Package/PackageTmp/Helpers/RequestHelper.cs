using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace BrakelWeb.Helpers
{
    public class RequestHelper
    {

        public static bool IsJsonRequest(HttpRequest request)
        {
            bool returnValue = false;
            if (request.ContentType == "application/json")
                returnValue = true;

            return returnValue;
        }
    }
}
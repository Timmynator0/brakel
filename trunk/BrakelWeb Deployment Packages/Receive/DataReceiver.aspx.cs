using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace BrakelWeb.Receive
{
    public partial class DataReceiver : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            
            if (Helpers.RequestHelper.IsJsonRequest(Request)) 
            {
        
            }

        }

        protected void OnReceived(object sender, EventArgs e)
        {
            if (Helpers.RequestHelper.IsJsonRequest(Request))
            {

            }


        }
    }
}
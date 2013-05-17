using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
//using BrakelWeb.Models.Mapping;
using BrakelWeb.Models;

namespace BrakelWeb
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            using (var db = new BrakelContext())
            {
                // Create and save a new Blog
                System.Diagnostics.Debug.WriteLine("Enter a name for a new Blog: ");
                Random autoRand = new Random();
                var name = "whoop" + autoRand.Next();

                var node = new Node { NodeAdress = name, Location = "bla" , Type = 1 , ObjectActive= true };
                var data = new Data { Id = autoRand.Next(), NodeAdress = name };
                db.Nodes.Add(node);
                db.SaveChanges();

                // Display all Blogs from the database
                var query = from b in db.Nodes
                            orderby b.NodeAdress
                            select b;

                System.Diagnostics.Debug.WriteLine("All blogs in the database:");
                foreach (var item in query)
                {
                    System.Diagnostics.Debug.WriteLine(item.NodeAdress);
                }

                System.Diagnostics.Debug.WriteLine("Press any key to exit...");
                //  Console.ReadKey();
            }
        }
    }
}
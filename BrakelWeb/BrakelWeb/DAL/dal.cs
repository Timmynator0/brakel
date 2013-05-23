using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BrakelWeb.Models;

namespace BrakelWeb.DAL
{
   public class StorageProvider
   {
        Boolean storeNode(Node node)
        {

            using (var db = new BrakelContext())
            {

                db.Nodes.Add(node);
                db.SaveChanges();
                     return true;

            }
           
        }


        Boolean removeNode(Node node)
        {
            using (var db = new BrakelContext())
            {

               // db.Nodes.Add(node);
                var nodeToDelete =  from b in db.Nodes
                                    where b.NodeAdress == node.NodeAdress
                                    select b;

                db.Nodes.Remove((Node)nodeToDelete);
                db.SaveChanges();
                return true;

            }          
        }

        Node getNode(String nodeAdress)
        {
             using (var db = new BrakelContext())
            {
                var node =  from b in db.Nodes
                            where b.NodeAdress  == nodeAdress
                            select b;            
                return (Node)node;
            }  
        }

        Boolean storeData(DataPoint data)
        {
            using (var db = new BrakelContext())
            {

                db.DataPoints.Add(data);
                db.SaveChanges();
                return true;

            }
        }

        public Boolean storeDataList(List<DataPoint> datalist)
        {
            using (var db = new BrakelContext())
            {
                foreach (DataPoint data in datalist)
                {
                    db.DataPoints.Add(data);

                }
                try
                {
                    db.SaveChanges();
                }
                catch (Exception e)
                {
                    System.Diagnostics.Debug.WriteLine(e.ToString());
                    return false;
                }
                return true;

            }
        }



        DataPoint getDataPoint(int id)
        {
            using (var db = new BrakelContext())
            {
                
                var datapoint = from b in db.DataPoints
                                where b.Id == id
                                select b;
                return (DataPoint) datapoint;
            }
        }




   }
}

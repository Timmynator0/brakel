using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BrakelWeb.Models;
using System.Data;

namespace BrakelWeb.DAL
{
   public class StorageProvider
   {
       public Boolean storeNode(Node node)
        {

            using (var db = new BrakelContext())
            {

                db.Nodes.Add(node);
                db.SaveChanges();
                     return true;

            }
           
        }


        public Boolean removeNode(Node node)
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

        public Node getNode(String nodeAdress)
        {
             using (var db = new BrakelContext())
            {
                var node =  from b in db.Nodes
                            where b.NodeAdress  == nodeAdress
                            select b;            
                return (Node)node;
            }  
        }

        public Boolean storeData(DataPoint data)
        {
            using (var db = new BrakelContext())
            {

                db.DataPoints.Add(data);
                db.SaveChanges();
                return true;

            }
        }

        public Boolean storeDataList(List<DataPoint> datalist , List<Node> nodeList)
        {
            using (var db = new BrakelContext())
            {
                foreach (DataPoint data in datalist)
                {
                    db.DataPoints.Add(data);
                }
                //foreach (Node node in nodeList)
                //{
                 //   db.Nodes.Add(node);
                //}

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



        public DataPoint getDataPoint(int id)
        {
            using (var db = new BrakelContext())
            {
                
                var datapoint = from b in db.DataPoints
                                where b.Id == id
                                select b;
                return (DataPoint) datapoint;
            }
        }

        public List<XbeeData> getDataPointsTemperature()
        {
            List<XbeeData> temperaturelist = new List<XbeeData>();
            using (var db = new BrakelContext())
            {
                List<XbeeData> tmplst = new List<XbeeData>();
                var datapoints = from b in db.DataPoints
                                 select b;

                foreach (DataPoint data in datapoints)
                {
                      temperaturelist.Add(new XbeeData { Temperature = data.Temperature,  CO2 = data.CO2, Humidity = data.Humidity, Light = data.Light }); 
                }
               
            }
             return temperaturelist;
        }




   }
}

using System;
using System.Collections.Generic;

namespace BrakelWeb.Models
{
    public partial class Node
    {
        public Node()
        {
            this.Data = new List<Data>();
        }

        public string NodeAdress { get; set; }
        public string Location { get; set; }
        public short Type { get; set; }
        public Nullable<bool> ObjectActive { get; set; }
        public virtual ICollection<Data> Data { get; set; }
    }
}

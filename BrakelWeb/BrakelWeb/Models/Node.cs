using System;
using System.Collections.Generic;

namespace BrakelWeb.Models
{
    public partial class Node
    {
        public string NodeAdress { get; set; }
        public string Location { get; set; }
        public short Type { get; set; }
        public Nullable<bool> ObjectActive { get; set; }
    }
}

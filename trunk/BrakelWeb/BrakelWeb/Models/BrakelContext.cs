using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using BrakelWeb.Models.Mapping;

namespace BrakelWeb.Models
{
    public partial class BrakelContext : DbContext
    {
        static BrakelContext()
        {
            Database.SetInitializer<BrakelContext>(null);
        }

        public BrakelContext()
            : base("Name=BrakelContext")
        {
        }

        public DbSet<DataPoint> DataPoints { get; set; }
        public DbSet<Node> Nodes { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Configurations.Add(new DataPointMap());
            modelBuilder.Configurations.Add(new NodeMap());
        }
    }
}

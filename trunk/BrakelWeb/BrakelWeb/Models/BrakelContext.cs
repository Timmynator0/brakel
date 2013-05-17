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

        public DbSet<Data> Data { get; set; }
        public DbSet<Node> Nodes { get; set; }
        public DbSet<sysdiagram> sysdiagrams { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Configurations.Add(new DataMap());
            modelBuilder.Configurations.Add(new NodeMap());
            modelBuilder.Configurations.Add(new sysdiagramMap());
        }
    }
}

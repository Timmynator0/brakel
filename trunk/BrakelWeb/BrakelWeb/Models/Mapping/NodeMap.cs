using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity.ModelConfiguration;

namespace BrakelWeb.Models.Mapping
{
    public class NodeMap : EntityTypeConfiguration<Node>
    {
        public NodeMap()
        {
            // Primary Key
            this.HasKey(t => t.NodeAdress);

            // Properties
            this.Property(t => t.NodeAdress)
                .IsRequired()
                .HasMaxLength(8);

            this.Property(t => t.Location)
                .HasMaxLength(50);

            // Table & Column Mappings
            this.ToTable("Node");
            this.Property(t => t.NodeAdress).HasColumnName("NodeAdress");
            this.Property(t => t.Location).HasColumnName("Location");
            this.Property(t => t.Type).HasColumnName("Type");
            this.Property(t => t.ObjectActive).HasColumnName("ObjectActive");
        }
    }
}

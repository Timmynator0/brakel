using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity.ModelConfiguration;

namespace BrakelWeb.Models.Mapping
{
    public class DataMap : EntityTypeConfiguration<Data>
    {
        public DataMap()
        {
            // Primary Key
            this.HasKey(t => t.Id);

            // Properties
            this.Property(t => t.Id)
                .HasDatabaseGeneratedOption(DatabaseGeneratedOption.None);

            this.Property(t => t.NodeAdress)
                .HasMaxLength(8);

            // Table & Column Mappings
            this.ToTable("Data");
            this.Property(t => t.Id).HasColumnName("Id");
            this.Property(t => t.Time).HasColumnName("Time");
            this.Property(t => t.Temperature).HasColumnName("Temperature");
            this.Property(t => t.CO2).HasColumnName("CO2");
            this.Property(t => t.Humidity).HasColumnName("Humidity");
            this.Property(t => t.Light).HasColumnName("Light");
            this.Property(t => t.NodeAdress).HasColumnName("NodeAdress");

            // Relationships
            this.HasOptional(t => t.Node)
                .WithMany(t => t.Data)
                .HasForeignKey(d => d.NodeAdress);

        }
    }
}

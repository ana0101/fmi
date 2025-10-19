using Microsoft.EntityFrameworkCore;
using WebApplication3.Models;

namespace WebApplication3.ContextModels
{
    public class StiriContext : DbContext
    {
        public StiriContext(DbContextOptions<StiriContext> options) : base(options) { }
        public DbSet<Stire> Stire { get; set; }
        public DbSet<Categorie> Categorie { get; set; }
    }
}

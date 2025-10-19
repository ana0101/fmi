using Microsoft.AspNetCore.Components;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Models;

namespace WebApplication2.ContextModels
{
    public class StudentContext : DbContext
    {
        public StudentContext(DbContextOptions<StudentContext> options) : base(options) { }
        public DbSet<Student> Students { get; set; }
    }
}

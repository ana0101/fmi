using Microsoft.Extensions.Hosting;
using System.Text.Json.Serialization;

namespace WebApplication3.Models
{
    public class Categorie
    {
        public int Id { get; set; }
        public string Nume { get; set; }

        [JsonIgnore]
        public ICollection<Stire> Stiri { get; set; }
    }
}

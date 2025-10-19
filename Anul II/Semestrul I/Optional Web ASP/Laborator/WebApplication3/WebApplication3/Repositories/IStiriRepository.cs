using Microsoft.AspNetCore.Mvc;
using WebApplication3.ContextModels;
using WebApplication3.Models;

namespace WebApplication3.Repositories
{
    public interface IStiriRepository
    {
        public Task<IEnumerable<Stire>> GetStiriAsync();
        public Task<Stire>? GetStireAsync(int id, bool includeCategorie);
        public Task<Stire> PostStireAsync(Stire stire);
        public Task<Stire>? PutStireAsync(Stire stire);
        public Task<Boolean> DeleteStireAsync(int id);
    }
}

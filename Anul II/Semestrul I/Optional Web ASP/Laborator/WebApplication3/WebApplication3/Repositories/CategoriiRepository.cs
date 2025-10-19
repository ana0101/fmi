using AutoMapper;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication3.ContextModels;
using WebApplication3.Models;

namespace WebApplication3.Repositories
{
    public class CategoriiRepository : ICategoriiRepository
    {
        private readonly StiriContext _stiriContext;
        private readonly IMapper _mapper;
        public CategoriiRepository(StiriContext stiriContext, IMapper mapper)
        {
            _stiriContext = stiriContext;
            _mapper = mapper;
        }

        public async Task<IEnumerable<Categorie>> GetCategoriiAsync()
        {
            var categorii = await _stiriContext.Categorie.ToListAsync();
            return categorii;
        }

        public async Task<Categorie>? GetCategorieAsync(int id)
        {
            var categorie = await _stiriContext.Categorie.FirstOrDefaultAsync(c => c.Id == id);
            return categorie;
        }

        public async Task<Categorie> PostCategorieAsync(Categorie categorie)
        {
            _stiriContext.Add(categorie);
            await _stiriContext.SaveChangesAsync();
            return categorie;
        }

        public async Task<Categorie>? PutCategorieAsync(Categorie categorieNoua)
        {
            var categorie = await _stiriContext.Categorie.FirstOrDefaultAsync(c => c.Id == categorieNoua.Id);
            if (categorie == null)
                return null;
            _mapper.Map(categorieNoua, categorie);
            _stiriContext.Update(categorie);
            await _stiriContext.SaveChangesAsync();
            return categorie;
        }

        public async Task<Boolean> DeleteCategorieAsync(int id)
        {
            var categorie = await _stiriContext.Categorie.FirstOrDefaultAsync(c => c.Id == id);
            if (categorie == null)
                return false;
            _stiriContext.Remove(categorie);
            await _stiriContext.SaveChangesAsync();
            return true;
        }
    }
}

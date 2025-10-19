using AutoMapper;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebApplication3.ContextModels;
using WebApplication3.Models;

namespace WebApplication3.Repositories
{
    public class StiriRepository : IStiriRepository
    {
        private readonly StiriContext _stiriContext;
        private readonly IMapper _mapper;
        public StiriRepository(StiriContext stiriContext, IMapper mapper)
        {
            _stiriContext = stiriContext;
            _mapper = mapper;
        }

        public async Task<IEnumerable<Stire>> GetStiriAsync()
        {
            var stiri = await _stiriContext.Stire.ToListAsync();
            return stiri;
        }

        public async Task<Stire>? GetStireAsync(int id, bool includeCategorie)
        {
            if (includeCategorie)
            {
                var stire = await _stiriContext.Stire.Include(s => s.Categorie).AsNoTracking().FirstOrDefaultAsync(s => s.Id == id);
                return stire;
            }
            else
            {
                var stire = await _stiriContext.Stire.FirstOrDefaultAsync(s => s.Id == id);
                return stire;
            }
        }

        public async Task<Stire> PostStireAsync(Stire stire)
        {
            _stiriContext.Stire.Add(stire);
            await _stiriContext.SaveChangesAsync();
            return stire;
        }

        public async Task<Stire>? PutStireAsync(Stire stireNoua)
        {
            var stire = await _stiriContext.Stire.FirstOrDefaultAsync(s => s.Id == stireNoua.Id);
            if (stire == null)
                return null;
            _mapper.Map(stireNoua, stire);
            _stiriContext.Stire.Update(stire);
            await _stiriContext.SaveChangesAsync();
            return stire;
        }

        public async Task<Boolean> DeleteStireAsync(int id)
        {
            var stire = _stiriContext.Stire.FirstOrDefault(s => s.Id == id);
            if (stire == null) 
                return false;
            _stiriContext.Remove(stire);
            await _stiriContext.SaveChangesAsync();
            return true;
        }
    }
}

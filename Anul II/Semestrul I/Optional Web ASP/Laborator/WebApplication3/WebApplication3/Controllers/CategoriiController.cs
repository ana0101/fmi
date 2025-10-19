using AutoMapper;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Migrations.Operations;
using WebApplication3.ContextModels;
using WebApplication3.Models;
using WebApplication3.Repositories;

namespace WebApplication3.Controllers
{
    [Route("api/[controller]")]
    [ApiController]

    public class CategoriiController : ControllerBase
    {
        private readonly IMapper _mapper;
        private readonly ICategoriiRepository _categoriiRepository;

        public CategoriiController(IMapper mapper, ICategoriiRepository categoriiRepository)
        {
            _mapper = mapper;
            _categoriiRepository = categoriiRepository;
        }

        [HttpGet]
        public async Task<IActionResult> GetCategorii()
        {
            var categorii = await _categoriiRepository.GetCategoriiAsync();
            return Ok(_mapper.Map<List<CategorieDto>>(categorii));
        }

        [HttpGet("{id}")]
        public async Task<IActionResult> GetCategorie(int id)
        {
            var categorie = await _categoriiRepository.GetCategorieAsync(id);
            if (categorie == null)
                return NotFound();
            return Ok(_mapper.Map<CategorieDto>(categorie));
        }

        [HttpPost]
        public async Task<IActionResult> PostCategorie(CategorieDtoCreate categorieDto)
        {
            var categorie = _mapper.Map<Categorie>(categorieDto);
            _categoriiRepository.PostCategorieAsync(categorie);
            return Ok(categorie);
        }

        [HttpPut]
        public async Task<IActionResult> PutCategorie(CategorieDto categorieDto)
        {
            var categorie = await _categoriiRepository.PutCategorieAsync(_mapper.Map<Categorie>(categorieDto));
            if (categorie == null)
                return NotFound();
            return Ok(categorie);
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteCategorie(int id)
        {
            var ok = await _categoriiRepository.DeleteCategorieAsync(id);
            if (ok == false) 
                return NotFound();
            return NoContent();
        }
    }
}

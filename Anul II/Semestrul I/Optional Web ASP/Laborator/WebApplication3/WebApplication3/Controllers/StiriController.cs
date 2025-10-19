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

    public class StiriController : ControllerBase
    {
        private readonly IMapper _mapper;
        private readonly IStiriRepository _stiriRepository;
        public StiriController(IMapper mapper, IStiriRepository stiriRepository)
        {
            _mapper = mapper;
            _stiriRepository = stiriRepository;
        }

        [HttpGet]
        //[Route("GetStiri")]
        public async Task<IActionResult> GetStiri()
        {
            var stiri = await _stiriRepository.GetStiriAsync();
            return Ok(_mapper.Map<List<StireDto>>(stiri));
        }

        [HttpGet("{id}")]
        public async Task<IActionResult> GetStire(int id, bool includeCategorie)
        {
            var stire = await _stiriRepository.GetStireAsync(id, includeCategorie);
            if (stire == null)
                return NotFound();
            if (includeCategorie)
                return Ok(stire);
            return Ok(_mapper.Map<StireDto>(stire));
        }

        [HttpPost]
        public async Task<IActionResult> PostStire(StireDtoCreate stireDto)
        {
            var stire = _mapper.Map<Stire>(stireDto);
            await _stiriRepository.PostStireAsync(stire);
            return Ok(stire);
        }

        [HttpPut]
        public async Task<IActionResult> PutStire(StireDto stireDto)
        {
            var stire = await _stiriRepository.PutStireAsync(_mapper.Map<Stire>(stireDto));
            if (stire == null)
                return NotFound();
            return Ok(stire);
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteStire(int id)
        {
            var ok = await _stiriRepository.DeleteStireAsync(id);
            if (ok == false) 
                return NotFound();
            return NoContent();
        }
    }
}

using AutoMapper;
using WebApplication3.Models;

namespace WebApplication3.Profiles
{
    public class CategoriiProfile : Profile
    {
        public CategoriiProfile() 
        {
            CreateMap<Categorie, CategorieDto>().ReverseMap();
            CreateMap<Categorie, CategorieDtoCreate>().ReverseMap();
            CreateMap<Categorie, Categorie>();
        }
    }
}

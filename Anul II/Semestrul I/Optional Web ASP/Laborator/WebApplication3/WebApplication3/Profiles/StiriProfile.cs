using AutoMapper;
using WebApplication3.Models;

namespace WebApplication3.Profiles
{
    public class StiriProfile : Profile
    {
        public StiriProfile() {
            CreateMap<Stire, StireDto>().ReverseMap();
            CreateMap<Stire, StireDtoCreate>().ReverseMap();
            CreateMap<Stire, Stire>();
        }
    }
}

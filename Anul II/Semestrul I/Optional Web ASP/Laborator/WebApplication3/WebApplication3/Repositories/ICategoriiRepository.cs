using WebApplication3.Models;

namespace WebApplication3.Repositories
{
    public interface ICategoriiRepository
    {
        public Task<IEnumerable<Categorie>> GetCategoriiAsync();
        public Task<Categorie>? GetCategorieAsync(int id);
        public Task<Categorie> PostCategorieAsync(Categorie categorie);
        public Task<Categorie>? PutCategorieAsync(Categorie categorie);
        public Task<Boolean> DeleteCategorieAsync(int id);
    }
}

namespace WebApplication2.Models
{
    public class Student
    {
        public int Id { get; set; }
        public string Nume { get; set; }
        public string Prenume { get; set; }
        public int Grupa { get; set; }

        public Student(int id, string nume, string prenume, int grupa)
        {
            Id = id;
            Nume = nume;
            Prenume = prenume;
            Grupa = grupa;
        }
    }
}

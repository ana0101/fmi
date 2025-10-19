namespace WebApplication1
{
    public class Student
    {
        public int Id { get; set; }
        public string Nume { get; set; }
        public string Prenume { get; set; }
        public int An { get; set; }
        private string Specializare { public get; public set; }

        public Student(int Id, string Nume, string Prenume, int An, string Specializare)
        {
            this.Id = Id;
            this.Nume = Nume;
            this.Prenume = Prenume;
            this.An = An;
            this.Specializare = Specializare;
        }
    }
}

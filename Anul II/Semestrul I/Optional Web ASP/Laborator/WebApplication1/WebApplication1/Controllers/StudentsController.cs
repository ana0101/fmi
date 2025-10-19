using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace WebApplication1.Controllers
{
    [Route("api/[controller]")]
    [ApiController]

    public class StudentsController : ControllerBase
    {
        List<Student> studentsList = new List<Student>()
        {
            new Student(1, "Ionescu", "Ion", 2, "matematica"),
            new Student(2, "Popescu", "Pop", 1, "informatica"),
            new Student(3, "Smith", "Jane", 3, "mate-info"),
            new Student(4, "Potter", "Harry", 2, "informatica"),
            new Student(5, "Tinuviel", "Luthien", 4, "cti")
        };

        [HttpGet(Name = "GetStudentsList")]
        public List<Student> Get() {  return studentsList; }


        [HttpPost(Name = "PostStudent")]
        public List<Student> PostStudent(Student student)
        {
            studentsList.Add(student);
            return studentsList;
        }


        [HttpPut(Name = "PutStudent")]
        public void PutStudent(int Id, string Nume2, string Prenume2, int An2, string Specializare2)
        {
            for (int i = 0; i < studentsList.Count; i++)
            {
                if (studentsList[i].Id == Id)
                {
                    studentsList[i].Nume = Nume2;
                    studentsList[i].Prenume = Prenume2;
                    studentsList[i].An = An2;
                    studentsList[i].Specializare = Specializare2;
                }
            }
        }

        [HttpDelete(Name = "DeleteStudent")]
        public void DeleteStudent(int Id)
        {
            for (int i = 0 ;i < studentsList.Count; i++) 
            {
                if (studentsList[i].Id == Id)
                {
                    studentsList.Remove(studentsList[i]);
                }
            }
        }
    }
}

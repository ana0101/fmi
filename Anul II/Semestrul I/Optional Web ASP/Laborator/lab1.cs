/*Console.WriteLine("introduceti numar: ");
int nr = Int32.Parse(Console.ReadLine());
if (nr % 3 == 0)
{
    Console.WriteLine("e divizibil cu 3");
}
else
{
    Console.WriteLine("nu e");
}*/


/*bool prim(int nr)
{
    if (nr == 1 || nr == 0)
    {
        return false;
    }
    if (nr == 2)
    {
        return true;
    }
    for (int j = 2; j <= nr / 2; j++)
    {
        if (nr % j == 0)
        {
            return false;
        }
    }
    return true;
}

Console.WriteLine("n =  ");
int n = Int32.Parse(Console.ReadLine());
int suma = 0;
for (int i = 0; i < n; i++)
{
    int nr = Int32.Parse(Console.ReadLine());
   
    if (prim(nr))
    {
        suma += nr;
    }
}
Console.WriteLine(suma.ToString());*/



/*int n = Int32.Parse(Console.ReadLine());
int m = 0, cn = n;
while (n > 0)
{
    m = m * 10 + n % 10;
    n /= 10;
}
if (m == cn)
{
    Console.WriteLine("palindrom");
}
else
{
    Console.WriteLine("nu palindrom");
}*/



/*void functie(string prop)
{
    string[] cuvinte = prop.Split(' ');
    for (int i = 0; i < cuvinte.Length; i++)
    {
        for (int j = i+1; j < cuvinte.Length; j++)
        {
            if (cuvinte[i].Length < cuvinte[j].Length)
            {
                string aux = cuvinte[i];
                cuvinte[i] = cuvinte[j];
                cuvinte[j] = aux;
            }
        }
    }

    for (int i = 0; i < cuvinte.Length; i++)
    {
        Console.WriteLine(cuvinte[i]);
    }
}

string prop = "Ana are multe mere";
functie(prop);*/


using System;

Dreptunghi dr = new Dreptunghi(2, 3);
int arie = dr.calcArie();
Patrat p = new Patrat(3);
int arie2 = p.calcArie();
Console.WriteLine(arie2.ToString());

class Dreptunghi
{
    protected int lungime;
    protected int latime;

    public Dreptunghi(int lung = 0, int lat = 0)
    {
        this.lungime = lung;
        this.latime = lat;
    }

    public int getLungime() { return lungime; }
    public int getLatime() { return latime; }

    public void setLungime(int lung) { this.lungime = lung; }
    public void setLatime(int lat) { this.latime = lat; }

    public int calcArie() { return lungime * latime; }
    public int calcPerimetru() { return lungime * 2 + latime * 2; }
}

class Patrat : Dreptunghi
{
    public Patrat(int l) : base(l, l)
    {

    }
}

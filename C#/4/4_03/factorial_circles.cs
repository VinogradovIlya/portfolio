Console.WriteLine("Напишите программу, которая принимает на вход число N и выдаёт произведение чисел от 1 до N.");

Console.Write("введите число N: ");
int chislo = Convert.ToInt32(Console.ReadLine());
Proizvedenie(chislo);
Console.WriteLine(Proizvedenie(chislo));

int Proizvedenie(int chislo) {
    int result = 1;
    for (int count = 1; count <= chislo; count++) {
        result = count * result;
    }
    return result;
}
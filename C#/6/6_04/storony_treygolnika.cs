Console.WriteLine("Напишите программу, которая принимает на вход три числа и проверяет, может ли существовать треугольник с сторонами такой длины.");

// ввод
Console.WriteLine("введите первую сторону треугольника: ");
double a = Convert.ToDouble(Console.ReadLine());
Console.WriteLine("введите второю сторону треугольника: ");
double b = Convert.ToDouble(Console.ReadLine());
Console.WriteLine("введите третью сторону треугольника: ");
double c = Convert.ToDouble(Console.ReadLine());

// проверка треугольника на реальность
SidesOfATriange(a, b, c);
Console.WriteLine(SidesOfATriange(a, b, c));

bool SidesOfATriange(double a, double b, double c) {
    if (a < (b + c) && 
        b < (a + c) &&
        c < (b + a)) return true;
    return false;
}
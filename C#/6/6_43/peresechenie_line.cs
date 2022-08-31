Console.WriteLine("Напишите программу, которая найдёт точку пересечения двух прямых, заданных уравнениями y = k1 * x + b1, y = k2 * x + b2; значения b1, k1, b2 и k2 задаются пользователем.");

Console.Write("введите k1: ");
double k1 = Convert.ToDouble(Console.ReadLine());
Console.Write("введите k2: ");
double k2 = Convert.ToDouble(Console.ReadLine());
Console.Write("введите b1: ");
double b1 = Convert.ToDouble(Console.ReadLine());
Console.Write("введите b2: ");
double b2 = Convert.ToDouble(Console.ReadLine());

double x = 0;
CoordinateX(k1, k2, b1, b2);
Console.Write("[{0}, ", x);
double y = 0;
CoordinateY(k2, b2);
Console.Write("{0}]", y);

double CoordinateX(double k1, double k2, double b1, double b2)
{
    return x = (b2 - b1)/(k1 - k2);
}

double CoordinateY(double k2, double b2) 
{
    return y = k2 * ((b2 - b1)/(k1 - k2)) + b2;
}
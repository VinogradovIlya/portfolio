Console.WriteLine("Напишите программу, которая принимает на вход координаты двух точек и находит расстояние между ними в 3D пространстве.");

Console.WriteLine("введите первые три координаты x1, y1 и z1: ");
double x1 = Convert.ToDouble(Console.ReadLine());
double y1 = Convert.ToDouble(Console.ReadLine());
double z1 = Convert.ToDouble(Console.ReadLine());

Console.WriteLine("введите вторые три координаты x2, y2 и z2: ");
double x2 = Convert.ToDouble(Console.ReadLine());
double y2 = Convert.ToDouble(Console.ReadLine());
double z2 = Convert.ToDouble(Console.ReadLine());

Diagonal(x1, y1, z1, x2, y2, z2);
Console.Write($"{Diagonal(x1, y1, z1, x2, y2, z2)}");

double Diagonal(double x1, double x2, double x3, double y1, double y2, double y3) {
    double xLine = (x2 - x1) * (x2 - x1);
    double yLine = (y2 - y1) * (y2 - y1);
    double zLine = (z2 - z1) * (z2 - z1);
    double result = Math.Sqrt(xLine + yLine + zLine);
    return result;
}
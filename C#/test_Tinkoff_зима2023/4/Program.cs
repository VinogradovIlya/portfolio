using System;

internal partial class Program
{
    private static void Main(string[] args)
    {
        int n = System.Convert.ToInt32(System.Console.ReadLine());
        // нахождение стороны a ?
        double sidePoligon = 1;


        // возвращает синус в градусах (а не в радианах)
        double MySinus(double cornerABC)
        {
            return Math.Sin(cornerABC / 180 * Math.PI);
        }

        // double cornerPoligon = (180 * (n-2)) / n;
        double cornerPoligon = 180 / n;

        // нахождение углов a и b ?
        double cornerA = cornerPoligon;
        double cornerB = cornerPoligon;
        // double cornerC = 180 - cornerA - cornerB;
        // if (cornerA + cornerB + cornerC != 180) System.Console.WriteLine("ошибка в градусах (строки 7-9)");

        Corner(sidePoligon, sidePoligon, sidePoligon);
        // поиск синуса зная только стороны
        double Corner(double sideA, double sideB, double sideC)
        {
            double step1 = Math.Pow(sideB, 2) + Math.Pow(sideC, 2) - Math.Pow(sideA, 2);
            double step2 = 2 * sideB * sideC;
            double cosCorner = step1 / step2;
            double sinCorner = Math.Sqrt(1 - Math.Pow(cosCorner, 2));
            return sinCorner;
        }

        // площадь треугольника по стороне и двум прилежащим углам
        double STriangle(double a, double cornerA, double cornerB)
        {
            double y = 180 - (cornerA + cornerB);
            double step1 = Math.Pow(a, 2) / 2;
            double step2 = MySinus(cornerA) * MySinus(cornerB) / MySinus(y);
            //double step2 = Corner(a, a, a) * Corner(a, a, a) / Corner(a, a, a);
            double s = step1 * step2;
            return s;
        }

        Console.WriteLine("{0:F6}", STriangle(sidePoligon, cornerA, cornerB));
    }
}


/*
double x = Math.E;
Console.WriteLine("E={0:##.######}", x); // не более шести знаков
Console.WriteLine("E={0:0.000000}", x); // ровно шесть знаков
Console.WriteLine("E={0:F6}", x); // число с плавающей точкой и 6 знаков после запятой
*/
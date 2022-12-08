string[] abc = Console.ReadLine().Split();
int a = Convert.ToInt32(abc[0]);
int b = Convert.ToInt32(abc[1]);
int c = Convert.ToInt32(abc[2]);

string[] xyz = Console.ReadLine().Split();
int x = Convert.ToInt32(xyz[0]);
int y = Convert.ToInt32(xyz[1]);
int z = Convert.ToInt32(xyz[2]);

// преобразование цифр в число и строку
/** деньга в кошельке (x, y, z) */
string NumberString (int chislo1, int chislo2, int chislo3) {
    string number = string.Empty;
    string strX = chislo1.ToString();
    string strY = chislo2.ToString();
    string strZ = chislo3.ToString();
    return number = strX + strY + strZ;
}

List<string> result = new List<string>();
result.Add(NumberString(x, y, z));

// функции перевода валюты в стороны + (dry!)
/**
нечетное = деньга в кошельке (x, y, z)
четное = ценность валюты 
*/
int Down(int chislo, int chislo1) {
    return chislo -= chislo1;
}
int Up(int chislo, int chislo1) {
    return chislo += chislo1;
}

// X<-- Y<-- Z
while (y > b || z > c) {
    // x y<-- z
    if (z >= b && (z-c) >= 0) {
        y = Up(y, b);
        z = Down(z, c);
        result.Add(NumberString(x, y, z));
        // System.Console.WriteLine(NumberString(x, y, z));
    }

    // x<-- y z
    if (y >= b && (y-b) >= 0) {
        x = Up(x, a);
        y = Down(y, b);
        result.Add(NumberString(x, y, z));
        // System.Console.WriteLine(NumberString(x, y, z));
    }
}

// по принципу волнового алгоритма
result.Sort();
result.Reverse();
int newXYZ = Convert.ToInt32(result[0]);
z = newXYZ % 10;
newXYZ = newXYZ / 10;
y = newXYZ % 10;
newXYZ = newXYZ / 10;
x = newXYZ % 10;

// System.Console.WriteLine($"{x}");
// System.Console.WriteLine($"{y}");
// System.Console.WriteLine($"{z}");

// x--> y--> z
while (x > a || y > b) {
    // x--> y z
    if (x >= a && (x-a) >= 0) {
        x = Down(x, a);
        y = Up(y, b);
        if (result.IndexOf(NumberString(x, y, z)) == -1) {
            result.Add(NumberString(x, y, z));
        }
        // System.Console.WriteLine(NumberString(x, y, z));
    }

    // x y--> z
    if (y >= b && (y-b) >= 0) {
        y = Down(y, b);
        z = Up(z, c);
        if (result.IndexOf(NumberString(x, y, z)) == -1) {
            result.Add(NumberString(x, y, z));
        }
        // System.Console.WriteLine(NumberString(x, y, z));
    }
}

foreach (var item in result.ToList()) {
    newXYZ = Convert.ToInt32(item);
    z = newXYZ % 10;
    newXYZ = newXYZ / 10;
    y = newXYZ % 10;
    newXYZ = newXYZ / 10;
    x = newXYZ % 10;

    // шаги в сторону 
    // x--> y z
    while (x >= a && (x-a) >= 0) {
        x = Down(x, a);
        y = Up(y, b);
        if (result.IndexOf(NumberString(x, y, z)) == -1) {
            result.Add(NumberString(x, y, z));
        }
    }

    // x y--> z
    while (y >= b && (y-b) >= 0) {
        y = Down(y, b);
        z = Up(z, c);
        if (result.IndexOf(NumberString(x, y, z)) == -1) {
            result.Add(NumberString(x, y, z));
        }
    }
}

foreach (var item in result)
{
    System.Console.WriteLine(item);
}

System.Console.WriteLine();
System.Console.WriteLine($"{result.Count}");
/* 
удаление из списка дублирующихся эл-тов
https://www.techiedelight.com/ru/remove-duplicates-from-list-csharp/#:~:text=%D0%A7%D1%82%D0%BE%D0%B1%D1%8B%20%D0%BF%D1%80%D0%B5%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%B2%D0%B0%D1%82%D1%8C%20%D1%80%D0%B5%D0%B7%D1%83%D0%BB%D1%8C%D1%82%D0%B8%D1%80%D1%83%D1%8E%D1%89%D1%83%D1%8E%20%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D1%8C%20%D0%B2%20%D1%81%D0%BF%D0%B8%D1%81%D0%BE%D0%BA%2C%20%D0%B2%D1%8B%D0%B7%D0%BE%D0%B2%D0%B8%D1%82%D0%B5%20%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%20ToList()%20%D0%BC%D0%B5%D1%82%D0%BE%D0%B4.&text=%D0%AD%D1%82%D0%BE%20%D0%B2%D1%81%D0%B5%20%D0%BE%D0%B1%20%D1%83%D0%B4%D0%B0%D0%BB%D0%B5%D0%BD%D0%B8%D0%B8%20%D0%B4%D1%83%D0%B1%D0%BB%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D0%B2%20%D0%B8%D0%B7%20%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%B0%20%D0%B2%20C%23.
метод первый:

result = result.Distinct().ToList();
result.Sort(); // если ранее не делал
foreach (var item in result)
{
    System.Console.WriteLine(item);
}

*/
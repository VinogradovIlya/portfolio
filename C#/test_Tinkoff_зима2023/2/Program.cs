string[] abc = Console.ReadLine().Split();
int a = Convert.ToInt32(abc[0]);
int b = Convert.ToInt32(abc[1]);
int c = Convert.ToInt32(abc[2]);

string[] xyz = Console.ReadLine().Split();
int x = Convert.ToInt32(xyz[0]);
int y = Convert.ToInt32(xyz[1]);
int z = Convert.ToInt32(xyz[2]);

// преобразование цифр в число и строку
string NumberString (int chislo1, int chislo2, int chislo3) {
    string number = string.Empty;
    string strX = chislo1.ToString();
    string strY = chislo2.ToString();
    string strZ = chislo3.ToString();
    return number = strX + strY + strZ;
}

// int BA1(int y, int b) {
//     return y -= b;
// }
// int BA2(int x, int a) {
//     return x += a;
// }

void BC (int y, int b, int z, int c) {
    if (y > b) {
        y -= b;
        z += c;
    }
}

// void CB (int z, int c, int y, int b) {
//     if (z > c) {
//         z -= c;
//         y += b;
//     }
// }

List<string> result = new List<string>();

// функции перевода валюты в сторону
int BC1(int y, int b) {
    return y -= b;
}

int BC2(int z, int c) {
    return z += c;
}
result.Add(NumberString(x,y,z));

    
    if (x > a && x != 0) {
        int AB1(int x, int a) {
            return x -= a;
        }

        int AB2(int y, int b) {
            return y += b;
        }
        result.Add(NumberString(x,y,z));
    }

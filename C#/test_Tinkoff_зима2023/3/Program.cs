int n = Convert.ToInt32(Console.ReadLine());

/*
a+b = n
1 + 5 =6
2 + 4 =6
3 + 3 =6
4 + 2 =6
5 + 1 =6

nod 1 and 5 == 1
nod 2 / 4 == 2
nod 
*/

List<int> delA = new List<int>();
List<int> delB = new List<int>();
// nok(a, b) = a * b / nod
int a, b;
int nok;
int proverka;
// int nod = 0;
int nod;
for (a = 1; a < n; a++) {
    b = n-a;
    nod = 0;
    Od(a, b);
    Nod(delA, delB);
    Nok(a, b, nod);

    proverka = nok;
    if (nok < proverka) proverka = nok;

    System.Console.WriteLine("------");
    System.Console.WriteLine("nod = {0}", nod); 
    System.Console.WriteLine("nok = {0}", nok);    
    System.Console.WriteLine("------");

    delA.Clear();
    delB.Clear();
}

void Od(int a, int b) {
    for (int i = 1; i <= a; i++) {
        if (a % i == 0) delA.Add(i);
    }

    for (int i = 1; i <= b; i++) {
        if (b % i == 0) delB.Add(i);
    }

    foreach (var item in delA)
    {
        System.Console.WriteLine($"{item}");
    }
    System.Console.WriteLine();

    foreach (var item in delB)
    {
        System.Console.WriteLine($"{item}");
    }
    System.Console.WriteLine();
}

int Nod(List<int> delA, List<int> delB) {
    int sizeA = delA.Count() - 1;
    int sizeB = delB.Count() - 1;
    for (int i = sizeA; i >= 0; i--) {
        for (int j = sizeB; j >= 0; j--) {
            if (delA[i] == delB[j]) return nod = delA[i];
        }
        return 1;
    }
    return 1;
}

int Nok(int a, int b, int nod) {
    nok = a * b / nod;
    return nok;
}


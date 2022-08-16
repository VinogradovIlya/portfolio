int Fibinnacci(int n) {
    if (n == 1 || n == 2) return 1;
    else return Fibinnacci(n - 1) + Fibinnacci(n - 2);
}
for (int i = 1; i < 10; i++)
{
    Console.WriteLine(Fibinnacci(i));
}
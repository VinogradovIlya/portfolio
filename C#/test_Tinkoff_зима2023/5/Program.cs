string[] inputNM = Console.ReadLine().Split();
int n = Convert.ToInt32(inputNM[0]);
int m = Convert.ToInt32(inputNM[1]);

List<string> input = new List<string> (m);
for (int i = 0; i < m; i++) {
    input.Add(Console.ReadLine());
}
input.Sort();
System.Console.WriteLine();
foreach (string item in input)
{
    System.Console.WriteLine(item);
}

// построение подходящего маршрута
List<string> path0 = new List<string> (m);
foreach (string item in input)
{
    string[] numbers = item.Split();
    int chet = Convert.ToInt32(numbers[2]);
    if (chet == 0) path0.Add(item);
}

System.Console.WriteLine();
foreach (string item in path0)
{
    System.Console.WriteLine(item);
}


List<string> path1 = new List<string> (m);
foreach (string item in input)
{
    string[] numbers = item.Split();
    int chet = Convert.ToInt32(numbers[2]);
    if (chet == 1) path1.Add(item);
}

System.Console.WriteLine();
foreach (string item in path1)
{
    System.Console.WriteLine(item);
}

// ответы
// System.Console.WriteLine(!!!!.Count);

/**************
работает при четном m
*/
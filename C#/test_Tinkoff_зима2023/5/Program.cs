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

// построение маршрута
List<string> path = new List<string> (m);
for (int i = 1; i < m; i+=2) {

    string[] start = input[i-1].Split();
    int number1 = Convert.ToInt32(start[0]);
    int number2 = Convert.ToInt32(start[1]);
    int number3 = Convert.ToInt32(start[2]);

    string[] finish = input[i].Split();
    int number11 = Convert.ToInt32(finish[0]);
    int number21 = Convert.ToInt32(finish[1]);
    int number31 = Convert.ToInt32(finish[2]);

    if (number2 <= number21) path.Add(input[i-1]); 
}

System.Console.WriteLine();
foreach (string item in path)
{
    System.Console.WriteLine(item);
}

// ответы
System.Console.WriteLine(path.Count);
// string result = string.Empty;
// foreach (string item in path)
// {
//     string[] str = item.Split();
//     string chet = str[2];
//     result = chet + " ";
// }
// System.Console.WriteLine(result);



/**************
работает при четном m
*/
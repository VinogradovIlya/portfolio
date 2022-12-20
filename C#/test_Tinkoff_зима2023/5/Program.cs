string[] inputNM = Console.ReadLine().Split();
int n = Convert.ToInt32(inputNM[0]);
int m = Convert.ToInt32(inputNM[1]);

List<string> input = new List<string> (m);
for (int i = 0; i < m; i++) {
    input.Add(Console.ReadLine());
}

// построение маршрутов
List<string> path = new List<string> (m);
// иду от обратного
for (int i = n; i > 0; i--) {
    for (int j = 0; j < m; j++) {
        string[] finish = input[j].Split();
        int number = Convert.ToInt32(finish[0]);
        int number1 = Convert.ToInt32(finish[1]);
        int number2 = Convert.ToInt32(finish[2]);
        if (number1 == i) path.Add(input[j]);
    }
}

System.Console.WriteLine();
foreach (string item in path)
{
    System.Console.WriteLine(item);
}



// ответы
// System.Console.WriteLine(!!!!.Count);

// // костыль
// string result = string.Empty;
// for (int i = 1; i < n; i++)
// {
//     string[] str = path[i-1].Split();
//     string aero = str[0];
//     string chet = str[2];
//     System.Console.WriteLine($"{aero} aero = {chet}");
//     result = result + chet;
//     if (i == n-1) {
//         aero = Convert.ToString(n);
//         //str = path.Count-1.Split();
//         int last = path.Count-1;
//         str = path[last].Split();
//         chet = str[2];
//         System.Console.WriteLine($"{aero} aero = {chet}");
//         result = result + chet;
//     }
// }
// System.Console.WriteLine(result);



/**************
работает при четном m
*/
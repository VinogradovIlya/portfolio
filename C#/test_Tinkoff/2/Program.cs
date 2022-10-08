Console.WriteLine("Аня - координатор стажировок в Тинькофф. Она хочет нанять самых сильных олимпиадников. Для того чтобы понять, кто же лучший, Аня решила проанализировать результаты командной олимпиады за последние N лет. Она знает все команды, занявшие первое место. Каждая команда задается тройкой имен, причем их порядок не важен, то есть записи ANTON BORIS CHRIS и BORIS ANTON CHRIS задают одну и ту же команду. Ане нужны лучшие из лучших, поэтому она хочет знать, какое максимальное число раз побеждала команда в одном и том же составе. Вы дружите с Аней, поэтому согласились ей помочь.");
Console.WriteLine("Формат входных данных");
Console.WriteLine("В первой строке задано одно целое число N (1 ≤ N ≤ 1000) - количество лет, за которые у Ани есть данные. В следующих N строках заданы команды-победители: в каждой строке указаны три разделенных пробелом имени. Каждое имя имеет длину от 1 до 10 символов, а также состоит из заглавных латинских символов ( A, ….., Z).");
Console.WriteLine("Формат выходных данных");
Console.WriteLine("В единственной строке выведите число - максимальное число побед команды в одинаковом составе.");
Console.WriteLine("Пример: 5");
Console.WriteLine("MIKHAIL\r\nVLADISLAV\r\nGRIGORY\r\nVLADISLAV\r\nMIKHAIL\r\nGRYGORY\r\nILYA IVAN\r\nVLADIMIR\r\nANDREY\r\nVLADIMIR ILYA\r\nVLADIMIR IVAN\r\nANDREY");

int n = Convert.ToInt32(Console.ReadLine());
string name = string.Empty;
string str = string.Empty;

for (int i = 0; i < n; i++) {
    name = Console.ReadLine();
    str = str + name + ' ';
}
    
str = str.ToUpper(); // ставит все буквы в верхний регистр (ToLower в нижний)
// Console.WriteLine(str);

string[] words = str.Split(' '); // делит строчку на слова
// Console.WriteLine(words[1]);

// разбивает слова - имена из строки по командам
for (int j = 0; j <= n*3; j+=3) {
    string team = words[j+0] + ' ' + words[j+1] + ' ' + words[j+2] + ' ';
    Console.WriteLine(team);
    if (j > n) break;
}
// int j = 0;
// while (j <= n*3) { 
//     string team = words[j+0] + ' ' + words[j+1] + ' ' + words[j+2] + ' ';
//     Console.WriteLine(team);
//     if (j > n) break;
//     j += 3;
// }

// основной метод
foreach (string s in words) {
    int result = 0;    
}
// мне нужно проверить сколько раз три слова фигурируют в строке

Console.WriteLine("Аня - координатор стажировок в Тинькофф. Она хочет нанять самых сильных олимпиадников. Для того чтобы понять, кто же лучший, Аня решила проанализировать результаты командной олимпиады за последние N лет. Она знает все команды, занявшие первое место. Каждая команда задается тройкой имен, причем их порядок не важен, то есть записи ANTON BORIS CHRIS и BORIS ANTON CHRIS задают одну и ту же команду. Ане нужны лучшие из лучших, поэтому она хочет знать, какое максимальное число раз побеждала команда в одном и том же составе. Вы дружите с Аней, поэтому согласились ей помочь.");
Console.WriteLine("Формат входных данных");
Console.WriteLine("В первой строке задано одно целое число N (1 ≤ N ≤ 1000) - количество лет, за которые у Ани есть данные. В следующих N строках заданы команды-победители: в каждой строке указаны три разделенных пробелом имени. Каждое имя имеет длину от 1 до 10 символов, а также состоит из заглавных латинских символов ( A, ….., Z).");
Console.WriteLine("Формат выходных данных");
Console.WriteLine("В единственной строке выведите число - максимальное число побед команды в одинаковом составе.");

// 5
// MIKHAIL VLADISLAV GRIGORY
// VLADISLAV MIKHAIL GRYGORY
// ILYA IVAN VLADIMIR
// ANDREY VLADIMIR ILYA
// VLADIMIR IVAN ANDREY

int n = Convert.ToInt32(Console.ReadLine());
string name = string.Empty;
string str = string.Empty;
string[] team = new string[n];

// чтение данных: сборка в строку + разбивка по командам
for (int i = 0; i < n; i++) {
    name = Console.ReadLine();
    team[i] = name.ToUpper();
    str = str + name + ' ';
}
str = str.ToUpper(); // ставит все буквы в верхний регистр (ToLower в нижний)
string[] words = str.Split(' '); // ? // делит строчку на слова

// основной метод (как работает foreach и IndexOf?)
int CountRep(string text, string sub ) {
    int count = 0;
    int pos = 0;
    while (true) {
        pos = text.IndexOf(sub, pos);
        if (pos != -1) {
            count++;
            pos++;
        } else {
            break;
        }
    }
    return count;
}
 Console.WriteLine(CountRep(str, team[0])); // ?
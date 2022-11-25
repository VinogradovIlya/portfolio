using System.Linq;
// Console.Clear();
// Console.WriteLine("Аня - координатор стажировок в Тинькофф. Она хочет нанять самых сильных олимпиадников. Для того чтобы понять, кто же лучший, Аня решила проанализировать результаты командной олимпиады за последние N лет. Она знает все команды, занявшие первое место. Каждая команда задается тройкой имен, причем их порядок не важен, то есть записи ANTON BORIS CHRIS и BORIS ANTON CHRIS задают одну и ту же команду. Ане нужны лучшие из лучших, поэтому она хочет знать, какое максимальное число раз побеждала команда в одном и том же составе. Вы дружите с Аней, поэтому согласились ей помочь.");
// Console.WriteLine("Формат входных данных");
// Console.WriteLine("В первой строке задано одно целое число N (1 ≤ N ≤ 1000) - количество лет, за которые у Ани есть данные. В следующих N строках заданы команды-победители: в каждой строке указаны три разделенных пробелом имени. Каждое имя имеет длину от 1 до 10 символов, а также состоит из заглавных латинских символов ( A, ….., Z).");
// Console.WriteLine("Формат выходных данных");
// Console.WriteLine("\nВ единственной строке выведите число - максимальное число побед команды в одинаковом составе.");

// 5
// MIKHAIL VLADISLAV GRIGORY
// // VLADISLAV MIKHAIL GRYGORY !!!!!  опечатка GRYGORY != GRIGORY
// VLADISLAV MIKHAIL GRIGORY
// ILYA IVAN VLADIMIR
// ANDREY VLADIMIR ILYA
// VLADIMIR IVAN ANDREY
// 2

// ввод
int n = Convert.ToInt32(Console.ReadLine());
if ((n < 1) || (n > 1000)) {
    Console.WriteLine("false");
} else {
    string str = string.Empty;
    string[] team = new string[n]; //?
    string[] person = new string[n];

    for (int i = 0; i < n; i++) {
        // чтение данных + калибровка
        team[i] = Console.ReadLine().ToUpper(); // ставит все буквы в верхний регистр (ToLower в нижний)

        // разбивка команды по составу
        person = team[i].Split(new char[] {' '}); // team[i].Split(' ');

        // сортировка
        Array.Sort(person);

        //сборка в строки 
        team[i] = string.Concat(person);
        str = str + team[i] + ' ';
}

// основной метод
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

// нахождение максимума
    int max = CountRep(str, team[0]);
    for (int i = 0; i < n; i++) {
    int nextValue = CountRep(str, team[i]);
    if (nextValue > max) max = nextValue;
}

// ответ
    Console.WriteLine("{0}", max); // Console.WriteLine($"{max}"); // Console.WriteLine(max + " ");
}


/**************************************
комментарии
StringBuilder (?)

разбить строку, положить в список, отсортировать и положить получившийся список в новую строчку
Array.Sort(name);

string[] arr = { "Sort", "Array", "C#" };
string[] sorted = arr.OrderBy(x => x).ToArray();
Console.WriteLine(String.Join(", ", sorted));

*/
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
    string[] team = new string[n]; 
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
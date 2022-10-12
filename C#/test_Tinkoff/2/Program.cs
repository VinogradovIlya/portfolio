Console.Clear();
Console.WriteLine("Аня - координатор стажировок в Тинькофф. Она хочет нанять самых сильных олимпиадников. Для того чтобы понять, кто же лучший, Аня решила проанализировать результаты командной олимпиады за последние N лет. Она знает все команды, занявшие первое место. Каждая команда задается тройкой имен, причем их порядок не важен, то есть записи ANTON BORIS CHRIS и BORIS ANTON CHRIS задают одну и ту же команду. Ане нужны лучшие из лучших, поэтому она хочет знать, какое максимальное число раз побеждала команда в одном и том же составе. Вы дружите с Аней, поэтому согласились ей помочь.");
Console.WriteLine("Формат входных данных");
Console.WriteLine("В первой строке задано одно целое число N (1 ≤ N ≤ 1000) - количество лет, за которые у Ани есть данные. В следующих N строках заданы команды-победители: в каждой строке указаны три разделенных пробелом имени. Каждое имя имеет длину от 1 до 10 символов, а также состоит из заглавных латинских символов ( A, ….., Z).");
Console.WriteLine("Формат выходных данных");
Console.WriteLine("\nВ единственной строке выведите число - максимальное число побед команды в одинаковом составе.");

// 5
// MIKHAIL VLADISLAV GRIGORY
// VLADISLAV MIKHAIL GRYGORY
// ILYA IVAN VLADIMIR
// ANDREY VLADIMIR ILYA
// VLADIMIR IVAN ANDREY
// 2

// ввод
int n = Convert.ToInt32(Console.ReadLine());
if ((n < 1) || (n > 1000)) {
    Console.WriteLine("false");
} else {
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

// основной метод (посмотреть foreach и IndexOf?)
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
// калибровка условий
    /*
    1 2 3
    ------------
    1 3 2
    3 2 1
    3 1 2
    2 1 3
    2 3 1
    */

// суть метода: если команда совпадает (какая команда?) с тремя словами из строчки, то max++
    void Proverka(string text, string sub) { 
        for (int i = 0; i < text.Length; i+=3) {
            string new_string = string.Empty;
            //new_string = text[0] + text[1] + text[2];
            int result = 0;
            //if (sub == new_string) result++; // самый простой вариант, где совпадение сразу
            if (sub == text[0] && text[1] && text[2]) result++;
            else {
                for (int i = 0; i < input.Length; i++) { // идет посимвольная проверка
                    if (input[i] == str[i]) { // пока символы совпадают все хорошо
                        Console.WriteLine("good");
                    } else { // работа с символами, которые не совпадают
                        for (int j = input.Length - i; j < input.Length; j++) { 
                            // if input[i] == input[j+1];
                            Console.WriteLine("bad");
                            break;
                        }
                    }
                }
            }
        }
            
    }

    Console.WriteLine("{0}", max); // Console.WriteLine($"{max}"); // Console.WriteLine(max + " ");
}
// Console.WriteLine("Один из ваших знакомых стал стажером-аналитиком в команде Тинькофф. У него есть данные за п дней о том, как клиенты подключают и отменяют подписки на один из сервисов. По странному стечению обстоятельств дни чередуются: в первый день подписки только подключались, во второй только отменялись и т.Д., т.е. каждый день число приобретенных подписок составляет (- 1)^(i-1)ai, где а, - число подключенных или отключечных подписок за 2-й день. Во время анализа данных ваш знакомый задался вопросом, увеличилась бы прибыль компании, если бы данные за какие-то дни поменялись местами. В качестве первого этапа он решил поменять местами не более двух дней. Проверьте, сможете ли вы стать стажером-аналитиком в Тинькофф. Для этого предлагаем вам посчитать максимально возможное значение прибыли, которую можно получить, поменяв местами данные за не более, чем два дня. Стоимость одной подписки можно считать равной 1.");
// Console.WriteLine("входные данные: \nВ первой строке задано одно натуральное число n (2 <= n <= 100000) - число дней, данные за которые у вас есть. Во второй строке заданы n чисел аі - количество подключенных/отмененных подписок за i-й день (1 <= і <= n, 1 <= ai <= 1000).");
// Console.WriteLine("Формат выходных данных: \nВ единственной строке выведите максимальную прибыль, которую можно получить, поменяв данные за не более, чем два дня. \nЗамечание \nМожно менять данные за не более, чем два дня, в том числе не менять ничего.");

// 2
// 1 2
// 1
// -------------
// 3
// 2 2 2
// 2

//ввод данных
int n = Convert.ToInt32(Console.ReadLine());
string[] input = Console.ReadLine().Split(new char[] {' '});
int[] numbers = new int[n];
for (int i = 0; i < n; i++) {
    numbers[i] = int.Parse(input[i].ToString());
}
int[] result = new int[n];


// работа с формулой 
int Formula(int n, int[] numbers) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int ai = numbers[i-1];
        int output = (int)Math.Pow(-1, i-1) * ai;
        sum = sum + output;
    }
    return sum;
}


// перестроение массива
// идея: проверять начиная с первого элемента, как выгоднее со следующим или через один
int[] Change(int n, int[] numbers) {
    int[] chislo1 = new int[n];
    int[] chislo2 = new int[n];
    int i = 0;
    int j = 1;
    while (i < n && j < n) {
        chislo1[i] = numbers[i];
        chislo1[j] = numbers[j];
        chislo2[i] = numbers[j];
        chislo2[j] = numbers[i];
        int sum1 = Formula(n, chislo1);
        int sum2 = Formula(n, chislo2);
        if (sum1 < sum2) {
            result[i] = numbers[j];
            result[j] = numbers[i];
        } else { 
            result[i] = numbers[i];
            result[j] = numbers[j];
        }
        i+=2;
        j+=2;
    }
    return result;
}

// сборка методов в один блок
if (n%2 == 0) {
    Change(n, numbers);
    // ответ
    Console.WriteLine("{0}", Formula(n, result));
} else {
    result[n-1] = numbers[n-1];
    Change(n, numbers);
    // ответ
    Console.WriteLine("{0}", Formula(n, result));
}


// // проверки
// Console.WriteLine("++++++++++++");

// // ответ
// Console.WriteLine("ответ с изменениями");
// Console.WriteLine("{0}", Formula(n, result));

// Console.WriteLine("ответ без изменений");
// Console.WriteLine("{0}", Formula(n, numbers));
// Console.WriteLine();

// Console.WriteLine("мой новый массив");
// for (int i = 0; i < n; i++) {
//     Console.Write(result[i]);
//     Console.Write(' ');
// }
// Console.WriteLine();
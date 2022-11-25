/***********************

Ввод
thats=zero 
a=10 
ten=a 
aboba=ten 
ten=-10
{
b=a
a=1337
c=a
{
d=a 
e=aboba
}
}
lol=a

Вывод
0
10
10
10
1337
1337
10
10

***********************/

List<string> input = new List<string>(); // инициализация списка (который List)
input.Add(Console.ReadLine());
foreach (string i in input) Console.WriteLine(i);

Environment.Exit(0);

// вопрос 1 -- реализация ввода 
// -- попробовать Environment.Exit(0);
// парсер конфигов
// вопрос 2 -- как реализовать присваивание 
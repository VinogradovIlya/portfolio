Console.WriteLine("<четное или нечетное>");
Console.Write("введите число: ");
int a = Convert.ToInt32(Console.ReadLine());
int result = a % 2;
if (result > 0) Console.Write("нечетное");
if (result == 0) Console.Write("четное");

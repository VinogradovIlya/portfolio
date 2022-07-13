Console.WriteLine("<четные из числа>");
Console.Write("введите число: ");
int a = Convert.ToInt32(Console.ReadLine()); // почему необходимо конвертировать string? в int, если я объявлял переменную как int? + в чем разница между int16, int32, int64?
if (a < 0) Console.Write("error");
int k;
int finish = 0;
for (k = 0; k < a - 1; k ++) {
    if (k % 2 <= 0) {
       finish = k + 2;
       Console.Write("{0} ", finish); 
    }
}
Console.WriteLine("В команде Тинькофф произошла реорганизация - объединились два отдела. Новые коллеги хотят сидеть рядом, поэтому офису требуется ремонт. Прежние места каждого отдела имели форму прямоугольника. Новая площадка должна быть квадратной, а также содержать предыдущие места, т.к. некоторые разработчики очень привязаны к ним. К сожалению, размеры офиса ограничены, поэтому зона должна иметь минимальную площадь. Строители пытаются посчитать, сколько материала им понадобится для ремонта. Для этого им нужно знать итоговую площадь обновленной площадки. Пожалуйста, помогите им. Формат входных данных В первой строке заданы четыре целых числа: х1, у1, x2, y2, где (x1, y1) и (x2, y2) - координаты левого нижнего и правого верхнего углов прежнего места первого отдела. Известно, что 0<= x1 < x2 <= 10 и 0<= y1 < y2 <= 10. Во второй строке заданы координаты места второго отдела в том же формате, что и первый. Гарантируется, что исходные площадки двух отделов не пересекаются, а так же не касаются друг друга. Формат выходных данных В единственной строке выведите одно число - площадь новой объединенной зоны.");
Console.WriteLine("пример:");
Console.WriteLine("6 6 8 8 ");
Console.WriteLine("1 8 4 9");
Console.WriteLine("вывод: 49");

string[] input1 = Console.ReadLine().Split(new char[] {' '});
string[] input2 = Console.ReadLine().Split(new char[] {' '});

int one = Convert.ToInt32(input1[0]);
int two = Convert.ToInt32(input1[1]);
int three = Convert.ToInt32(input1[2]);
int four = Convert.ToInt32(input1[3]);
int step1 = Math.Abs(one - three);
int step2 = Math.Abs(two - four);
int area1 = step1 * step2;

int five = Convert.ToInt32(input2[0]);
int six = Convert.ToInt32(input2[1]);
int seven = Convert.ToInt32(input2[2]);
int eight = Convert.ToInt32(input2[3]);
int step3 = seven - five;
int step4 = eight - six;
int area2 = step3 * step4;

int res = Convert.ToInt32(Math.Pow((area1 + area2), 2));
Console.WriteLine("{0}", res);
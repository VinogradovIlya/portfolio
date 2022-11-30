using System.Text.RegularExpressions;

// ввод данных
string[] input = Console.ReadLine().Split();
int n, q;
n = Convert.ToInt32(input[0]); 
q = Convert.ToInt32(input[1]);

// фамилии + список в алфавитном порядке
List<string> inputN = new List<string>(n);
for (int i = 0; i < n; i++) {
	inputN.Add(Console.ReadLine());
}
List<string> inputNSortCopy = new List<string>(inputN);
inputNSortCopy.Sort();

// запросы
string[] inputQ = new string[2];
List<int> numberZapros = new List<int>();
List<string> nameZapros = new List<string>();
for (int i = 0; i < q; i++) {
	inputQ = Console.ReadLine().Split();
	numberZapros.Add(Convert.ToInt32(inputQ[0]));
	nameZapros.Add(inputQ[1]);
}

List<string> surnameList = new List<string>(q);
void Sorted(List<string> inputNSortCopy, List<string> nameZapros, int i) {
	foreach (string surname in inputNSortCopy) { // прохожу по фамилиям из отсортированного массива
		if (Regex.IsMatch(surname, nameZapros[i], RegexOptions.IgnoreCase)) { // нахожу однокоренные фамилии
			surnameList.Add(surname); // добавляю подходящие элементы
		}
	}
	
	System.Console.WriteLine("---------");
	foreach (var item in surnameList)
	{
		System.Console.WriteLine(item);
	}
}

void Delete(List<string> surnameList, int i) {
	for (int j = 1; j < numberZapros[i]; j++) { //удаляю лишние предыдущие фамилии
		surnameList.RemoveAt(0);
	}
}

List<int> result = new List<int>();
// определяю номера искомых фамилий
void Result(List<string> surnameList, List<int> result, int i) {
	int chislo = inputN.IndexOf(surnameList[0]);
	chislo++;
	result.Add(chislo);
}

for (int i = 0; i < q; i++) {
	Sorted(inputNSortCopy, nameZapros, i);
	Delete(surnameList, i);
	Result(surnameList, result, i);
	surnameList.Clear();
}

//ответ
foreach (var item in result)
{
	Console.WriteLine(item);
}

/*********
bool Contains(T item): возвращает true, если элемент item есть в списке

int IndexOf(T item): возвращает индекс первого вхождения элемента в списке

алгоритм метода:
// --------------------
// 1. приходит отсортированный список
// (запрос 2 ab (в списке abc, aboba, ad, a, b))
// 2. из него вычленяются фамилии соответсвующие указанным условиям к буквам в фамилии (abc, aboba)
// 3. из нового отсеянного списка выбирается фамилия соответсвующая номеру в запросе (цифра 2 => aboba)
// 4. в исходном списке ищется указанная фамилия (aboba) и возвращается номер указанной фамилии
// --------------------

*/
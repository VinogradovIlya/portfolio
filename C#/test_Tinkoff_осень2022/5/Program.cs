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
}

List<int> result = new List<int>();
void Result(List<string> surnameList, List<int> numberZapros, int i, List<string> inputN, List<string> nameZapros) {
	// выбираю необходимые фамилии
	string[] surnameArray = surnameList.ToArray();
	int count = numberZapros[i];
	int chislo;
	if (count > 1) {
		int j = numberZapros[i]; // i на один меньше нужен
		if (j > q) { // если номер искомой фамилии заведомо больше списка всех фамилий
			result.Add(-1);
		} else {
			j--;
			string surname = surnameArray[j];
			chislo = inputN.IndexOf(surname);
			chislo++;
			result.Add(chislo);
		}
	} else {
		if (inputN.IndexOf(nameZapros[i]) == -1) { // если не присутствует искомая фамилия в списке всех фамилий
			result.Add(-1);
		} else {
			chislo = inputN.IndexOf(nameZapros[i]);
			chislo++;
			result.Add(chislo);
		}
	}
}

for (int i = 0; i < q; i++) {
	Sorted(inputNSortCopy, nameZapros, i);
	Result(surnameList, numberZapros, i, inputN, nameZapros);
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
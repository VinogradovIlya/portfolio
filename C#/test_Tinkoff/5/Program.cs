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

 List<int> result = new List<int>(q);

Sort(inputN, inputNSortCopy, numberZapros, nameZapros);
// --------------------
// 1. приходит отсортированный список
// (запрос 2 ab (в списке abc, aboba, ad, a, b))
// 2. из него вычленяются фамилии соответсвующие указанным условиям к буквам в фамилии (abc, aboba)
// 3. из нового отсеянного списка выбирается фамилия соответсвующая номеру в запросе (цифра 2 => aboba)
// 4. в исходном списке ищется указанная фамилия (aboba) и возвращается номер указанной фамилии
// --------------------
void Sort(List<string> inputN, List<string> inputNSortCopy, 
	List<int> numberZapros, List<string> nameZapros) {
	
	List<string> surnameList = new List<string>(q);
	int count = nameZapros.Count; // == q
	for (int i = 0; i < count; i++) { // прохожу по каждому запросу
		foreach (string surname in inputNSortCopy) { // прохожу по фамилиям из отсортированного массива
			if (Regex.IsMatch(surname, nameZapros[i], RegexOptions.IgnoreCase)) { // нахожу однокоренные фамилии
				surnameList.Add(surname); // добавляю подходящие элементы
			}
		}

		for (int j = 1; j < numberZapros[i]; j++) { //удаляю лишние предыдущие фамилии
			surnameList.RemoveAt(0);
		}
	}

	Console.WriteLine("------"); // test
	foreach (var item in surnameList)
	{
		Console.WriteLine(item);
	}

}


/*********
bool Contains(T item): возвращает true, если элемент item есть в списке

int IndexOf(T item): возвращает индекс первого вхождения элемента в списке
				//int vhod = inputNSortCopy.IndexOf(nameZapros[number]);
				// inputNSortCopy.Remove(inputNSortCopy[vhod]);

алгоритм метода:
что входит: фамилии (+ место для хранения отсортированного списка) + условия
что выходит номер фамилии в неотсортированном списке

как работает метод

указывается первое вхождение фамилии по указанным условиям в отсортированном списке
сохраняется позиция

string[] rows = {"Москва— столица Российской Федерации.",
                         "Это предложение оказалось здесь случайно",
                         "Москва - город федерального значения, административный центр Центрального федерального округа и центр Московской области.",
                         "Жители столицы - москвичи.",
                         "Как и это."};
        foreach (string row in rows)
        {
            if (Regex.IsMatch(row, "моск", RegexOptions.IgnoreCase)) Указывает, обнаружено ли в указанной входной строке соответствие заданному регулярному выражению, используя указанные параметры сопоставления.
                Console.WriteLine(row);
            foreach (Match match in Regex.Matches(row, @"\b\w*моск\w*\b", RegexOptions.IgnoreCase))
                Console.WriteLine("\t\t{0}", match.Value);
        }
*/
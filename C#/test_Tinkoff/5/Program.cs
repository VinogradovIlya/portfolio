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

Console.WriteLine("------"); // test
foreach (string item in inputNSortCopy) {
	Console.WriteLine(item);
}
Console.WriteLine("------");

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
	
	int count = numberZapros.Count; // == q
	for (int i = 0; i < count; i++) { // прохожу по всем запросам

		for (int j = 0; j < numberZapros[i]; j++) { 
// циклом прохожу по всем числам из запросов и удаляю более ранние вхождения
			
			int vhod = inputNSortCopy.IndexOf(nameZapros[j]); // возвращает int позицию первого вхождения
			inputNSortCopy.Remove(inputNSortCopy[vhod]);
		}

		foreach (var item in inputNSortCopy)
		{
			Console.WriteLine(item);
		}
	}
	

}


/*********
bool Contains(T item): возвращает true, если элемент item есть в списке

int IndexOf(T item): возвращает индекс первого вхождения элемента в списке

алгоритм метода:
что входит: фамилии (+ место для хранения отсортированного списка) + условия
что выходит номер фамилии в неотсортированном списке

как работает метод

указывается первое вхождение фамилии по указанным условиям в отсортированном списке
сохраняется позиция


*/
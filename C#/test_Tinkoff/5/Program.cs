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
for (int i = 0; i < q; i++) {
	inputQ = Console.ReadLine().Split();
	int numberZapros = Convert.ToInt32(inputQ[0]);
	string nameZapros = inputQ[1];

	Sort(inputN, inputNSortCopy, numberZapros, nameZapros);
}

List<int> result = new List<int>(q);
// --------------------
// 1. приходит отсортированный список
// (запрос 2 ab (в списке abc, aboba, ad, a, b))
// 2. из него вычленяются фамилии соответсвующие указанным условиям к буквам в фамилии (abc, aboba)
// 3. из нового отсеянного списка выбирается фамилия соответсвующая номеру в запросе (цифра 2 => aboba)
// 4. в исходном списке ищется указанная фамилия (aboba) и возвращается номер указанной фамилии
// --------------------
// использовать indexOf?
void Sort(List<string> inputN, List<string> inputNSortCopy, int numberZapros, string nameZapros) {

	int vhod;
	for (int i = 0; i < numberZapros; i++) {
		vhod = inputNSortCopy.IndexOf(nameZapros); // возвращает первое вхождение
		//if (vhod == -1) return result.Add(-1);
		inputNSortCopy.Remove(inputNSortCopy[vhod]);
		
		Console.WriteLine(inputNSortCopy[vhod]);
	}
	// Console.WriteLine(inputNSortCopy[vhod]);
	

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
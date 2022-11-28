// ввод данных
string[] input = Console.ReadLine().Split();
int n, q;
n = Convert.ToInt32(input[0]); 
q = Convert.ToInt32(input[1]);

// фамилии
List<string> inputN = new List<string>();
for (int i = 1; i <= n; i++) {
	inputN.Add(Console.ReadLine());
}

// запросы (доработать)
string[] inputQ = new string[2];
for (int i = 0; i < q; i++) {
	inputQ = Console.ReadLine().Split();
	int numberZapros = Convert.ToInt32(inputQ[0]);
	string nameZapros = inputQ[1];

	Sort(inputN, inputQ, numberZapros, nameZapros);
}

// --------------------
// 1. приходит отсортированный список
// (запрос 2 ab (в списке abc, aboba, ad, a, b))
// 2. из него вычленяются фамилии соответсвующие указанным условиям к буквам в фамилии (abc, aboba)
// 3. из нового отсеянного списка выбирается фамилия соответсвующая номеру в запросе (цифра 2 => aboba)
// 4. в исходном списке ищется указанная фамилия (aboba) и возвращается номер указанной фамилии
// --------------------
// использовать indexOf?
void Sort(List<string> inputN, string[] inputQ, int numberZapros, string nameZapros) {
	inputN.Sort();
	foreach (string name in inputN) {
		Console.WriteLine(name);
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
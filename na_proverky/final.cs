Console.WriteLine("введите данные: ");
string[] text = Console.ReadLine().Split(new Char[] { ' ' });

StringSize(text);
void StringSize(string[] text) {
    for (int i = 0; i < text.Length; i++) {
        if (text[i].Length <= 3) Console.WriteLine(text[i]);
    }
}
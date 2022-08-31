Console.WriteLine("Дан текст. В тексте нужно все пробелы заменить черточками, маленькие буквы “к” заменить большими “К”, а большие “С” заменить маленькими “с”.");

Console.WriteLine("введите текст для правок: ");
string text = Console.ReadLine();
Console.WriteLine("введите символ для замены: ");
char oldValue = Convert.ToChar(Console.ReadLine());
Console.WriteLine("введите символ на замену: ");
char newValue = Convert.ToChar(Console.ReadLine());

string Replace(string text, char oldValue, char newValue) {
    string result = String.Empty;
    int length = text.Length;
    for (int i = 0; i < length; i++) {
        if (text[i] == oldValue) result = result + $"{newValue}";
        else result = result + $"{text[i]}";
    }
    return result;
}

string newText = Replace(text, oldValue, newValue);
Console.WriteLine(newText);
Console.WriteLine("введите данные: ");
string text = Console.ReadLine();


string StringSize(string text) {
    
    int count = 0;
    
    for (int i = 0; i < text.Length; i++) {
        if (text[i] == " ") count = 0;
        else {
            int newCount = 0;
            newCount++;
            string rezult = string.Empty;
            if (newCount <= 3) result = result + $"{text[i]}";
        }
    }
    return result;
}
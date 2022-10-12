Console.Clear();
Console.WriteLine("1 2 3 == 3 2 1?");

/*
1 2 3
------------
1 3 2
3 2 1
3 1 2
2 1 3
2 3 1
*/

// суть метода: если команда совпадает (какая команда?) с тремя словами из строчки, то max++
void Proverka(string text, string sub) { 

    if (input == str) Console.WriteLine("yes"); // самый простой вариант, где совпадение сразу
    else {
        for (int i = 0; i < input.Length; i++) { // идет посимвольная проверка
            if (input[i] == str[i]) { // пока символы совпадают все хорошо
                Console.WriteLine("good");
            } else { // работа с символами, которые не совпадают
                for (int j = input.Length - i; j < input.Length; j++) { 
                    // if input[i] == input[j+1];
                    Console.WriteLine("bad");
                    break;
                }
            }
        }
    }
}
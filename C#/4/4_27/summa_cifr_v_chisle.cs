Console.WriteLine("Напишите программу, которая принимает на вход число и выдаёт сумму цифр в числе.");
// /*
// будет три метода: 
// первый считает десятки
// второй метод делит заданное число на цифры
// третий считает сумму
// */

//ввод
Console.Write("введите число: ");
string chislo = Console.ReadLine();
int result = 0;
int razryad = 0;
int number = Convert.ToInt32(chislo);
int desyatki = 1;

// int Summ(int number, int desyatki, int chislo) {
//     for (int i = 0; i < chislo.Length; i++) {
//     result = number % desyatki;
//     }
//     return result;
// }
// Console.WriteLine(Summ(number, desyatki));


// // //подсчет разрядности
// // Razryad(chislo);
// // int Razryad(string chislo) {
// //     razryad = chislo.Length - 1;
// //     return razryad;
// // }

// // //получение десяток для деления
// // Desyatki(razryad, desyatki);
// // int Desyatki(int razryad, int desyatki) {
// //     for (int i = 0; i < razryad; i++) {
// //         desyatki = desyatki * 10;
// //         //return desyatki;
// //     }
// //     return desyatki;
// // }
// // Console.WriteLine(Desyatki(razryad, desyatki));
// // Console.WriteLine("{0}", desyatki);

// // //сумма цифр в числе
// // Summ(number, desyatki);
// // int Summ(int number, int desyatki) {
// //     int summa = 1;
// //     summa = summa + (number % desyatki);
// //     int result = 0;
// //     result = result + summa;
// //     return result;
// // }
// // //Console.WriteLine("{0}", Summ(number, desyatki));

//*******************************************************

PrintArray(chislo);
void PrintArray(string chislo) {
    for (int i = 0; i < chislo.Length; i++) {
        double sum = Convert.ToInt32(chislo[i]);
        Console.Write("{0} = ", chislo[i]);
        Console.WriteLine("{0} ", sum);
    }
}
Console.WriteLine();

Console.WriteLine("{0}", Array(chislo));
double Array(string chislo) {
    for (int i = 1; i < chislo.Length; i++) {
        Console.Write("{0} ", chislo[i]);
        Console.Write("{0} ", chislo[i - 1]);
        return chislo[i - 1] + chislo[i];
    }
    return 1;
}
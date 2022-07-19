Console.WriteLine("Напишите программу, которая выводит третью цифру заданного числа или сообщает, что третьей цифры нет.");

void zadacha() {
    Console.WriteLine("введите число: ");
    string chislo = Console.ReadLine();
    Console.WriteLine(chislo[2]);
}
zadacha();


/*********************************************************
посмотрите пожалуйста, что надо было сделать с этим чудом(((((((((
void zadacha() {
    Console.WriteLine("введите число: ");
    int input = Convert.ToInt32(Console.ReadLine());
    int step1 = input / 10;
    int step2 = input % 100 % 10;
    if (input < 100) {
        Console.Write("третьей цифры нет");
    }
    if (input > 1000) {
        int new_input = 0;
        do {
            new_input = input / 10;
        }
        while (input > 1000);
        new_input = input / 10;
        int step_1 = new_input % 100 % 10;
        Console.Write("{0}", step_1);
    }
    if (input > 100 && input < 1000) {
        Console.Write("{0}", step2);
    }
}

zadacha();

//как это все совместить?(
// int put() {
//     int input = Convert.ToInt32(Console.ReadLine());
//     Console.Write(input);
//     return input;
// }

// int zadacha(int put) {
//     int step1 = input % 100;
//     int step2 = step1 % 10;
//     return step2;
// }

// void main() {
//     Console.WriteLine("введите число: ");
//     put();
//     zadacha(put);
//     Console.Write("{0}", put);
// }

// // int zadacha() {
// //     Console.WriteLine("введите число: ");
// //     int chislo = Convert.ToInt32(Console.ReadLine());
// //     int result;
// //     if (chislo < 100) { // проверка есть ли третий знак
// //         Console.Write("третьей цифры нет");
// //     } result = chislo % 10;
// //     if (chislo < 1000 && chislo > 100) { // третий знак
// //         result = chislo % 10;
// //     }
// //     if (chislo < 10000 && chislo > 1000) { // 3/4
// //         result = (chislo % 100 - chislo % 10) / 10;
// //     }
// //     if (chislo < 100000 && chislo > 10000) { // 3/5
// //         result = (chislo % 1000 - chislo % 100) / 100;
// //     } else {
// //         Console.WriteLine("молодец держи"); // 3/6
// //         if (chislo < 1000000 && chislo > 100000) {
// //         result = (chislo % 10000 - chislo % 1000) / 1000;
// //         }
// //     }
// //     return result;
// // }

// // Console.Write(zadacha());

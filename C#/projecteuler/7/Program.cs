using System;
using System.Collections.Generic;

/**
https://projecteuler.net/problem=24

Перестановка — это упорядоченное расположение объектов.
Например, 3124 — это одна из возможных перестановок цифр 1, 2, 3 и 4.
Если все перестановки перечислены в числовом или алфавитном порядке, мы называем это лексикографическим порядком.
Лексикографические перестановки 0, 1 и 2:
012 021 102 120 201 210
Какова миллионная лексикографическая перестановка цифр 0, 1, 2, 3, 4, 5, 6, 7, 8 и 9?
*/

class Program
{
    static void Main(string[] args)
    {
        int[] arr = new int[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        List<string> list = new List<string>();
        ShowAllCombinations(arr, list);
        System.Console.WriteLine(list[999999]);
    }
    
    public static List<string> ShowAllCombinations<T>(IList<T> arr, List<string> list = null, string current = "")
    {
        if (list == null) list = new List<string>();
        if (arr.Count == 0) //если все элементы использованы, выводим на консоль получившуюся строку и возвращаемся
        {
            list.Add(current);
            // System.Console.WriteLine(current);
            return list;
        }
        for (int i = 0; i < arr.Count; i++) //в цикле для каждого элемента прибавляем его к итоговой строке, создаем новый список из оставшихся элементов, и вызываем эту же функцию рекурсивно с новыми параметрами.
        {
            List<T> lst = new List<T>(arr);
            lst.RemoveAt(i);
            ShowAllCombinations(lst, list, current + arr[i].ToString());
        }
        return list;
    }
}

/**
перепроверить
Почитайте про Generics. T-это произвольный тип. Вдруг вы захотите вместо массива чисел подать массив строк, к примеру, или каких-то своих объектов? Для данного метода не будет никакой разницы, ведь преобразовать к строке можно любой объект при помощи метода ToString().

IList -- интерфейс. Можно подавать любую коллекцию, которая реализует этот интерфейс. Массив, список и тд.
*/
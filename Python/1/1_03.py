from traceback import print_list

print('Напишите программу, которая будет на вход принимать число N и выводить числа от -N до N. \n*Примеры:* \n- 5 -> -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5')

n = abs(int(input('введите число N: ')))
if n > 0:
    new_n = -1 * n
    for new_n in range(new_n, n+1):
        print(new_n, sep=' ', end=' ')
else: print(n)
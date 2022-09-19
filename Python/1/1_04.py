# tuple -- ?
print('Напишите программу, которая будет принимать на вход дробь и показывать первую цифру дробной части числа. \n*Примеры:* \n- 6,78 -> 7')

n = abs(float(input('введите число: ')))
# n = int(input('введите число: ').split('.'))
new_n = n % 1
new_n *= 10
new_new_n = new_n % 1 #как привести к типу int?
final = new_n - new_new_n
if final == 0:
    print('нет')
else: print(round(final))
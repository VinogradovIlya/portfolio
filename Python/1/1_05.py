print('Напишите программу, которая принимает на вход число и проверяет, кратно ли оно 5 и 10 или 15, но не 30.')

# number = abs(int(input('введите число: '))) ничего не дает
number = int(input('введите число: '))
divisibility_5 = number // 5
divisibility_5_0 = number / 5
if divisibility_5 != divisibility_5_0:
    print('no')
else: print('yes')

divisibility_10 = number // 10
divisibility_10_0 = number / 10
if divisibility_10 != divisibility_10_0:
    print('no')
else: print('yes')

divisibility_15 = number // 15
divisibility_15_0 = number / 15
if divisibility_15 != divisibility_15_0:
    print('no')
else: print('yes')


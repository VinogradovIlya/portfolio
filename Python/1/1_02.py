print('Напишите программу, которая на вход принимает 5 чисел и находит максимальное из них.')

# ?????????????????
# a = int(input('первое число: '))
# b = int(input('второе число: '))
# c = int(input('третье число: '))
# d = int(input('четвертое число: '))
# e = int(input('пятое число: '))

# max = a
# print(max)

# if b > max:
#     max = b
# elif c > max:
#     max = c
# elif d > max:
#     max = d
# elif e > max: 
#     max = e

# print(max)

# list
num = [int(i) for i in input().split()[:5]] #! + [:5] -- задает размерность листа/массива
max_num = num[0]
for i in range(len(num)):
    if num[i] > max_num:
        max_num = num[i]
print(num)
print(max_num)
print(max(num))
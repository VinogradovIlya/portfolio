print('Напишите программу, которая принимает на вход вещественное число и показывает сумму его цифр.\nПример:\n- 6782 -> 23')

##################костыль#######################
chislo = [int(i) for i in input().split('.')]

summa1 = chislo[0]
summa2 = chislo[1]

count = 0
while summa1 != 0:
    new_sum = summa1 % 10 
    summa1 = (summa1 - new_sum) / 10
    count = count + new_sum
while summa2 != 0:
    new_sum = summa2 % 10 
    summa2 = (summa2 - new_sum) / 10
    count = count + new_sum
print(int(count))


# chislo = abs(float(input('введите число: ')))

# if chislo % 1 == 0:
#     count = 0
#     while chislo != 0:
#         new_chislo = chislo % 10 
#         chislo = (chislo - new_chislo) / 10
#         count = count + new_chislo
##         print('{} - {} - {}'.format(chislo, new_chislo, count))
#     print(int(count))
# else: 
#     count = 0
#     new_count = 0
#     while chislo != 0:
#         new_chislo = chislo % 10 
#         desyatki = chislo % 1 #до какого момента их увеличивать?
#         chislo = (chislo - new_chislo) / 10
#         count = count + new_chislo
#         #print('{} - {} - {}'.format(chislo, new_chislo, count))
#     print(int(count))
#     print(desyatki)

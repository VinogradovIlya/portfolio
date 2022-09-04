from xmlrpc.client import boolean


print('hello world')

# типы данных и переменная
# int, float, boolean, str, lis, None
a = 123
b = 1.23
value = None
s = "hello world"
print('a \nb')
f = True
list = []
print(list)
list = [1, 2, 3]
print(list)

# вывод строк
print(a, b, s, f)
print(a, '-', b, '-', s, '-', f)
print(f'{a} - {b} - {s} - {f}')
print('{} - {} - {} - {}'.format(a, b, s, f))

# ввод данных
print('введите данные: ')
a = input()
print('введите данные: ')
b = input()
print(a, ' + ', b, ' = ', a+b)

print('введите данные: ')
a = int(input())
print('введите данные: ')
b = int(input())
print(a, ' + ', b, ' = ', a+b)

# бинарный минус и бинарный плюс
# арифметические операции
# +, -, *, /, %, //, **
# (), сокращенные операции


a = +123
b = -456
c = a + b
print(c)

a = 10
b = 6
c = a / b
print(c)

a = 10
b = 6
c = a // b
print(c)

a = 8
b = 2
c = a ** b 
print(c)

a = 1.3
b = 3
c = round(a * b)
j = round(a * b, 3) 
print(c, j)

# Логические операции
# <, <=, >, >=, ==, !=
# not, and, or не путать с &, |, ^
# кое что еще: is, is not, in, hot in

f = [1, 2, 3, 4]
print(f)
print(2 in f)
is_odd = f[0] % 2 == 0
print(is_odd)

q = 1
w = 2
e = 3
print(q < w < e)

# управляющие конструкции if, if-else
a = int(input('a = '))
b = int(input('b = '))
if a > b:
    print(a)
else:
    print(b)

# или
day = input('введите день недели: ')
if day == '1':
    print('нет')
elif day == '2':
    print('нет')
elif day == '3':
    print('нет')
elif day == '4':
    print('нет')
elif day == '5':
    print('нет')
elif day == '6':
    print('да')
elif day == '7':
    print('да')
else: print('пробуй еще')

# циклы
# while и while - else
original = 23
inverted = 0
while original != 0:
    inverted = inverted * 10 + (original % 10)
    original //= 10
print(inverted)

# for
for i in 1, 2, 3, 4, 5:
    print(i**2)

for i in range(1, 11, 2):
    print(i)

# немного о строках
text = 'съешь еще этих французских булок'
print(len(text))  # 39
print('еще' in text) # true
print(text.isdigit())
print(text.islower())
print(text.replace('еще' , 'ЕЩЕ'))

for c in text:
    print(c)


# cреды
text = 'съешь еще этих французских булок'
print(text[0])
print(text[1])
print(text[len(text)-1])
print(text[-5])
print(text[:])
print(text[:2])
print(text[len(text)-2:])
print(text[2:9])
print(text[6:-18])
print(text[0:len(text):6])
print(text[::6])

# списки

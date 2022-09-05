print('Напишите программу, которая принимает на вход координаты двух точек и находит расстояние между ними в 2D пространстве.')

print('введите первую пару координат: ')
x1 = int(input())
y1 = int(input())

print('введите вторую пару координат: ')
x2 = [int(input().split(','))]
y2 = [int(input().split(','))]

katet1 = (x2 - x1)**2
katet2 = (y2 - y1)**2
gipotenyza = (katet1 + katet2)**(0.5)
print(round(gipotenyza, 3))

# a = [int(i) for i in input('введите координаты первой точки пример "12,6" a=').split(',')]
# b = [int(i) for i in input('введите координаты первой точки пример "7,2" b=').split(',')]

# len_line = ((a[0]-b[0])**2+(a[1]-b[1])**2)**(0.5)

# print(round(len_line, 3))
print('В текстовом файле посчитать количество строк, а также для каждой отдельной строки определить количество в ней символов и слов.')

lines = 0
with open('text') as file:
    for line in file:
        lines += 1
        symbols = 0
        words = 0
        for s in line:
            symbols += 1
            if s != ' ' and symbols == 0:
                words += 1
                symbols = 1
            elif s == ' ':
                symbols = 0
print('количество строк: ', lines)
print('количество слов: ', len(line))
print('количество символов: ', words)
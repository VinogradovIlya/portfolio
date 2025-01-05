def main():
    try:
        with (
            open('ds.csv', 'r', encoding='utf-8') as f,
            open('ds.tsv', 'w', encoding='utf-8') as fw,
        ):
            res = []
            for line in f:
                line = line.replace('","', '"\t"')
                line = line.replace('",', '"\t')
                line = line.replace(',"', '\t"')
                line = line.split('\t')
                last, temp = line[-1], line[-2].split(',')
                line = line[:-2] + temp + [last]
                res.append(line)
            res = list(map(lambda x: '\t'.join(x), res))
            for i in res:
                fw.write(i)
    except FileNotFoundError:
        print(f'Файл ds.csv не найден.')


if __name__ == '__main__':
    main()

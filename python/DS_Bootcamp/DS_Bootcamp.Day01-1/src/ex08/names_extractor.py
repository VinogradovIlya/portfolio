import sys


def names_extractor(email: str) -> str:
    return '\t'.join(map(lambda x: x.title(), email[:-10].split('.')))


def main(path: str):
    with (open(path, 'r') as f,
          open('employees.tsv', 'w') as f_out,
          ):
        f_out.write('Name\tSurname\tE-mail\n')
        for line in f:
            if 'mail' in line.lower():
                continue
            f_out.write(names_extractor(line) + '\t' + line)


if __name__ == '__main__':
    main(sys.argv[1])

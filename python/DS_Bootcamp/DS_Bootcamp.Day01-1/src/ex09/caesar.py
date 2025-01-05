import sys


def encode(string: str, shift: int) -> str:
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    alphabet_rus = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'
    res = ''
    len_en = len(alphabet)
    for char in alphabet_rus:
        if char in string:
            raise ValueError("The script does not support your language yet")
        if char.upper() in string:
            raise ValueError("The script does not support your language yet")

    for char in string:
        up = char.isupper()
        char_lower = char.lower()
        if char_lower in alphabet:
            new_index = (alphabet.index(char_lower) + shift) % len_en
            res += alphabet[new_index].upper() if up else alphabet[new_index]
        else:
            res += char
    return res


def decode(string: str, shift: int) -> str:
    return encode(string, -shift)


if __name__ == '__main__':
    if len(sys.argv) == 4:
        if sys.argv[1] == 'encode':
            print(encode(sys.argv[2], int(sys.argv[3])))
        elif sys.argv[1] == 'decode':
            print(decode(sys.argv[2], int(sys.argv[3])))
    else:
        raise ValueError("Invalid number of arguments")

# python3 caesar.py encode hello 100
# python3 caesar.py encode Hello 12

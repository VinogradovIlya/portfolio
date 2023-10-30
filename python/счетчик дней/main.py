import os
from pathlib import Path
import datetime
import json


def create(event: str) -> None:
    data = {}
    try:
        with open(DIR / 'счетчик дней.json', 'r') as file:
            data = json.load(file)
    except FileNotFoundError:
        pass
    data[event] = str(datetime.datetime.today())
    with open(DIR / 'счетчик дней.json', 'w') as file:
        json.dump(data, file)


def update(event: str) -> None:
    with open(DIR / 'счетчик дней.json', 'r+') as file:
        data = json.load(file)
        if event in data:
            data[event] = str(datetime.datetime.today())
            file.seek(0)
            json.dump(data, file)
            file.truncate()
        else:
            print(f"{event} отсутвует")


def delete(event: str) -> None:
    with open(DIR / 'счетчик дней.json', 'r+') as file:
        data = json.load(file)
        if event in data:
            del data[event]
            file.seek(0)
            json.dump(data, file)
            file.truncate()
        else:
            print(f"{event} отсутвует")


def show() -> None:
    if os.path.exists(DIR / 'счетчик дней.json'):
        with open('счетчик дней.json', 'r') as file:
            data = json.load(file)
            now = datetime.datetime.today()
            for i in data:
                old_day = datetime.datetime.strptime(
                    data[i], "%Y-%m-%d %H:%M:%S.%f")
                print(
                    f"С события {i} прошло {(now - old_day).days} дней & {int(round((now - old_day).seconds/3600, 0))} часов & {int(round((now - old_day).seconds/60, 0))} минут")
    else:
        print("Файл не найден")


# читаем файл
DIR = Path(__file__).resolve().parent  # путь до текущей папки
# print(DIR)
os.chdir(DIR)  # перейти в папку по пути

print('Приложение счетчик дней, которое поможет знать сколько дней прошло с какого-то события')
move = input(
    'Введите действие которое хотите сделать:\n1 - добавить событие\n2 - обновить событие\n3 - удалить событие\n4 - показать все события\n0 - выйти\n')
while move != '0':
    if move == '1':
        event = input("Какое событие важно для вас?\n")
        create(event)
        show()
    if move == '2':
        event = input('Какое событие хотите обновить?\n')
        show()
        update(event)
        show()
    if move == '3':
        show()
        event = input('Какое событие хотите удалить?\n')
        delete(event)
        show()
    if move == '4':
        show()
    move = input(
        'Введите действие которое хотите сделать:\n1 - добавить событие\n2 - обновить событие\n3 - удалить событие\n4 - показать все события\n0 - выйти\n')

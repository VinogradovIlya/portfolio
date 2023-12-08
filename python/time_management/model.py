from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
import json
import os
from pathlib import Path
from datetime import datetime


# читаем файл
DIR = Path(__file__).resolve().parent  # путь до текущей папки
# print(DIR)
os.chdir(DIR)  # перейти в папку по пути


class Model():
    def showDate(self, date):
        self.lbl.setText(date.toString())

    def save(self):
        """ метод записи в json файл """
        # создаем словарь
        self.data = {}
        # добавляем ключ и словарь в значение
        self.data['work'] = {}
        # обработка исключений
        try:
            # открытие файла в режиме чтения
            with open('my work time.json', 'r') as file:
                # загрузка файла в список
                self.data = json.load(file)
        except FileNotFoundError:
            pass
        self.data['work'][datetime.today()] = self.my_time.value()
        with open(DIR / 'my work time.json', 'w') as file:
            json.dump(self.data, file)

    def done(self):
        """ Всплывающее окошко о выполнении """
        self.done_win = QMessageBox()
        self.done_win.setText('Выполнено')
        self.done_win.exec()

    def final_move(self):
        """ сохранение и оповещение о готовности """
        self.save()
        self.done()
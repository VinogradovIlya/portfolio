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


class Model(QObject):
    date_selected = pyqtSignal(QDate)

    def __init__(self):
        super().__init__()

    def set_selected_date(self, date):
        # Логика обработки выбранной даты

        # Сигнал о выбранной дате
        self.date_selected.emit(date)

    def save(self):
        """ метод записи в json файл """
        # создаем словарь
        data = {}
        # добавляем ключ и словарь в значение
        data['work'] = {}
        # обработка исключений
        try:
            # открытие файла в режиме чтения
            with open('my work time.json', 'r') as file:
                # загрузка файла в список
                data = json.load(file)
        except FileNotFoundError:
            pass
        data['work'][str(datetime.today())] = self.my_time.value()
        with open(DIR / 'my work time.json', 'w') as file:
            json.dump(data, file)

    def done(self):
        """ Всплывающее окошко о выполнении """
        done_win = QMessageBox()
        done_win.setText('Выполнено')
        done_win.exec()

    def final_move(self):
        """ сохранение и оповещение о готовности """
        self.save()
        self.done()

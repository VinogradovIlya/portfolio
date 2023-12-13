from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
from pathlib import Path
from datetime import datetime


# читаем файл

# print(DIR)
# os.chdir(DIR)  # перейти в папку по пути


class Model(QWidget):
    """ Класс для обработки данных """
    date_selected = None

    def __init__(self, view):
        super().__init__()
        self.surname_list = list()
        self.view = view
        self.DIR = Path(__file__).resolve().parent  # путь до текущей папки

    def set_selected_date(self):
        date = self.view.cal.selectedDate()
        date_selected = date.toString("yyyy:MM:dd")

    def set_surname_list(self) -> None:
        self.surname = self.view.surname.text()
        self.surname_list = self.surname.replace(' ', '').split(',')

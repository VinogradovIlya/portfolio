from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
import json
import pprint
import mysql.connector


class Сontroller():
    def __init__(self, model, view) -> None:
        self.calendar_model = model
        self.view = view

    def save(self) -> None:
        """ метод записи в json файл """
        self.calendar_model.take_info()
        # обработка исключений
        try:
            # открытие файла в режиме чтения
            with open(self.calendar_model.DIR / 'my work time.json', 'r', encoding='utf-8') as file:
                # загрузка файла в список
                data = json.load(file)
        except FileNotFoundError:
            data = {}
        if 'work' not in data:
            data['work'] = {}
        data['work'][self.calendar_model.date_selected] = self.calendar_model.surname_list
        with open(self.calendar_model.DIR / 'my work time.json', 'w', encoding='utf-8') as file:
            json.dump(data, file, ensure_ascii=False)

    def pretty_load_file(self) -> None:
        try:
            with open(self.model.DIR / 'my work time.json', "r") as file:
                file_content = file.read()
                # Используем pprint для форматированного вывода содержимого файла
                pretty_content = pprint.pformat(file_content)
                self.view.text_edit.setPlainText(pretty_content)
        except FileNotFoundError:
            self.view.text_edit.setPlainText("File not found.")
        except Exception as e:
            self.view.text_edit.setPlainText(
                "An error occurred while loading the file:\n" + str(e))

    def load_file(self) -> None:
        try:
            with open(self.calendar_model.DIR / 'my work time.json', "r") as file:
                file_content = file.read()
                pretty_content = json.dumps(json.loads(
                    file_content), indent=4, ensure_ascii=False)
                self.view.text_edit.setPlainText(pretty_content)
        except FileNotFoundError:
            self.view.text_edit.setPlainText("File not found.")
        except Exception as e:
            self.view.text_edit.setPlainText(
                "An error occurred while loading the file:\n" + str(e))

    def final_move(self) -> None:
        """ сохранение и оповещение о готовности """
        self.save()
        self.view.done()

    def checkbox_group_state_changed(self, state) -> None:
        """ Нажатие на чекбокс "Группа" """
        if state == 2:
            self.view.type = 2
            self.view.ind.setChecked(False)

    def checkbox_ind_state_changed(self, state) -> None:
        """ Нажатие на чекбокс "Индив" """
        if state == 2:
            self.view.type = 1
            self.view.group.setChecked(False)

    def open_main_win(self) -> None:
        """ Возврат к главному экрану """
        self.view.main_win.setCurrentIndex(0)

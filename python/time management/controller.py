from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
import json
import pprint


class Controller:
    def __init__(self, model, view):
        self.model = model
        self.view = view

    def save(self):
        """ метод записи в json файл """
        self.take_info()
        # обработка исключений
        try:
            # открытие файла в режиме чтения
            with open(self.model.DIR / 'my work time.json', 'r', encoding='utf-8') as file:
                # загрузка файла в список
                data = json.load(file)
        except FileNotFoundError:
            data = {}
        if 'work' not in data:
            data['work'] = {}
        data['work'][self.model.date_selected] = self.model.surname_list
        with open(self.model.DIR / 'my work time.json', 'w', encoding='utf-8') as file:
            json.dump(data, file, ensure_ascii=False)

    # def load_file(self):
    #     try:
    #         with open(self.model.DIR / 'my work time.json', "r") as file:
    #             file_content = file.read()
    #             # Используем pprint для форматированного вывода содержимого файла
    #             pretty_content = pprint.pformat(file_content)

    #             self.view.text_edit.setPlainText(pretty_content)
    #     except FileNotFoundError:
    #         self.view.text_edit.setPlainText("File not found.")
    #     except Exception as e:
    #         self.view.text_edit.setPlainText(
    #             "An error occurred while loading the file:\n" + str(e))

    def load_file(self):
        try:
            with open(self.model.DIR / 'my work time.json', "r") as file:
                file_content = file.read()
                pretty_content = json.dumps(json.loads(
                    file_content), indent=4, ensure_ascii=False)
                self.view.text_edit.setPlainText(pretty_content)
        except FileNotFoundError:
            self.view.text_edit.setPlainText("File not found.")
        except Exception as e:
            self.view.text_edit.setPlainText(
                "An error occurred while loading the file:\n" + str(e))

    def final_move(self):
        """ сохранение и оповещение о готовности """
        self.save()
        self.view.done()

    def take_info(self):
        self.model.set_selected_date()
        self.model.set_surname_list()

    def open_main_win(self):
        self.view.main_win.setCurrentIndex(0)

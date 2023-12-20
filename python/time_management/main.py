from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
from view.view import View_window
from model.model import Model_for_calendar
from model.sql_model import MysqlModel
from controller.controller import Сontroller
from controller.sql_controller import MysqlController


app = QApplication([])
view = View_window()
model = Model_for_calendar(view)
controller = Сontroller(model, view)
sql_model = MysqlModel(view)
sql_controller = MysqlController(view, sql_model)

view.set_controller(controller)
# view.set_model(model)
view.set_sql_controller(sql_controller)


app.exec()

# if __name__ == '__main__':
#     print(sql_model.dates)
#     print(sql_model.hours)
#     print(sql_model.surnames)
#     print(sql_model.types)

""" 
x Добавить доступ к бд
2. Добавить функцию подсчета времени за месяц
x Добавить обработку групп/индив
x Переработать MVC
5. При смене даты очищать поле ввода информации
x Переделать ввод фамилий
x Переделать очистку полей ввода, при смене дня
8. Добавить поля ввода/удалить поля ввода(?)
"""
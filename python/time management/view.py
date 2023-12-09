from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *


class View(QMainWindow):
    """ Класс View, который отвечает только за внешний вид экрана """

    def __init__(self):
        super().__init__()
        # главный экран виджет, для удобного прехода между окнами
        self.main_win = QStackedWidget()
        # сделать main_win главным экраном
        self.setCentralWidget(self.main_win)
        self.main_win_ui()
        self.set_appear()
        self.show()

    def set_appear(self):
        """ метод для формирования окна """
        # создание названия окна
        self.setWindowTitle('My time')
        # цвет заднего фона
        self.setStyleSheet("background-color: rgb(207, 208, 118)")
        # один метод для размеров экрана и появления в координатах
        self.setGeometry(200, 129, 500, 300)

    def main_win_ui(self):
        """ внешний вид окна 
        2 кнопки: добавить/удалить/обновить и посмотреть результат
        """
        btn_add = QPushButton('Добавить часы')
        # переход к новому экрану
        btn_add.clicked.connect(self.add_screen_ui)
        btn_show = QPushButton('Показать отработанные часы')
        btn_show.clicked.connect(self.res_screen_ui)

        # создание лэйаута (направляющей линии, где будут наши виджеты (кнопки, текст и тд))
        layout_widget = QWidget()
        v_layout = QVBoxLayout()
        # добавление виджетов на направляющие линии и расположение
        v_layout.addWidget(
            btn_add, alignment=Qt.AlignmentFlag.AlignCenter)
        v_layout.addWidget(
            btn_show, alignment=Qt.AlignmentFlag.AlignCenter)
        layout_widget.setLayout(v_layout)
        # добавление виджета на экран
        self.main_win.addWidget(layout_widget)

    def add_screen_ui(self):
        """ метод для отображения второго экрана по добавлению времени """
        # выбор дня
        day = QLabel('Выберите день')
        # календарь
        self.cal = QCalendarWidget()
        self.cal.setGridVisible(True)
        self.cal.resize(310, 200)
        # cal.selectionChanged.connect()

        surname_lbl = QLabel(
            'Введите фамилии учеников (время можно указать в скобках) через ","')
        self.surname = QLineEdit()
        self.surname.setFixedWidth(300)
        self.surname.setStyleSheet("border: 1px solid black;")

        # кнопка для сохранения
        btn_save = QPushButton('Сохранить')
        btn_save.clicked.connect(self.controller.final_move)

        # кнопка назад
        btn_back = QPushButton('Назад')
        btn_back.clicked.connect(self.open_main_win)

        # лэйаут для расположения виджетов на экране
        layout_widget = QWidget()
        c_line = QVBoxLayout()
        bottom_h_line = QHBoxLayout()
        bottom_h_line.addWidget(
            btn_back, alignment=Qt.AlignmentFlag.AlignCenter)
        bottom_h_line.addWidget(
            btn_save, alignment=Qt.AlignmentFlag.AlignCenter)

        c_line.addWidget(day, alignment=Qt.AlignmentFlag.AlignCenter)
        c_line.addWidget(self.cal, alignment=Qt.AlignmentFlag.AlignCenter)
        c_line.addWidget(
            surname_lbl, alignment=Qt.AlignmentFlag.AlignCenter)
        c_line.addWidget(
            self.surname, alignment=Qt.AlignmentFlag.AlignCenter)
        c_line.addLayout(bottom_h_line)
        layout_widget.setLayout(c_line)
        self.main_win.addWidget(layout_widget)
        self.main_win.setCurrentWidget(layout_widget)

    def res_screen_ui(self):
        # реализовать выбор месяца
        res_lbl = QLabel('Уроки за месяц:')
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(True)
        self.controller.load_file()
        btn_back = QPushButton('Назад')
        btn_back.clicked.connect(self.open_main_win)

        layout_widget = QWidget()
        c_line = QVBoxLayout()
        c_line.addWidget(res_lbl, alignment=Qt.AlignmentFlag.AlignCenter)
        c_line.addWidget(
            self.text_edit, alignment=Qt.AlignmentFlag.AlignCenter)
        c_line.addWidget(btn_back, alignment=Qt.AlignmentFlag.AlignLeft)
        layout_widget.setLayout(c_line)
        self.main_win.addWidget(layout_widget)
        self.main_win.setCurrentWidget(layout_widget)

    def done(self):
        """ Всплывающее окно о выполнении """
        done_win = QMessageBox()
        done_win.setText('Выполнено')
        done_win.setInformativeText(
            f'Дата: {self.model.date_selected}\nУченики: {", ".join(self.model.surname_list)}')
        done_win.exec()

    def open_main_win(self):
        self.main_win.setCurrentIndex(0)

    def set_controller(self, controller: object):
        self.controller = controller

    def set_model(self, model: object):
        self.model = model

    # Применение стилей к календарю
    calendar_style = """
        QCalendarWidget QAbstractItemView {
            selection-background-color: rgb(207, 208, 118);
        }
        QCalendarWidget QWidget#qt_calendar_navigationbar {
            background-color: rgb(207, 208, 118);
        }
        QCalendarWidget QToolButton {
            padding: 5px;
        }
    """

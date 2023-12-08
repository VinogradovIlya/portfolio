from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
from controller import Controller
from model import Model


class View(QMainWindow):
    """ Класс View, который отвечает только за внешний вид экрана """

    def __init__(self):
        super().__init__()
        self.main_win = QStackedWidget()
        self.setCentralWidget(self.main_win)
        self.set_appear()
        self.main_win_ui()
        self.show()

    def set_appear(self):
        """ метод для формирования окна """
        self.setWindowTitle('My time')
        self.setStyleSheet("background-color: rgb(207, 208, 118)")
        self.setGeometry(200, 129, 500, 300)

    def main_win_ui(self):
        """ внешний вид окна 
        2 кнопки: добавить/удалить/обновить и посмотреть результат
        """
        self.btn_add = QPushButton('Добавить часы')
        self.btn_add.clicked.connect(self.add_screen_ui)
        self.btn_show = QPushButton('Показать отработанные часы')

        self.layout_widget = QWidget()
        self.v_layout = QVBoxLayout()

        self.v_layout.addWidget(
            self.btn_add, alignment=Qt.AlignmentFlag.AlignCenter)
        self.v_layout.addWidget(
            self.btn_show, alignment=Qt.AlignmentFlag.AlignCenter)
        self.layout_widget.setLayout(self.v_layout)

        self.main_win.addWidget(self.layout_widget)

    def add_screen_ui(self):
        """ метод для отображения второго экрана по добавлению времени """
        # # надпись
        # self.input_time = QLabel('Введите время')
        # # поле ввода
        # self.my_time = QSpinBox()
        # # задаю минимальный диапазон
        # self.my_time.setMinimum(0)
        # выбор дня
        self.day = QLabel('Выберите день')

        self.cal = QCalendarWidget()
        self.cal.setGridVisible(True)
        self.cal.resize(310, 200)

        # self.cal.clicked[QDate].connect(self.showDate)
        # выбор дня
        # self.lbl = QLabel()
        # сообщение для наглядности
        # self.result_label = QLabel()
        # self.result_label.setText(
        #     f'вы выбрали {} и {self.my_time.value()} часов')

        self.surname_lbl = QLabel(
            'Введите фамилии учеников (время можно указать в скобках) через ";"')
        self.surname = QLineEdit()

        self.btn_save = QPushButton('Сохранить')
        self.btn_save.clicked.connect(Model.done)

        self.btn_back = QPushButton('Назад')
        self.btn_back.clicked.connect(self.open_main_win)

        self.layout_widget = QWidget()
        self.c_line = QVBoxLayout()
        self.bottom_h_line = QHBoxLayout()

        self.bottom_h_line.addWidget(
            self.btn_back, alignment=Qt.AlignmentFlag.AlignCenter)
        self.bottom_h_line.addWidget(
            self.btn_save, alignment=Qt.AlignmentFlag.AlignCenter)

        # self.c_line.addWidget(
        #     self.input_time, alignment=Qt.AlignmentFlag.AlignCenter)
        # self.c_line.addWidget(
        #     self.my_time, alignment=Qt.AlignmentFlag.AlignCenter)
        self.c_line.addWidget(self.day, alignment=Qt.AlignmentFlag.AlignCenter)
        self.c_line.addWidget(self.cal, alignment=Qt.AlignmentFlag.AlignCenter)
        # self.c_line.addWidget(
        #     self.result_label, alignment=Qt.AlignmentFlag.AlignCenter)
        self.c_line.addWidget(
            self.surname_lbl, alignment=Qt.AlignmentFlag.AlignCenter)
        self.c_line.addWidget(
            self.surname, alignment=Qt.AlignmentFlag.AlignCenter)

        self.c_line.addLayout(self.bottom_h_line)
        self.layout_widget.setLayout(self.c_line)
        self.main_win.addWidget(self.layout_widget)
        self.main_win.setCurrentWidget(self.layout_widget)

    def open_main_win(self):
        self.main_win.setCurrentIndex(0)

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

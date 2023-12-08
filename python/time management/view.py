from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *


class View(QMainWindow):
    """ Класс View, который отвечает только за внешний вид экрана """

    def __init__(self):  # Добавлен параметр контроллера
        super().__init__()
        # главный экран виджет, для удобного прехода между окнами
        self.main_win = QStackedWidget()
        # сделать main_win главным экраном
        self.setCentralWidget(self.main_win)
        self.set_appear()
        self.main_win_ui()
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
        self.btn_add = QPushButton('Добавить часы')
        # переход к новому экрану
        self.btn_add.clicked.connect(self.add_screen_ui)
        self.btn_show = QPushButton('Показать отработанные часы')

        # создание лэйаута (направляющей линии, где будут наши виджеты (кнопки, текст и тд))
        self.layout_widget = QWidget()
        self.v_layout = QVBoxLayout()
        # добавление виджетов на направляющие линии и расположение
        self.v_layout.addWidget(
            self.btn_add, alignment=Qt.AlignmentFlag.AlignCenter)
        self.v_layout.addWidget(
            self.btn_show, alignment=Qt.AlignmentFlag.AlignCenter)
        self.layout_widget.setLayout(self.v_layout)
        # добавление виджета на экран
        self.main_win.addWidget(self.layout_widget)

    def add_screen_ui(self):
        """ метод для отображения второго экрана по добавлению времени """
        # выбор дня
        self.day = QLabel('Выберите день')
        # календарь
        self.cal = QCalendarWidget()
        self.cal.setGridVisible(True)
        self.cal.resize(310, 200)
        self.cal.setSizePolicy(QSizePolicy.Policy.Expanding,
                               QSizePolicy.Policy.Expanding)

        # self.cal.clicked[QDate].connect(Model.showDate)

        self.surname_lbl = QLabel(
            'Введите фамилии учеников (время можно указать в скобках) через ";"')
        self.surname = QLineEdit()
        self.surname.setFixedWidth(300)
        self.surname.setStyleSheet("background-color: rgb(255, 255, 255)")

        # кнопка для сохранения
        self.btn_save = QPushButton('Сохранить')
        # кнопка назад
        self.btn_back = QPushButton('Назад')
        self.btn_back.clicked.connect(self.open_main_win)

        # лэйаут для расположения виджетов на экране
        self.layout_widget = QWidget()
        self.c_line = QVBoxLayout()
        self.bottom_h_line = QHBoxLayout()
        self.bottom_h_line.addWidget(
            self.btn_back, alignment=Qt.AlignmentFlag.AlignCenter)
        self.bottom_h_line.addWidget(
            self.btn_save, alignment=Qt.AlignmentFlag.AlignCenter)

        self.c_line.addWidget(self.day, alignment=Qt.AlignmentFlag.AlignCenter)
        self.c_line.addWidget(self.cal, alignment=Qt.AlignmentFlag.AlignCenter)
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

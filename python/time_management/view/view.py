from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtGui import QFocusEvent
from PyQt6.QtWidgets import *


class View_window(QMainWindow):
    """ Класс View, который отвечает только за внешний вид экрана """

    def __init__(self) -> None:
        super().__init__()
        self.main_win = QStackedWidget()
        self.setCentralWidget(self.main_win)
        self.main_win_ui()
        self.set_appear()
        self.show()

    def set_appear(self) -> None:
        """ метод для формирования окна """
        self.setWindowTitle('My time')
        self.setStyleSheet("background-color: rgb(207, 208, 118)")
        self.setGeometry(200, 129, 500, 300)

    def main_win_ui(self) -> None:
        """ внешний вид окна 
        2 кнопки: добавить/удалить/обновить и посмотреть результат
        """
        btn_add = QPushButton('Добавить часы')
        btn_add.clicked.connect(self.add_screen_ui)
        btn_show = QPushButton('Показать отработанные часы')
        btn_show.clicked.connect(self.res_screen_ui)

        layout_widget = QWidget()
        v_layout = QVBoxLayout()

        v_layout.addWidget(
            btn_add, alignment=Qt.AlignmentFlag.AlignCenter)
        v_layout.addWidget(
            btn_show, alignment=Qt.AlignmentFlag.AlignCenter)
        v_layout.setStretchFactor(btn_add, 2)
        v_layout.setStretchFactor(btn_show, 2)
        layout_widget.setLayout(v_layout)
        self.main_win.addWidget(layout_widget)

    def add_screen_ui(self) -> None:
        """ метод для отображения второго экрана по добавлению времени """
        self.cal = QCalendarWidget()
        self.cal.setGridVisible(True)
        self.cal.resize(310, 200)
        # self.cal.selectionChanged.connect(self.cal_model.new_string)

        btn_add = QPushButton('Добавить')
        btn_add.clicked.connect(self.sql_controller.add_info)

        btn_save = QPushButton('Сохранить')
        btn_save.clicked.connect(self.sql_controller.final_move)

        btn_back = QPushButton('Назад')
        btn_back.clicked.connect(self.controller.open_main_win)

        layout_widget = QWidget()
        self.c_line = QVBoxLayout()
        bottom_h_line = QHBoxLayout()
        bottom_h_line.addWidget(
            btn_back, alignment=Qt.AlignmentFlag.AlignCenter)
        bottom_h_line.addWidget(
            btn_save, alignment=Qt.AlignmentFlag.AlignCenter)

        self.c_line.addWidget(self.cal, alignment=Qt.AlignmentFlag.AlignCenter)
        self.new_line()
        stratch_line = QHBoxLayout()
        stratch_line.addStretch(1)
        stratch_line.addWidget(btn_add, 2)
        stratch_line.addStretch(1)
        self.c_line.addLayout(bottom_h_line)
        self.c_line.addLayout(stratch_line)
        layout_widget.setLayout(self.c_line)
        self.main_win.addWidget(layout_widget)
        self.main_win.setCurrentWidget(layout_widget)

    def res_screen_ui(self) -> None:
        # реализовать выбор месяца
        res_lbl = QLabel('Уроки за месяц:')
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(True)
        # self.controller.load_file()
        self.sql_controller.output()

        btn_back = QPushButton('Назад')
        btn_back.clicked.connect(self.controller.open_main_win)

        layout_widget = QWidget()
        c_line = QVBoxLayout()
        c_line.addWidget(res_lbl, alignment=Qt.AlignmentFlag.AlignCenter)
        c_line.addWidget(
            self.text_edit, alignment=Qt.AlignmentFlag.AlignCenter)
        c_line.addWidget(btn_back, alignment=Qt.AlignmentFlag.AlignLeft)
        layout_widget.setLayout(c_line)
        self.main_win.addWidget(layout_widget)
        self.main_win.setCurrentWidget(layout_widget)

    def done(self) -> None:
        """ Всплывающее окно о выполнении """
        done_win = QMessageBox()
        done_win.setText('Выполнено')
        # done_win.setInformativeText(
        #     f'Дата: {self.cal_model.date_selected}\nУченики: {", ".join(self.cal_model.surname_list)}')
        done_win.exec()
        self.add_screen_ui()

    def new_line(self) -> None:
        """ Метод для добавления фамилий и времени """
        self.surname = QLineEdit('Фамилия')
        self.surname.setStyleSheet("border: 1px solid black;")
        self.surname.focusInEvent = lambda event: self.surname.clear()

        self.time = QLineEdit('Время')
        self.time.setStyleSheet("border: 1px solid black;")
        self.time.focusInEvent = lambda event: self.time.clear()

        self.group = QCheckBox('Группа')
        self.group.stateChanged.connect(
            self.controller.checkbox_group_state_changed)
        self.ind = QCheckBox('Индив')
        self.ind.setChecked(True)
        self.type = 1
        self.ind.stateChanged.connect(
            self.controller.checkbox_ind_state_changed)

        info_line = QHBoxLayout()
        info_line.addWidget(self.surname)
        info_line.addWidget(self.time)
        info_line.addWidget(self.group)
        info_line.addWidget(self.ind)
        self.c_line.addLayout(info_line)

    def set_controller(self, controller: object) -> None:
        self.controller = controller

    # def set_model(self, model: object) -> None:
    #     self.cal_model = model

    def set_sql_controller(self, sql_controller) -> None:
        self.sql_controller = sql_controller

    def set_sql_model(self, sql_model) -> None:
        self.sql_model = sql_model

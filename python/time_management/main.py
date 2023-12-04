from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *


class MainWin(QWidget):
    def __init__(self):
        super().__init__()
        self.set_appear()
        self.initUI()
        self.show()

    def set_appear(self):
        self.setWindowTitle('My time')
        self.resize(500, 300)
        self.setStyleSheet("background-color: rgb(207, 208, 118)")
        self.move(200, 100)

    def initUI(self):
        # сделать 4 кнопки: добавить/удалить/обновить/получить(посмотреть результат)
        # вопрос для подсчета времени за день
        self.question1 = QLabel("Сколько ты отработал сегодня?")
        self.answer1 = QLineEdit()
        self.btn = QPushButton('Записать')

        self.v_layout = QVBoxLayout()
        self.v_layout.addWidget(
            self.question1, alignment=Qt.AlignmentFlag.AlignCenter)
        self.v_layout.addWidget(
            self.answer1, alignment=Qt.AlignmentFlag.AlignCenter)
        self.v_layout.addWidget(
            self.btn, alignment=Qt.AlignmentFlag.AlignCenter)
        self.setLayout(self.v_layout)


app = QApplication([])
mw = MainWin()
app.exec()

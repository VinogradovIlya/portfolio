from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
import view


class Controller:
    def __init__(self, view):
        self.view = view

    def open_add_screen(self):
        self.view.main_win.setCurrentWidget(self.view.layout_widget)

    def open_main_screen(self):
        self.view.main_win.setCurrentWidget(self.view.main_win)

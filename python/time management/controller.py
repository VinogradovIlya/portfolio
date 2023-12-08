from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *


class Controller:
    def __init__(self, model, view):
        self.model = model
        self.view = view

        self.view.handle_date_selection.connect(self.model.set_selected_date)
        self.model.date_selected.connect(self.view.show_selected_date)

    def open_add_screen(self):
        self.view.main_win.setCurrentWidget(self.view.layout_widget)

    def open_main_screen(self):
        self.view.main_win.setCurrentWidget(self.view.main_win)

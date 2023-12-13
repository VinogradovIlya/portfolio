from PyQt6.QtGui import *
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
from view import View
from model import Model
from controller import Controller


app = QApplication([])
# view принимает контроллер, model ничего, controller model
view = View()
model = Model(view)
controller = Controller(model, view)

view.set_controller(controller)
view.set_model(model)

app.exec()

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import *


app = QApplication([])
main_win = QWidget()

main_h_layout = QHBoxLayout()
add_left_layout = QVBoxLayout()
add_right_layout = QVBoxLayout()

main_h_layout.addLayout(add_left_layout)
main_h_layout.addLayout(add_right_layout)
main_win.setLayout(main_h_layout)

field_note = QTextEdit()
field_note.setText('Введите текст заметки')
# удаление текста при нажатии ! (подумать)
add_left_layout.addWidget(field_note)

label_notes = QLabel('Список заметок')
list_notes = QListWidget()
add_h1_line = QHBoxLayout()
button_create_notes = QPushButton('Создать заметку')
button_remove_notes = QPushButton('Удалить заметку')
add_h1_line.addWidget(button_create_notes)
add_h1_line.addWidget(button_remove_notes)
button_save_notes = QPushButton('Сохранить заметку')

add_right_layout.addWidget(label_notes)
add_right_layout.addWidget(list_notes)
add_right_layout.addLayout(add_h1_line)
add_right_layout.addWidget(button_save_notes)

label_tags = QLabel('Список тегов')
list_tags = QListWidget()
add_h2_line = QHBoxLayout()
button_create_tags = QPushButton('Создать заметку')
button_remove_tags = QPushButton('Удалить заметку')
add_h2_line.addWidget(button_create_tags)
add_h2_line.addWidget(button_remove_tags)
button_save_tags = QPushButton('Сохранить заметку')

add_right_layout.addWidget(label_tags)
add_right_layout.addWidget(list_tags)
add_right_layout.addLayout(add_h2_line)
add_right_layout.addWidget(button_save_tags)

main_win.show()
app.exec()

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import *
import json
import os
from pathlib import Path

# читаем файл
DIR = Path(__file__).resolve().parent  # путь до текущей папки
# print(DIR)
os.chdir(DIR)  # перейти в папку по пути


app = QApplication([])
main_win = QWidget()


def show_note() -> None:
    key = list_notes.selectedItems()[0].text()
    field_note.setText(notes[key]['text'])
    list_tags.clear()
    list_tags.addItems(notes[key]['tags'])


def add_note():
    note_name, ok = QInputDialog().getText(
        main_win, 'Добавить заметку', 'Название заметки')
    if ok and note_name != '':
        notes[note_name] = {'text': '', 'tags': []}
        list_notes.addItem(note_name)
        list_tags.addItems(notes[note_name]['tags'])


def del_note():
    if list_notes.selectedItems():
        key = list_notes.selectedItems()[0].text()
        del notes[key]
        list_notes.clear()
        list_tags.clear()
        field_note.clear()
        list_notes.addItems(notes)
        with open('notes_data.json', 'w') as file:
            json.dump(notes, file, sort_keys=True,
                      ensure_ascii=False, indent=4)
        done()
    else:
        warning = QMessageBox()
        warning.setText('Выберите заметку для удаления')
        warning.exec()


def save_note():
    if list_notes.selectedItems():
        key = list_notes.selectedItems()[0].text()
        notes[key]['text'] = field_note.toPlainText()
        with open('notes_data.json', 'w') as file:
            json.dump(notes, file, sort_keys=True,
                      ensure_ascii=False, indent=4)
        done()
    else:
        warning = QMessageBox()
        warning.setText('Выберите заметку для сохранения')
        warning.exec()


def done():
    done = QMessageBox()
    done.setText('Выполнено')
    done.exec()


main_h_layout = QHBoxLayout()
add_left_layout = QVBoxLayout()
add_right_layout = QVBoxLayout()

main_h_layout.addLayout(add_left_layout)
main_h_layout.addLayout(add_right_layout)
main_win.setLayout(main_h_layout)

field_note = QTextEdit()
add_left_layout.addWidget(field_note)

label_notes = QLabel('Список заметок')
list_notes = QListWidget()
add_h1_line = QHBoxLayout()

button_create_notes = QPushButton('Создать заметку')
button_create_notes.clicked.connect(add_note)
button_remove_notes = QPushButton('Удалить заметку')
button_remove_notes.clicked.connect(del_note)
button_save_notes = QPushButton('Сохранить заметку')
button_save_notes.clicked.connect(save_note)

add_h1_line.addWidget(button_create_notes)
add_h1_line.addWidget(button_remove_notes)

add_right_layout.addWidget(label_notes)
add_right_layout.addWidget(list_notes)
add_right_layout.addLayout(add_h1_line)
add_right_layout.addWidget(button_save_notes)

label_tags = QLabel('Список тегов')
list_tags = QListWidget()
add_h2_line = QHBoxLayout()
button_create_tags = QPushButton('Добавить к заметке')
button_remove_tags = QPushButton('Открепить от заметки')
tag_line = QLineEdit()
tag_line.setPlaceholderText('Введите тег')
add_h2_line.addWidget(button_create_tags)
add_h2_line.addWidget(button_remove_tags)
button_save_tags = QPushButton('Искать заметки по тегу')

add_right_layout.addWidget(label_tags)
add_right_layout.addWidget(list_tags)
add_right_layout.addWidget(tag_line)
add_right_layout.addLayout(add_h2_line)
add_right_layout.addWidget(button_save_tags)

list_notes.itemClicked.connect(show_note)

try:
    with open("notes_data.json", "r", encoding='utf-8') as file:
        notes = json.load(file)
    list_notes.addItems(notes)
except FileNotFoundError:
    notes = {
        'Добро пожаловать': {
            'text': 'Вводная инструкция',
            'tags': ['Умные заметки', 'Инструкция']
        }
    }
    with open(DIR/'notes_data.json', 'w', encoding='utf-8') as file:
        json.dump(notes, file, sort_keys=True, ensure_ascii=False, indent=4)
    list_notes.addItems(notes)


main_win.show()
app.exec()

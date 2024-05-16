from datetime import datetime
from pywebio.input import input, input_group, textarea, TEXT
from pywebio.output import put_table, put_text


class Note:
    def __init__(self) -> None:
        self.note = input_group("Введите данные для заметки: название и текст",
                                [input('Заголовок заметки: ',
                                       type=TEXT, validate=self.is_empty, name='name'),
                                 textarea('Текст заметки: ', validate=self.is_empty, name='text')])
        self.date()
        self.done()

    def date(self):
        self.date_note = datetime.now().strftime("%x %X")

    def done(self):
        put_text('Заметка создана')
        put_text('Смотри ее в общем списке заметок ниже')

    def is_empty(self, text):
        if not text:
            return 'Нельзя оставлять поле пустым'

    @staticmethod
    def not_done():
        put_text("Записи с таким номером нет")

    @staticmethod
    def del_note():
        return input('Введите номер заметки для удаления: ',
                     type=TEXT)

    @staticmethod
    def print_note(*args):
        put_table([
            ['Номер заметки', 'Имя заметки',
                'Текст заметки', 'Дата создания заметки'],
            *args
        ])


if __name__ == '__main__':
    note = Note()
    Note.print_note(*note)

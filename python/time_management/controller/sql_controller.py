from mysql.connector import connect, Error
from getpass import getpass


class MysqlController():
    """Класс для работы с бд"""

    def __init__(self, view, model) -> None:
        self.view = view
        self.sql_model = model

    def print_type_lesson(self) -> None:
        try:
            data = None
            with connect(
                host='localhost',
                user='root',
                password='YAtvoishprotedal1',
                database='my_lessons'
            ) as connection:
                with connection.cursor() as cursor:
                    cursor.execute("SELECT * FROM type_lesson")
                    data = cursor.fetchall()
                    self.view.text_edit.setPlainText(
                        ' '.join(str(item) for item in data))
        except Error as e:
            print(e)

    def add_lesson(self) -> None:
        self.sql_model.take_info()
        try:
            with connect(
                host='localhost',
                user='root',
                password='YAtvoishprotedal1',
                database='my_lessons'
            ) as connection:
                with connection.cursor() as cursor:
                    data = tuple(zip(self.sql_model.types, self.sql_model.surnames, self.sql_model.hours,
                                     self.sql_model.dates))
                    # data = ', '.join(map(str, data))
                    cursor.executemany("""
                                   INSERT INTO my_lessons.lesson (type_lesson, surname, time, date)
                                   VALUES ( %s, %s, %s, %s)""", data)
                    connection.commit()
        except Error as e:
            print(e)
        
    def output(self) -> None:
        try:
            with connect(
                host='localhost',
                user='root',
                password='YAtvoishprotedal1',
                database='my_lessons'
            ) as connection:
                with connection.cursor() as cursor:
                    cursor.execute(""" SELECT * FROM my_lessons.lesson """)
                    data = cursor.fetchall()
                    self.view.text_edit.setPlainText(', '.join(map(str, data)))
        except Error as e:
            print(e)

    def add_info(self) -> None:
        """ Метод для приема данных и добавления новой строки """
        self.sql_model.take_info()
        self.view.new_line()

    def final_move(self) -> None:
        """ Метод для сохранения данных и оповещения """
        self.add_lesson()
        self.view.done()

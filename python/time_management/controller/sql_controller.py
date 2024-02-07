from mysql.connector import connect, Error
from getpass import getpass


class MysqlController():
    """Класс для работы с бд"""

    def __init__(self, view, model) -> None:
        self.view = view
        self.sql_model = model

    def add_lesson(self) -> None:
        """ Метод для добавления уроков """
        self.sql_model.take_info()
        try:
            with connect(
                host='localhost',
                user=input('Имя: '),
                password=getpass('Пароль: '),
                database='my_lessons'
            ) as connection:
                with connection.cursor() as cursor:
                    data = tuple(zip(self.sql_model.types, self.sql_model.surnames, self.sql_model.hours,
                                     self.sql_model.dates))
                    cursor.executemany("""
                                   INSERT INTO my_lessons.lesson (type_lesson, surname, time, date)
                                   VALUES ( %s, %s, %s, %s)""", data)
                    connection.commit()
        except Error as e:
            print(e)
        
    def output(self) -> None:
        """ Метод для вывода уроков """
        try:
            with connect(
                host='localhost',
                user=input('Имя: '),
                password=getpass('Пароль: '),
                database='my_lessons'
            ) as connection:
                with connection.cursor() as cursor:
                    cursor.execute(""" SELECT COUNT(*) FROM my_lessons.lesson """)
                    data = cursor.fetchall()
                    self.view.text_edit.setPlainText(str(data[0][0]))
                    cursor.execute(""" SELECT surname, time FROM my_lessons.lesson """)
                    data = cursor.fetchall()
                    self.view.text_edit.append('\n'.join(map(str, data)))
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

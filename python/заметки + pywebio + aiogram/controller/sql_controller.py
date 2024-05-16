import sqlite3


class DB:
    def __init__(self, name):
        self.name = name
        self.connection = None
        self.cursor = None

    def __enter__(self):
        self.connection = sqlite3.connect(self.name)
        self.cursor = self.connection.cursor()
        return self.cursor

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.connection.commit()
        self.connection.close()
        self.cursor = self.connection = None

    def add(self, model):
        self.cursor.executemany("""
        insert into notes(title, text, date)
        values (?, ?, ?)
        """, model)

    def output(self):
        self.cursor.execute(""" select * from notes order by id desc""")
        return self.cursor.fetchall()

    def delete(self, number):
        self.cursor.executemany(""" DELETE FROM notes WHERE id = ? """, (number,))

if __name__ == '__main__':
    db = DB('notes.db')
    with db as cur:
        cur.execute("""create table if not exists notes(
                    id INTEGER PRIMARY KEY,
                    title VARCHAR,
                    text VARCHAR,
                    date DATETIME);""")
        db.add([('title1', 'text1', '05/16/24 02:15:12')])

class Model:
    def __init__(self, note):
        self.note = note

    def __str__(self) -> str:
        return f'title = {self.note.note['name']}, text = {self.note.note['text']}, data = {self.note.date_note}'

    def info_note(self):
        self.name = self.note.note['name']
        self.text = self.note.note['text']
        self.data = self.note.date_note
        return [(self.name, self.text, self.data)]
    
    @staticmethod
    def del_note(cls):
        return cls.del_note()


if __name__ == '__main__':
    print()

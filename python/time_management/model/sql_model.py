class MysqlModel():
    def __init__(self, view) -> None:
        self.view = view
        self.surnames = list()
        self.hours = list()
        self.types = list()
        self.dates = list()

    def set_selected_date(self) -> str:
        """ Метод для получения дат из календаря """
        date = self.view.cal.selectedDate()
        return date.toString("yyyy:MM:dd")
    
    def take_info(self) -> None:
        """ Метод для получения данных """
        self.surnames.append(self.view.surname.text())
        self.hours.append(self.view.time.text())
        self.types.append(self.view.type)
        self.dates.append(self.set_selected_date())

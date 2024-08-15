from decimal import Decimal
from typing import Any


class Atm:
    __slots__ = ('_rub', '_count')

    def __init__(self, rub: int | float = 0) -> None:
        """ Метод инициализации экземпляра """
        self._rub = Decimal(rub)
        self._count = 0

    def add_rub(self, money: Decimal) -> None:
        """ Метод для работы с начислением рублей экземпляра """
        if money > 0 and self.check50(money):
            self += money
        else:
            raise ValueError('Некорректное значение')

    def take_rub(self, money: Decimal) -> None:
        """ Метод для работы со списанием рублей экземпляра """
        if money > self._rub:
            raise ValueError('Сумма больше, чем денег на счете')
        elif money <= 0:
            raise ValueError('Некорректное значение')
        percent = money * Decimal(1.015)
        if not 30 < percent < 600:
            if percent < 30:
                percent = 30
            elif percent > 600:
                percent = 600
        self -= percent

    def count(self) -> None:
        """ Метод для проверки количества операций"""
        self._count += 1
        if not self._count % 3:
            self *= Decimal(0.97)

    def check50(self, money: Decimal) -> None:
        """ Метод для проверки кратности 50 """
        if money % 50:
            raise ValueError('Значение должно быть кратным 50')
        return not money % 50

    def check_wealth(self):
        """ Метод для списания налога на богатство """
        if self._rub > 5_000_000:
            self._rub *= Decimal(0.9)

    def __str__(self) -> str:
        """ Метод для строчного представления экземпляра """
        return f'rub = {self._rub:0.2f}'

    def __repr__(self) -> str:
        """ Метод для представления экземпляра для программиста"""
        return f'Atm({self._rub})'

    def __iadd__(self, money: Decimal) -> Any:
        """ Метод для сложения экземпляра и числа \n(вспомогательный метод для вычисления рублей) """
        self._rub = self._rub + money
        return Atm(self._rub)

    def __isub__(self, money: Decimal):
        """ Метод для вычитания экземпляра и числа \n(вспомогательный метод для вычисления рублей) """
        self._rub = self._rub - money
        return Atm(self._rub)

    def __imul__(self, money: Decimal):
        """ Метод для вычитания экземпляра и числа \n(вспомогательный метод для вычисления рублей) """
        self._rub = self._rub * money
        return Atm(self._rub)

    def __setattr__(self, name, value) -> None:
        """ Метод для попытки присвоения значения атрибуту экземпляра """
        if not name in ('_rub', '_count'):
            raise AttributeError(
                'Error 2: Ведутся технические работы, пока что возможна только работа в рублях')
        return object.__setattr__(self, name, value)

    def __getattr__(self, item) -> None:
        """ Метод для попытки присвоения значения несуществующему атрибуту экземпляра """
        return None

    def __delattr__(self, item):
        if item in self.__slots__:
            setattr(self, item, 0)
        else:
            object.__delattr__(self, item)


if __name__ == '__main__':
    # help(Atm)
    atm = Atm()
    print(atm)

    atm.add_rub(50)
    print(atm)

    # atm._usd = 100  # AttributeError: Error 2: Ведутся технические работы, пока что возможна только работа в рублях
    print(atm._usd)  # None

    atm._rub = 100
    print(atm)

    print(atm.check50(100))

    del atm._rub
    print(atm)

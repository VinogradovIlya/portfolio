from decimal import Decimal
from typing import Any


class Atm:
    def __init__(self, rub: int | float = 0) -> None:
        """ Метод инициализации экземпляра """
        self._rub = Decimal(rub)
        self._count = 0

    def add_rub(self, money: int | float) -> None:
        """ Метод для работы с начислением рублей экземпляра """
        money = Decimal(money)
        if money > 0:
            self += money
        else:
            raise ValueError('Некорректное значение')

    def take_rub(self, money: int | float | Decimal = 0) -> None:
        """ Метод для работы со списанием рублей экземпляра """
        if money > self._rub:
            raise ValueError('Сумма больше, чем денег на счете')
        percent = money * 1.015
        if not 30 < percent < 600:
            if percent < 30:
                percent = 30
            elif percent > 600:
                percent = 600
        self -= percent  # доделать in place вычитание

    def check50(self, money: int | float | Decimal = 0) -> None:
        """ Метод для проверки кратности 50 """
        money = Decimal(money)
        if money % 50:
            raise ValueError('Значение должно быть кратным 50')
        return not money % 50

    def check_wealth(self):
        """ Метод для списания налога на богатство """
        if self._rub > 5_000_000:
            self._rub *= 0.9

    def __str__(self) -> str:
        """ Метод для строчного представления экземпляра """
        return f'rub = {self._rub}'

    def __repr__(self) -> str:
        """ Метод для представления экземпляра для программиста"""
        return f'Atm({self._rub})'

    def __iadd__(self, money: int | float | Decimal) -> Any:
        """ Метод для сложения экземпляра и числа \n(вспомогательный метод для начисления рублей) """
        self._rub = self._rub + money
        return Atm(self._rub)

    # def __getattribute__(self, currency: str) -> Any:
    #     """ Метод для работы с попыткой обращения к атрибутам экземпляра """
    #     if not currency in ('_rub', '_count'):
    #         raise AttributeError(
    #             'Error 1: Ведутся технические работы, пока что возможна только работа в рублях')
    #     return object.__getattribute__(self, currency)

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
        if item in ('_rub', '_count'):
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

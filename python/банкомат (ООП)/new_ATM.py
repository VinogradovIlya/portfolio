from decimal import Decimal
from typing import Any


class Atm:
    def __init__(self, rub: int | float | Decimal = 0) -> None:
        """ Метод инициализации экземпляра """
        self._rub = rub

    def add_rub(self, money: int | float | Decimal = 0) -> None:
        """ Метод для работы с начислением рублей экземпляра """
        self._rub += money

    def take_rub(self, money: int | float | Decimal = 0) -> None:
        """ Метод для работы со списанием рублей экземпляра """
        self._rub -= money

    def __str__(self) -> str:
        """ Метод для строчного представления экземпляра """
        return f'rub = {self._rub}'

    def __repr__(self) -> str:
        """ Метод для представления экземпляра для программиста"""
        return f'Atm({self._rub})'

    def __iadd__(self, money: int | float | Decimal = 0) -> Any:
        """ Метод для сложения экземпляра и числа \n(вспомогательный метод для начисления рублей) """
        self._rub = self._rub + money
        return Atm(self._rub)

    def __getattr__(self, item) -> None:
        """ Метод для попытки присвоения значения несуществующему атрибуту экземпляра """
        return None

    def __getattribute__(self, currency: str) -> Any:
        """ Метод для работы с попыткой обращения к атрибутам экземпляра """
        if currency != '_rub':
            raise AttributeError(
            'Ведутся технические работы, пока что возможна только работа в рублях')
        return object.__getattribute__(self, currency)

    def __setattr__(self, name, value) -> None:
        """ Метод для попытки присвоения значения атрибуту экземпляра """
        if name != '_rub':
            raise AttributeError(
                'Ведутся технические работы, пока что возможна только работа в рублях')
        return object.__setattr__(self, name, value)

    def __delattr__(self, item):
        if item in ('_rub'):
            setattr(self, item, 0)
        else:
            object.__delattr__(self, item)


if __name__ == '__main__':
    help(Atm)
    atm = Atm()
    print(atm)

    atm += 50
    print(atm)

    # atm._usd = 100  # AttributeError: Ведутся технические работы, пока что возможна только работа в рублях
    print(atm._usd)  # None

    atm._rub = 100
    print(atm)

    del atm._rub
    print(atm)

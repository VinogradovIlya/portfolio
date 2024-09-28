from typing import Any


class DataBases:
    """ Метод для работы с базами данных """
    def __init__(self) -> None:
        ...

    def __call__(self, *args: Any, **kwds: Any) -> Any:
        """ Метод для выполнения запросов """
        pass

    def __iter__(self):
        """ Метод для иттерирования по истории запросов """
        return self

    def __next__(self):
        """ Метод для иттерирования по истории запросов """
        pass

    def __str__(self) -> str:
        """ Метод для строкового представления для пользователя """
        pass

    def __repr__(self) -> str:
        """ Метод для строкового представления для разработчика"""
        pass

    def __enter__(self):
        """ Метод для работы с менеджером контекста with """
        ...

    def exit(self):
        """ Метод для работы с менеджером контекста with """
        ...


if __name__ == '__main__':
    db = DataBases()
    with db:
        pass
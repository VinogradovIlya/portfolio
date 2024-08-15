from new_ATM import Atm
from decimal import Decimal


atm = Atm()
while move := input('Введите действие:\n1 - пополнить\n2 - снять\n3 - выйти\n'):
    if move == '1':
        money = Decimal(input('Введите сумму для пополнения: '))
        atm.add_rub(money)
    elif move == '2':
        money = Decimal(input('Введите сумму для снятия: '))
        atm.take_rub(money)
    elif move == '3':
        break
    atm.check_wealth()
    atm.count()
    print(atm)
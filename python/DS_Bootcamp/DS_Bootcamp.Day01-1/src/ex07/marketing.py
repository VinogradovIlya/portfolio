import sys


def input_data():
    ''' Первый список — учетные записи электронной почты ваших клиентов.
    Второй список содержит учетные записи электронной почты участников вашего последнего мероприятия
    (некоторые из них были вашими клиентами).
    Третий список содержит учетные записи ваших клиентов,
    которые просмотрели ваше последнее рекламное письмо. '''
    clients = ['andrew@gmail.com', 'jessica@gmail.com', 'ted@mosby.com',
               'john@snow.is', 'bill_gates@live.com', 'mark@facebook.com',
               'elon@paypal.com', 'jessica@gmail.com']
    participants = ['walter@heisenberg.com', 'vasily@mail.ru',
                    'pinkman@yo.org', 'jessica@gmail.com', 'elon@paypal.com',
                    'pinkman@yo.org', 'mr@robot.gov', 'eleven@yahoo.com']
    recipients = ['andrew@gmail.com', 'jessica@gmail.com', 'john@snow.is']
    return clients, participants, recipients


def call_center():
    clients, _, recipients = input_data()
    client = set(clients)
    recipient = set(recipients)
    client -= recipient
    return list(client)


def potential_clients():
    clients, participants, _ = input_data()
    client = set(clients)
    participant = set(participants)
    participant -= client
    return list(participant)


def loyalty_program():
    clients, participants, _ = input_data()
    client = set(clients)
    participants = set(participants)
    client -= participants
    return list(client)


if __name__ == '__main__':
    if len(sys.argv) == 2:
        if sys.argv[1] == 'call_center':
            print(call_center())
        elif sys.argv[1] == 'potential_clients':
            print(potential_clients())
        elif sys.argv[1] == 'loyalty_program':
            print(loyalty_program())
        else:
            raise ValueError('Invalid argument')

import sys


def search(name_company: str):
    COMPANIES = {
        'Apple': 'AAPL',
        'Microsoft': 'MSFT',
        'Netflix': 'NFLX',
        'Tesla': 'TSLA',
        'Nokia': 'NOK'
    }

    STOCKS = {
        'AAPL': 287.73,
        'MSFT': 173.79,
        'NFLX': 416.90,
        'TSLA': 724.88,
        'NOK': 3.37
    }
    name_company = name_company.split(',')
    name_company = list(map(lambda x: x.strip(), name_company))
    if '' in name_company:
        name_company.remove('')
    if len(name_company) == 3:
        for i in name_company:
            if i in STOCKS:
                for name, abrv in COMPANIES.items():
                    if abrv == i:
                        print(f'{i} is a ticker symbol for {name}')
                continue
            i = i.title()
            if i in COMPANIES:
                print(f'{i} stock price is {STOCKS[COMPANIES[i]]}')
                continue
            if i not in STOCKS and i not in COMPANIES:
                print(f'{i} is an unknown company or an unknown ticker symbol')


if __name__ == '__main__':
    if len(sys.argv) == 2:
        search(sys.argv[1])

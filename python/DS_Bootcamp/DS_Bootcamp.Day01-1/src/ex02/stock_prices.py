import sys


def search(name_company: str):
    name_company = name_company.title()
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

    if name_company not in COMPANIES:
        return 'Unknown company'
    else:
        return STOCKS[COMPANIES[name_company]]


if __name__ == '__main__':
    if len(sys.argv) == 2:
        print(search(sys.argv[1]))

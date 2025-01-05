import sys


def search(name_company: str):
    name_company = name_company.upper()
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

    if name_company not in COMPANIES.values() and name_company not in STOCKS.keys():
        return 'Unknown company'
    else:
        for key, value in COMPANIES.items():
            if value == name_company:
                return ' '.join(map(str, (key, STOCKS[name_company])))


if __name__ == '__main__':
    if len(sys.argv) == 2:
        print(search(sys.argv[1]))

import sys


def search(email: str) -> str:
    with open('employees.tsv', 'r') as f:
        for line in f:
            if email in line:
                return f"Dear {line.split('\t')[0]}, welcome to our team. We are sure that it will be a pleasure to \
work with you. That’s a precondition for the professionals that our company hires."


if __name__ == '__main__':
    print(search(sys.argv[1]))

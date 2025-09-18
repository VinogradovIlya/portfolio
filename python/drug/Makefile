# tests:
# 	pytest -v

# env:
# 	cp .env.develop .env


migrate:
	python3 manage.py makemigrations
	python3 manage.py migrate

start:
	python3 manage.py runserver

cov: clean
	coverage run -m pytest
	
report: cov
	coverage report
	coverage html

clean:
	rm -f .coverage
	rm -rf htmlcov .pytest_cache

cp-envs:
	cp .env.development .env
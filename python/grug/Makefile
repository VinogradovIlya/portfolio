# tests:
# 	pytest -v

cov: clean
	coverage run -m pytest
	
report:
	coverage report
	coverage html

clean:
	rm -f .coverage
	rm -rf htmlcov .pytest_cache

cp-envs:
	cp .env.development .env
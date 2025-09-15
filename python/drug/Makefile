# tests:
# 	pytest -v

# env:
# 	cp .env.develop .env

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
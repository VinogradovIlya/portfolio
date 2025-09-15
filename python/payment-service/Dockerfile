FROM python:3.11-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
    gcc \
    sqlite3 \
    && rm -rf /var/lib/apt/lists/*

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

RUN useradd --create-home --shell /bin/bash appuser

RUN chown -R appuser:appuser /app
USER appuser

COPY --chown=appuser:appuser . .

CMD ["uvicorn", "app.main:app", "--host", "0.0.0.0", "--port", "8000"]

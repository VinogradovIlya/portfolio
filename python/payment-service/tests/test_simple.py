import pytest
from fastapi.testclient import TestClient

from app.main import app


@pytest.fixture
def client():
    return TestClient(app)


class TestBasic:
    """Базовые тесты без зависимости от БД"""

    def test_root_endpoint(self, client: TestClient):
        """Тест корневого эндпоинта"""
        response = client.get("/")
        assert response.status_code == 200
        data = response.json()
        assert data["message"] == "Payment Service API"

    def test_health_check(self, client: TestClient):
        """Тест health check"""
        response = client.get("/health")
        assert response.status_code == 200
        data = response.json()
        assert data["status"] == "healthy"

    def test_auth_without_token(self, client: TestClient):
        """Тест запроса без токена"""
        response = client.get("/auth/me")
        assert response.status_code == 403

    def test_payments_without_token(self, client: TestClient):
        """Тест запроса платежей без токена"""
        response = client.get("/payments/")
        assert response.status_code == 403

    def test_invalid_register_data(self, client: TestClient):
        """Тест регистрации с невалидными данными"""
        invalid_data = {
            "email": "not-an-email",
            "username": "ab",
            "password": "123",
        }

        response = client.post("/auth/register", json=invalid_data)
        assert response.status_code == 422

    def test_register_missing_fields(self, client: TestClient):
        """Тест регистрации с отсутствующими полями"""
        incomplete_data = {"email": "test@example.com"}

        response = client.post("/auth/register", json=incomplete_data)
        assert response.status_code == 422

    def test_login_empty_data(self, client: TestClient):
        """Тест входа с пустыми данными"""
        response = client.post("/auth/login", json={})
        assert response.status_code == 422

    def test_invalid_payment_data(self, client: TestClient):
        """Тест создания платежа с невалидными данными"""
        invalid_payment = {
            "amount": -50.00,
            "description": "Invalid payment",
        }

        response = client.post("/payments/", json=invalid_payment)
        assert response.status_code in [403, 422]

    def test_nonexistent_endpoints(self, client: TestClient):
        """Тест несуществующих эндпоинтов"""
        response = client.get("/nonexistent")
        assert response.status_code == 404

        response = client.get("/payments/nonexistent")
        assert response.status_code == 403

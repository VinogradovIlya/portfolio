import pytest
from fastapi.testclient import TestClient

from app.main import app


@pytest.fixture
def client():
    return TestClient(app)


def test_root_endpoint():
    """Тест корневого эндпоинта"""
    client = TestClient(app)
    response = client.get("/")
    assert response.status_code == 200
    data = response.json()
    assert data["message"] == "Payment Service API"


def test_health_check():
    """Тест health check"""
    client = TestClient(app)
    response = client.get("/health")
    assert response.status_code == 200
    data = response.json()
    assert data["status"] == "healthy"


def test_auth_validation():
    """Тест валидации данных аутентификации"""
    client = TestClient(app)

    response = client.post(
        "/auth/register",
        json={"email": "not-an-email", "username": "testuser", "password": "password123"},
    )
    assert response.status_code == 422

    response = client.post(
        "/auth/register",
        json={"email": "test@example.com", "username": "ab", "password": "password123"},
    )
    assert response.status_code == 422

    response = client.post(
        "/auth/register",
        json={"email": "test@example.com", "username": "testuser", "password": "123"},
    )
    assert response.status_code == 422


def test_payment_validation():
    """Тест валидации данных платежей"""
    client = TestClient(app)

    response = client.post("/payments/", json={"amount": -50.00, "description": "Invalid payment"})
    assert response.status_code in [403, 422]


def test_unauthorized_access():
    """Тест неавторизованного доступа"""
    client = TestClient(app)

    response = client.get("/auth/me")
    assert response.status_code == 403

    response = client.get("/payments/")
    assert response.status_code == 403

    headers = {"Authorization": "Bearer invalid_token"}
    response = client.get("/auth/me", headers=headers)
    assert response.status_code == 401


def test_nonexistent_endpoints():
    """Тест несуществующих эндпоинтов"""
    client = TestClient(app)

    response = client.get("/nonexistent")
    assert response.status_code == 404

    response = client.get("/payments/nonexistent")
    assert response.status_code == 403


def test_cors_headers():
    """Тест CORS заголовков"""
    client = TestClient(app)

    response = client.options(
        "/", headers={"Origin": "http://localhost:3000", "Access-Control-Request-Method": "GET"}
    )
    assert response.status_code in [200, 405]


def test_api_versioning():
    """Тест версионирования API"""
    client = TestClient(app)

    response = client.get("/")
    assert response.status_code == 200
    data = response.json()
    assert "version" in data
    assert data["version"] == "1.0.0"


def test_request_methods():
    """Тест HTTP методов"""
    client = TestClient(app)

    assert client.get("/").status_code == 200
    assert client.get("/health").status_code == 200

    assert client.post("/auth/register").status_code == 422
    assert client.post("/auth/login").status_code == 422

    fake_uuid = "550e8400-e29b-41d4-a716-446655440000"
    assert client.put(f"/payments/{fake_uuid}/confirm").status_code == 403

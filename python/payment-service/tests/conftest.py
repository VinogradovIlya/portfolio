import asyncio

import pytest
import pytest_asyncio
from fastapi.testclient import TestClient
from sqlalchemy.ext.asyncio import AsyncSession, async_sessionmaker, create_async_engine
from sqlalchemy.pool import StaticPool

from app.core.database import Base, get_async_session
from app.main import app
from app.models.payment import Payment
from app.models.user import User

TEST_DATABASE_URL = "sqlite+aiosqlite:///:memory:"

test_engine = create_async_engine(
    TEST_DATABASE_URL,
    poolclass=StaticPool,
    connect_args={"check_same_thread": False},
)

TestAsyncSessionLocal = async_sessionmaker(test_engine, class_=AsyncSession, expire_on_commit=False)


async def override_get_async_session():
    """Переопределяем получение сессии для тестов"""
    async with TestAsyncSessionLocal() as session:
        try:
            yield session
        finally:
            await session.close()


app.dependency_overrides[get_async_session] = override_get_async_session


@pytest_asyncio.fixture(scope="session")
def event_loop():
    """Создает event loop для всей сессии тестов"""
    policy = asyncio.get_event_loop_policy()
    loop = policy.new_event_loop()
    yield loop
    loop.close()


@pytest_asyncio.fixture(autouse=True)
async def setup_database():
    """Создает таблицы перед каждым тестом и удаляет после"""
    async with test_engine.begin() as conn:
        await conn.run_sync(Base.metadata.create_all)

    yield

    async with test_engine.begin() as conn:
        await conn.run_sync(Base.metadata.drop_all)


@pytest.fixture
def client():
    """FastAPI тест клиент"""
    return TestClient(app)


@pytest.fixture
def test_user_data():
    """Уникальные данные тестового пользователя"""
    import uuid

    unique_id = str(uuid.uuid4())[:8]

    return {
        "email": f"test{unique_id}@example.com",
        "username": f"testuser{unique_id}",
        "password": "password123",
        "full_name": "Test User",
    }


@pytest.fixture
def second_test_user_data():
    """Уникальные данные второго тестового пользователя"""
    import uuid

    unique_id = str(uuid.uuid4())[:8]

    return {
        "email": f"user2{unique_id}@example.com",
        "username": f"testuser2{unique_id}",
        "password": "password123",
        "full_name": "Test User 2",
    }


@pytest.fixture
def authenticated_user(client: TestClient, test_user_data: dict):
    """Создает аутентифицированного пользователя"""
    response = client.post("/auth/register", json=test_user_data)
    if response.status_code != 200:
        pytest.skip(f"Failed to create user: {response.status_code}")

    token = response.json()["access_token"]
    user_info = response.json()["user"]

    return {
        "token": token,
        "headers": {"Authorization": f"Bearer {token}"},
        "user": user_info,
        "data": test_user_data,
    }


@pytest.fixture
def second_user(client: TestClient, second_test_user_data: dict):
    """Создает второго аутентифицированного пользователя"""
    response = client.post("/auth/register", json=second_test_user_data)
    if response.status_code != 200:
        pytest.skip(f"Failed to create second user: {response.status_code}")

    token = response.json()["access_token"]
    user_info = response.json()["user"]

    return {
        "token": token,
        "headers": {"Authorization": f"Bearer {token}"},
        "user": user_info,
        "data": second_test_user_data,
    }


@pytest.fixture
def funded_user(client: TestClient, test_user_data: dict):
    """Создает пользователя с балансом для тестирования платежей"""
    response = client.post("/auth/register", json=test_user_data)
    if response.status_code != 200:
        pytest.skip(f"Failed to create funded user: {response.status_code}")

    token = response.json()["access_token"]
    user_info = response.json()["user"]

    import asyncio

    async def add_balance():
        async with TestAsyncSessionLocal() as session:
            from sqlalchemy import update

            stmt = update(User).where(User.id == user_info["id"]).values(balance=1000.00)
            await session.execute(stmt)
            await session.commit()

    try:
        loop = asyncio.get_running_loop()
        loop.create_task(add_balance())
    except RuntimeError:
        asyncio.run(add_balance())

    return {
        "token": token,
        "headers": {"Authorization": f"Bearer {token}"},
        "user": {**user_info, "balance": "1000.00"},
        "data": test_user_data,
    }

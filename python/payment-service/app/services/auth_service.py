import logging
from typing import Optional

from sqlalchemy import select
from sqlalchemy.ext.asyncio import AsyncSession

from ..core.security import create_access_token, get_password_hash, verify_password
from ..models.user import User
from ..schemas.user import UserCreate

logger = logging.getLogger(__name__)


class AuthService:
    def __init__(self, db: AsyncSession) -> None:
        self.db = db

    async def create_user(self, user_data: UserCreate) -> User:
        """Создание нового пользователя"""
        existing_user = await self.get_user_by_username(user_data.username)
        if existing_user:
            raise ValueError("Пользователь с таким username уже существует")

        existing_email = await self.get_user_by_email(user_data.email)
        if existing_email:
            raise ValueError("Пользователь с таким email уже существует")

        hashed_password = get_password_hash(user_data.password)
        db_user = User(
            email=user_data.email,
            username=user_data.username,
            full_name=user_data.full_name,
            hashed_password=hashed_password,
            balance=0.00,
        )

        self.db.add(db_user)
        await self.db.commit()
        await self.db.refresh(db_user)

        logger.info(f"Создан новый пользователь: {user_data.username}")
        return db_user

    async def authenticate_user(self, username: str, password: str) -> Optional[User]:
        """Аутентификация пользователя"""
        user = await self.get_user_by_username(username)
        if not user:
            return None

        if not verify_password(password, str(user.hashed_password)):
            return None

        logger.info(f"Успешная аутентификация пользователя: {username}")
        return user

    async def get_user_by_username(self, username: str) -> Optional[User]:
        """Получение пользователя по username"""
        result = await self.db.execute(select(User).where(User.username == username))
        return result.scalar_one_or_none()

    async def get_user_by_email(self, email: str) -> Optional[User]:
        """Получение пользователя по email"""
        result = await self.db.execute(select(User).where(User.email == email))
        return result.scalar_one_or_none()

    def create_token(self, user_id: int) -> str:
        """Создание JWT токена для пользователя"""
        return create_access_token(data={"sub": str(user_id)})

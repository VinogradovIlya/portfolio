from typing import Annotated

from fastapi import APIRouter, Depends, HTTPException, status
from fastapi.security import HTTPBearer
from sqlalchemy.ext.asyncio import AsyncSession

from ..core.database import get_async_session
from ..core.deps import get_current_user
from ..models.user import User
from ..schemas.user import TokenResponse, UserCreate, UserLogin, UserResponse
from ..services.auth_service import AuthService

router = APIRouter()
security = HTTPBearer()


@router.post("/register", response_model=TokenResponse)
async def register(
    user_data: UserCreate, db: Annotated[AsyncSession, Depends(get_async_session)]
) -> TokenResponse:
    """Регистрация нового пользователя"""
    auth_service = AuthService(db)

    try:
        user = await auth_service.create_user(user_data)
        token = auth_service.create_token(int(user.id))

        return TokenResponse(access_token=token, user=UserResponse.model_validate(user))
    except ValueError as e:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail=str(e))


@router.post("/login", response_model=TokenResponse)
async def login(
    credentials: UserLogin, db: Annotated[AsyncSession, Depends(get_async_session)]
) -> TokenResponse:
    """Вход пользователя"""
    auth_service = AuthService(db)

    user = await auth_service.authenticate_user(credentials.username, credentials.password)

    if not user:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED, detail="Неверные учетные данные"
        )

    token = auth_service.create_token(user.id)

    return TokenResponse(access_token=token, user=UserResponse.model_validate(user))


@router.get("/me", response_model=UserResponse)
async def get_current_user_info(
    current_user: Annotated[User, Depends(get_current_user)]
) -> UserResponse:
    """Получение информации о текущем пользователе"""
    return UserResponse.model_validate(current_user)

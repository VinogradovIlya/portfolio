from typing import Annotated, List
from uuid import UUID

from fastapi import APIRouter, Depends, HTTPException, Query, status
from sqlalchemy.ext.asyncio import AsyncSession

from ..core.database import get_async_session
from ..core.deps import get_current_user
from ..models.user import User
from ..schemas.payment import PaymentCreate, PaymentResponse
from ..services.payment_service import PaymentService

router = APIRouter()


@router.post("/", response_model=PaymentResponse)
async def create_payment(
    payment_data: PaymentCreate,
    current_user: Annotated[User, Depends(get_current_user)],
    db: Annotated[AsyncSession, Depends(get_async_session)],
) -> PaymentResponse:
    """Создание нового платежа"""
    payment_service = PaymentService(db)

    try:
        payment = await payment_service.create_payment(payment_data, current_user.id)
        return PaymentResponse.model_validate(payment)
    except ValueError as e:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail=str(e))


@router.get("/", response_model=List[PaymentResponse])
async def get_payments(
    current_user: Annotated[User, Depends(get_current_user)],
    db: Annotated[AsyncSession, Depends(get_async_session)],
    limit: int = Query(default=50, le=100),
    offset: int = Query(default=0, ge=0),
) -> List[PaymentResponse]:
    """Получение списка платежей пользователя"""
    payment_service = PaymentService(db)

    payments = await payment_service.get_user_payments(current_user.id, limit=limit, offset=offset)

    return [PaymentResponse.model_validate(payment) for payment in payments]


@router.put("/{payment_id}/confirm", response_model=PaymentResponse)
async def confirm_payment(
    payment_id: UUID,
    current_user: Annotated[User, Depends(get_current_user)],
    db: Annotated[AsyncSession, Depends(get_async_session)],
) -> PaymentResponse:
    """Подтверждение платежа"""
    payment_service = PaymentService(db)

    try:
        payment = await payment_service.confirm_payment(payment_id, current_user.id)
        return PaymentResponse.model_validate(payment)
    except ValueError as e:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail=str(e))


@router.put("/{payment_id}/cancel", response_model=PaymentResponse)
async def cancel_payment(
    payment_id: UUID,
    current_user: Annotated[User, Depends(get_current_user)],
    db: Annotated[AsyncSession, Depends(get_async_session)],
) -> PaymentResponse:
    """Отмена платежа"""
    payment_service = PaymentService(db)

    try:
        payment = await payment_service.cancel_payment(payment_id, current_user.id)
        return PaymentResponse.model_validate(payment)
    except ValueError as e:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail=str(e))


@router.get("/{payment_id}", response_model=PaymentResponse)
async def get_payment(
    payment_id: UUID,
    current_user: Annotated[User, Depends(get_current_user)],
    db: Annotated[AsyncSession, Depends(get_async_session)],
) -> PaymentResponse:
    """Получение информации о конкретном платеже"""
    payment_service = PaymentService(db)

    try:
        payment = await payment_service._get_payment_by_id(payment_id)

        if payment.sender_id != int(current_user.id) and payment.receiver_id != int(
            current_user.id
        ):
            raise HTTPException(
                status_code=status.HTTP_403_FORBIDDEN, detail="У вас нет доступа к этому платежу"
            )

        return PaymentResponse.model_validate(payment)
    except ValueError as e:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=str(e))

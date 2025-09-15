import logging
from datetime import datetime
from typing import List
from uuid import UUID

from sqlalchemy import or_, select
from sqlalchemy.ext.asyncio import AsyncSession

from ..models.payment import Payment, PaymentStatus
from ..models.user import User
from ..schemas.payment import PaymentCreate

logger = logging.getLogger(__name__)


class PaymentService:
    def __init__(self, db: AsyncSession) -> None:
        self.db = db

    async def create_payment(self, payment_data: PaymentCreate, sender_id: int) -> Payment:
        """Создание нового платежа"""
        sender = await self._get_user_by_id(sender_id)
        if sender.balance < payment_data.amount:
            raise ValueError("Недостаточно средств на балансе")

        if payment_data.receiver_id:
            receiver = await self._get_user_by_id(payment_data.receiver_id)
            if not receiver:
                raise ValueError("Получатель не найден")

            if sender_id == payment_data.receiver_id:
                raise ValueError("Нельзя переводить деньги самому себе")

        payment = Payment(
            sender_id=sender_id,
            receiver_id=payment_data.receiver_id,
            card_last_four=payment_data.card_last_four,
            card_holder_name=payment_data.card_holder_name,
            amount=payment_data.amount,
            description=payment_data.description,
            status=PaymentStatus.CREATED,
        )

        self.db.add(payment)
        await self.db.commit()
        await self.db.refresh(payment)

        logger.info(
            f"Создан платеж {payment.id} от пользователя {sender_id} на сумму {payment_data.amount}"
        )
        return payment

    async def confirm_payment(self, payment_id: UUID, user_id: int) -> Payment:
        """Подтверждение платежа"""
        payment = await self._get_payment_by_id(payment_id)

        if int(payment.sender_id) != user_id:
            raise ValueError("Вы можете подтверждать только свои платежи")

        if payment.status != PaymentStatus.CREATED:
            raise ValueError(f"Платеж уже обработан, статус: {payment.status.value}")

        sender = await self._get_user_by_id(int(payment.sender_id))
        if sender.balance < payment.amount:
            raise ValueError("Недостаточно средств на балансе")

        sender.balance = sender.balance - payment.amount

        if payment.receiver_id:
            receiver = await self._get_user_by_id(payment.receiver_id)
            receiver.balance = receiver.balance + payment.amount

        setattr(payment, "status", PaymentStatus.PAID)
        setattr(payment, "paid_at", datetime.now())

        await self.db.commit()
        await self.db.refresh(payment)

        logger.info(f"Подтвержден платеж {payment_id}")
        return payment

    async def cancel_payment(self, payment_id: UUID, user_id: int) -> Payment:
        """Отмена платежа"""
        payment = await self._get_payment_by_id(payment_id)

        if int(payment.sender_id) != user_id:
            raise ValueError("Вы можете отменять только свои платежи")

        if payment.status != PaymentStatus.CREATED:
            raise ValueError(f"Платеж уже обработан, статус: {payment.status.value}")

        setattr(payment, "status", PaymentStatus.CANCELLED)

        await self.db.commit()
        await self.db.refresh(payment)

        logger.info(f"Отменен платеж {payment_id}")
        return payment

    async def get_user_payments(
        self, user_id: int, limit: int = 100, offset: int = 0
    ) -> List[Payment]:
        """Получение списка платежей пользователя"""
        query = (
            select(Payment)
            .where(or_(Payment.sender_id == user_id, Payment.receiver_id == user_id))
            .order_by(Payment.created_at.desc())
            .offset(offset)
            .limit(limit)
        )

        result = await self.db.execute(query)
        return list(result.scalars().all())

    async def _get_user_by_id(self, user_id: int) -> User:
        """Получение пользователя по ID"""
        result = await self.db.execute(select(User).where(User.id == user_id))
        user = result.scalar_one_or_none()
        if not user:
            raise ValueError(f"Пользователь с ID {user_id} не найден")
        return user

    async def _get_payment_by_id(self, payment_id: UUID) -> Payment:
        """Получение платежа по ID"""
        result = await self.db.execute(select(Payment).where(Payment.id == payment_id))
        payment = result.scalar_one_or_none()
        if not payment:
            raise ValueError(f"Платеж с ID {payment_id} не найден")
        return payment

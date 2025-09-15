import uuid
from enum import Enum as PyEnum
from typing import TYPE_CHECKING, Optional

from sqlalchemy import Column, DateTime, Enum, ForeignKey, Integer, Numeric, String
from sqlalchemy.dialects.postgresql import UUID
from sqlalchemy.orm import relationship
from sqlalchemy.sql import func

from ..core.database import Base

if TYPE_CHECKING:
    from .user import User


class PaymentStatus(PyEnum):
    CREATED = "created"
    PAID = "paid"
    CANCELLED = "cancelled"


class Payment(Base):
    __tablename__ = "payments"

    id = Column(UUID(as_uuid=True), primary_key=True, default=uuid.uuid4, index=True)
    sender_id = Column(Integer, ForeignKey("users.id"), nullable=False)
    receiver_id = Column(Integer, ForeignKey("users.id"), nullable=True)

    card_last_four = Column(String(4), nullable=True)
    card_holder_name = Column(String(100), nullable=True)

    amount = Column(Numeric(10, 2), nullable=False)
    description = Column(String(500), nullable=True)
    status: Column[PaymentStatus] = Column(
        Enum(PaymentStatus), default=PaymentStatus.CREATED, nullable=False
    )

    created_at = Column(DateTime(timezone=True), server_default=func.now())
    updated_at = Column(DateTime(timezone=True), onupdate=func.now())
    paid_at = Column(DateTime(timezone=True), nullable=True)

    sender = relationship("User", foreign_keys=[sender_id], back_populates="sent_payments")
    receiver = relationship("User", foreign_keys=[receiver_id], back_populates="received_payments")

from typing import TYPE_CHECKING

from sqlalchemy import Column, DateTime, Integer, Numeric, String
from sqlalchemy.orm import relationship
from sqlalchemy.sql import func

from ..core.database import Base

if TYPE_CHECKING:
    from .payment import Payment


class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True, index=True)
    email = Column(String(100), unique=True, index=True, nullable=False)
    username = Column(String(50), unique=True, index=True, nullable=False)
    hashed_password = Column(String(128), nullable=False)
    full_name = Column(String(100), nullable=True)
    balance = Column(Numeric(10, 2), default=0.00, nullable=False)
    created_at = Column(DateTime(timezone=True), server_default=func.now())
    updated_at = Column(DateTime(timezone=True), onupdate=func.now())

    sent_payments = relationship(
        "Payment", foreign_keys="Payment.sender_id", back_populates="sender"
    )
    received_payments = relationship(
        "Payment", foreign_keys="Payment.receiver_id", back_populates="receiver"
    )

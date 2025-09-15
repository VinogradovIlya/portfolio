from datetime import datetime
from decimal import Decimal
from typing import Any, List, Optional
from uuid import UUID

from pydantic import BaseModel, Field, field_validator

from ..models.payment import PaymentStatus


class PaymentBase(BaseModel):
    amount: Decimal = Field(..., gt=0, decimal_places=2)
    description: Optional[str] = Field(None, max_length=500)


class PaymentCreate(PaymentBase):
    receiver_id: Optional[int] = Field(None, description="ID получателя для внутреннего перевода")
    card_last_four: Optional[str] = Field(
        None, pattern=r"^\d{4}$", description="4 последние цифры карты"
    )
    card_holder_name: Optional[str] = Field(None, max_length=100, description="ФИО владельца карты")

    @field_validator("card_last_four", "card_holder_name", mode="before")
    @classmethod
    def validate_external_payment(cls, v: Any, info: Any) -> Any:
        return v


class PaymentUpdate(BaseModel):
    status: PaymentStatus


class PaymentResponse(PaymentBase):
    id: UUID
    sender_id: int
    receiver_id: Optional[int]
    card_last_four: Optional[str]
    card_holder_name: Optional[str]
    status: PaymentStatus
    created_at: datetime
    updated_at: Optional[datetime]
    paid_at: Optional[datetime]

    sender_username: Optional[str] = None
    receiver_username: Optional[str] = None

    class Config:
        from_attributes = True


class PaymentListResponse(BaseModel):
    payments: List[PaymentResponse]
    total: int
    page: int
    per_page: int

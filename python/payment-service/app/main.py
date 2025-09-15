import logging
from contextlib import asynccontextmanager
from typing import AsyncGenerator, Dict

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from .routers import auth, payments
from .utils.logger import setup_logging

setup_logging()
logger = logging.getLogger(__name__)


@asynccontextmanager
async def lifespan(app: FastAPI) -> AsyncGenerator[None, None]:
    logger.info("Запуск приложения...")
    logger.info("База данных инициализирована")
    yield
    logger.info("Завершение работы приложения...")


app = FastAPI(
    title="Payment Service API",
    description="Сервис для создания и управления платежами",
    version="1.0.0",
    lifespan=lifespan,
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000", "http://127.0.0.1:3000"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(auth.router, prefix="/auth", tags=["authentication"])
app.include_router(payments.router, prefix="/payments", tags=["payments"])


@app.get("/")
async def root() -> Dict[str, str]:
    """Корневой эндпоинт"""
    return {"message": "Payment Service API", "version": "1.0.0", "docs": "/docs", "health": "OK"}


@app.get("/health")
async def health_check() -> Dict[str, str]:
    """Проверка здоровья приложения"""
    return {"status": "healthy", "service": "payment-service"}

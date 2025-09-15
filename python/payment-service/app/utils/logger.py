import logging
import sys


def setup_logging() -> None:
    """Настройка логирования для приложения"""

    log_format = "[%(asctime)s] %(levelname)s in %(name)s: %(message)s"

    logging.basicConfig(
        level=logging.INFO,
        format=log_format,
        handlers=[
            logging.StreamHandler(sys.stdout),
        ],
    )

    logging.getLogger("sqlalchemy.engine").setLevel(logging.WARNING)
    logging.getLogger("uvicorn.access").setLevel(logging.INFO)

    logger = logging.getLogger("payment_service")
    logger.setLevel(logging.INFO)

    logger.info("Система логирования инициализирована")

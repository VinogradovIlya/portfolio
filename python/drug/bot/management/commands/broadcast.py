from django.core.management.base import BaseCommand
from pyrogram import Client
from bot.models import TelegramUser
import os
import asyncio

class Command(BaseCommand):
    help = 'Отправка сообщения пользователям бота'

    def add_arguments(self, parser):
        parser.add_argument('message', type=str, help='Текст сообщения')

    def handle(self, *args, **options):
        asyncio.run(self.send_message(options['message']))

    async def send_message(self, message_text):
        app = Client(
            "drug_bot",
            api_id=int(os.getenv('TELEGRAM_API_ID')),
            api_hash=os.getenv('TELEGRAM_API_HASH')),
            bot_token=os.getenv('TELEGRAM_BOT_TOKEN'),
            workdir="bot/"
        )
        
        async with app:
            users = TelegramUser.objects.filter(is_blocked=False)
            
            for user in users:
                try:
                    await app.send_message(
                        chat_id=user.telegram_id,
                        text=message_text
                    )
                    print(f"Отправлено: {user.first_name}")
                    await asyncio.sleep(0.05)  # Пауза между сообщениями
                except Exception as e:
                    print(f"Ошибка {user.telegram_id}: {e}")
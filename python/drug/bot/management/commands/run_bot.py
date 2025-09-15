import os
import logging
from django.core.management.base import BaseCommand
from pyrogram import Client, filters
from pyrogram.types import InlineKeyboardMarkup, InlineKeyboardButton

class Command(BaseCommand):
    help = 'Запуск Telegram бота'

    def handle(self, *args, **options):
        logging.getLogger("pyrogram").setLevel(logging.WARNING)
        
        api_id_raw = os.getenv('TELEGRAM_API_ID')
        if api_id_raw is None:
            self.stdout.write(self.style.ERROR('❌ TELEGRAM_API_ID не найден!'))
            return
        
        api_id = int(api_id_raw)
        api_hash = os.getenv('TELEGRAM_API_HASH')
        bot_token = os.getenv('TELEGRAM_BOT_TOKEN')
        
        app = Client(
            "drug_bot",
            api_id=api_id,
            api_hash=api_hash,
            bot_token=bot_token,
            workdir="bot/"
        )
        
        @app.on_message(filters.command("start"))
        async def start_command(client, message):
            user = message.from_user
            user_id = user.id
            
            keyboard = InlineKeyboardMarkup([
                [InlineKeyboardButton(
                    "🐾 Перейти на сайт", 
                    url=f"https://yourdomain.com/invite/{user_id}"
                )]
            ])
            
            await message.reply_text(
                f"Привет, {user.first_name}! 👋\n\n"
                f"Добро пожаловать в социальную сеть для владельцев питомцев!\n",
                # reply_markup=keyboard
            )
        
        self.stdout.write(self.style.SUCCESS('🤖 Бот запущен и готов к работе!'))
        self.stdout.write('Нажми Ctrl+C для остановки')
        
        app.run()
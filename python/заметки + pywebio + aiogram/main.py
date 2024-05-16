from view.note import Note
from controller.sql_controller import DB
from model.model import Model
import os
from pathlib import Path
import asyncio
from aiogram import Bot, Dispatcher, types, F
from aiogram.filters.command import Command


DIR = Path(__file__).parent.resolve()
os.chdir(DIR)
API_TOKEN = '7028351306:AAEdgf7w2qHa-QG6dtOHZbNMfkAc5XXMDdQ'


bot = Bot(token=API_TOKEN)
dp = Dispatcher()
db = DB('notes.db')
with db as cur:
    cur.execute("""create table if not exists notes(
                    id INTEGER PRIMARY KEY,
                    title VARCHAR,
                    text VARCHAR,
                    date DATETIME);""")


@dp.message(Command("start"))
async def cmd_start(message: types.Message):
    kb = [
        [types.KeyboardButton(text="Список дел")],
    ]
    keyboard = types.ReplyKeyboardMarkup(resize_keyboard=True, keyboard=kb)
    await message.answer("Привет! Я бот для написания списка дел.", reply_markup=keyboard)


@dp.message(F.text.lower() == "список дел")
async def functions_call(message: types.Message):
    kb = [
        [types.KeyboardButton(text="Добавить заметку")],
        [types.KeyboardButton(text="Удалить заметку")]
    ]
    keyboard = types.ReplyKeyboardMarkup(resize_keyboard=True, keyboard=kb)
    await message.answer("Что вы хотите сделать?", reply_markup=keyboard)


@dp.message(F.text.lower() == "добавить заметку")
async def function_call_add_note(message: types.Message):
    note = Note()
    model = Model(note)
    with db:
        db.add(model.info_note())
    with db:
        Note.print_note(*db.output())
    await message.answer("Заметка добавлена")


@dp.message(F.text.lower() == "удалить заметку")
async def function_call_add_note(message: types.Message):
    with db:
        Note.print_note(*db.output())
        db.delete(Model.del_note(Note))
    await message.answer("Заметка удалена")
    with db:
        Note.print_note(*db.output())


@dp.message()
async def echo(message: types.Message):
    await message.reply(f"Я Вас не понял: {message.text}")


async def main():
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())

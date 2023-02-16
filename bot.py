import telebot
import sqlite3
import pandas as pd


# Запуск бота по токену
bot = telebot.TeleBot('5917529535:AAFD3WCLgiwZXqZtrQqAxkUi0Qam5w-AEms')


@bot.message_handler(commands=['data'])
def cancel_notification(message):
    # Подключение к БД
    con = sqlite3.connect('C:\\Users\\artjo\\Desktop\\esp32\\camera_data.db')
    cur = con.cursor()
    # Взятие всех записей
    cur.execute(f"""SELECT * FROM main_data""")
    columns = [desc[0] for desc in cur.description]
    data = cur.fetchall()
    df = pd.DataFrame(list(data), columns=columns)
    # Запись в EXCEL
    writer = pd.ExcelWriter('C:\\Users\\artjo\\Desktop\\Semester2\\4\\data.xlsx')
    df.to_excel(writer, sheet_name='Результаты', index=False)
    writer.save()
    # Отправка в чат
    with open('C:\\Users\\artjo\\Desktop\\Semester2\\4\\data.xlsx', 'rb') as f1:
        bot.send_document(message.chat.id, f1)


@bot.message_handler(commands=['help'])
def send_text(message):
    bot.send_message(message.chat.id, 'Используйте команду /data для получения файла с результатами')


bot.polling()

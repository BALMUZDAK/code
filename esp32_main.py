import cv2
import numpy as np
import time
import datetime
import requests
from urllib.request import urlopen
import sqlite3


# IP адрес камеры из ARDUINO IDE
URL = "http://192.168.0.17"
# Подключение к стриму
cap = cv2.VideoCapture(URL + ":81/stream")
# Проставляем расширение экрана
requests.get(URL + "/control?var=framesize&val={}".format(5))
# Проставляем качество видеопотока
requests.get(URL + "/control?var=quality&val={}".format(10))

# Параметры рапознавания окружностей
params = cv2.SimpleBlobDetector_Params()
params.minInertiaRatio = 0.6
detector = cv2.SimpleBlobDetector_create(params)

# Токен ТГ бота и ID чата
token = '5917529535:AAFD3WCLgiwZXqZtrQqAxkUi0Qam5w-AEms'
chat_id = '-863991500'

# Подключение к БД (базе данных)
con = sqlite3.connect('camera_data.db')
cur = con.cursor()

if __name__ == '__main__':
    while True:
        if cap.isOpened():
            # взятие кадра
            ret, frame = cap.read()
            if ret:
                # Перевод кадра в черно-белое изображение
                frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                # распознавание окружностей на изображении
                blobs = detector.detect(frame)

                # Отображение кадров в отдельном окне:
                # cv2.imshow("frame", frame_gray)
                # cv2.waitKey(1)

                # n - количество окружностей
                n = len(blobs)
                # Если найдены окружности
                if n > 0:
                    # Блок отображения:
                    # for b in blobs:
                    #     pos = b.pt
                    #     r = b.size / 2
                    #     cv2.circle(frame_gray, (int(pos[0]), int(pos[1])),
                    #                int(r), (255, 0, 0), 2)
                    # cv2.imshow("frame", frame_gray)
                    # cv2.waitKey(1)

                    # Задержка 4 секунды, чтобы дать кубикам остановиться
                    time.sleep(4)
                    # Очистка всех окон и отключение от видеопотока
                    cv2.destroyAllWindows()
                    cap.release()
                    # Подключение для взятие одного изображения (скрина)
                    req = urlopen('http://192.168.0.17/capture')
                    arr = np.asarray(bytearray(req.read()), dtype=np.uint8)
                    frame = cv2.imdecode(arr, 0)
                    # Определение количества окружностей на изображении
                    blobs = detector.detect(frame)
                    count = len(blobs)
                    # print(count)
                    # Задержка 30 секунд
                    time.sleep(30)
                    # Взятие текущего времени
                    now = datetime.datetime.now().strftime("%d/%m/%Y %H:%M:%S")
                    # Разделение времени на дату и время
                    dt = now.split(' ')
                    # Подготовка текста для сообщения ТГ
                    txt = f"""Сумма очков: {count} \n{now}"""
                    url = 'https://api.telegram.org/bot' + token + '/sendMessage?chat_id=' + \
                          chat_id + '&text=' + txt
                    # Отправка сообщения
                    requests.get(url)
                    # Запись в БД
                    cur.execute(f"""INSERT INTO main_data (count, time, date) 
                                    VALUES ({count},'{dt[1]}','{dt[0]}')""")
                    con.commit()
                    # Повторный запуск видеопотока
                    cap = cv2.VideoCapture(URL + ":81/stream")
    cv2.destroyAllWindows()
    cap.release()

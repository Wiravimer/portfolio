from flask import Flask
from flask import request
from flask import jsonify
from flask_restful import Api, Resource, reqparse
import requests
import json
import threading
import time
import sqlite3
import datetime
import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.ticker import LinearLocator


app = Flask(__name__)
api = Api()

TOKEN = '123456789:ABcDFg-Ps0nSqORBxlzgjhqUzR17YR54Wx'
URL = 'https://api.telegram.org/bot'



# +++++++++++++++++++++++++++++++

def set_status(status, parameter, chat_id):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    arduino_id=cur.execute(f'SELECT arduino_id FROM users WHERE alias="{parameter.strip()}" AND chat_id={chat_id};').fetchone()[0]
    cur.execute(f'UPDATE arduino_status SET status = "{status.upper()}" WHERE arduino_id = {arduino_id}')
    conn.commit()
    print("изменение состояния на", status.upper())


def register(parameter, user_id):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    l=parameter.split()
    arduino_id=l[0]
    alias = l[1]
    cur.execute(f"INSERT INTO users (chat_id, arduino_id, alias) VALUES ({user_id}, {arduino_id}, '{alias}');")
    cur.execute(f"INSERT INTO arduino_status (arduino_id, status) VALUES ({arduino_id}, 'ON');")
    conn.commit()
    send_message(user_id, alias+' создан')

def send_img(parameter, chat_id):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    arduino_id=cur.execute(f'SELECT arduino_id FROM users WHERE alias="{parameter.strip()}" AND chat_id={chat_id};').fetchone()[0]
    
    data=cur.execute(f"SELECT data_time,soil_humidity  FROM plant_status WHERE arduino_id={arduino_id};").fetchall()
    x=[d[0] for d in data]
    y=[d[1] for d in data]
    df = pd.DataFrame({"Time": x, "soil_humidity": y})
    ax = df.plot(x='Time', y='soil_humidity', rot=45, figsize=(20, 15))
    ax.grid()
    ax.xaxis.set_major_locator(LinearLocator(len(x)))
    ax.set_xticklabels(x)
    plt.savefig('saved_figure.png')

    files = {'photo': open('saved_figure.png', 'rb')}
    requests.post(f'{URL}{TOKEN}/sendPhoto?chat_id={chat_id}', files=files)



# =========================================================================
def get_updates(offset=0):
    result = requests.get(f'{URL}{TOKEN}/getUpdates?offset={offset}').json()
    return result['result']

def send_message(chat_id, text='test massage'):
    requests.get(f'{URL}{TOKEN}/sendmessage?chat_id={chat_id}&text={text}')
    
def check_message(update_id):
    # update_id=id
    json=get_updates(update_id)

    if update_id < json[-1]['update_id']:#проверяем есть ли новое сообщение
        update_id = json[-1]['update_id'] # Присваиваем ID последнего отправленного сообщения боту
        for j in json[1:]:#обработка каждого нового сообщения
            try:#обработка исключений если придет сообщение без текста
                msg=j['message']['text']
                chat_id=j['message']['chat']['id']
                command = msg.split("/")[-1]
                parameter = msg.split("/")[0]

                if command == "on" or command == "off":
                    set_status(command, parameter, chat_id)
                elif command == "register":
                    register(parameter, chat_id)
                elif command == "graph":
                    send_img(parameter, chat_id)

                

                # 
            except: print('Нет текста')    
    else: print('Нет новых сообщений')

    return update_id

    
# =================================
@app.route('/api/<int:id>', methods=['GET'])
def get(id):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    cur.execute("SELECT status FROM arduino_status WHERE arduino_id = ?", (id, ))
    status=cur.fetchone()[0]
    if status == 'ON':
        return {'num':1}
    elif status == 'OFF':
        return {'num':0}
    return {'num':1}


def power_status(arduino_id, value):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    info=cur.execute("SELECT chat_id, alias FROM users WHERE arduino_id = ?", (arduino_id, )).fetchone()
    if value == 1:
        send_message(info[0], text= info[1]+' ON')
    elif value == 0:
        send_message(info[0], text= info[1]+' OFF')

def pump_status(arduino_id, value):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    info=cur.execute("SELECT chat_id, alias FROM users WHERE arduino_id = ?", (arduino_id, )).fetchone()
    if value == 1:
        send_message(info[0], text= info[1]+' pump ON')
    elif value == 0:
        send_message(info[0], text= info[1]+' pump OFF')

def measure(arduino_id, value):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    dt=datetime.datetime.now().strftime("%d.%m.%Y_%H:%M:%S")
    cur.execute(f'INSERT INTO plant_status(arduino_id, soil_humidity, data_time) VALUES({arduino_id}, {value}, "{dt}");')
    conn.commit()

@app.route('/', methods=['POST'])
def arduino_status():
    request_data = request.get_json()
    id=request_data['id']
    info=request_data['info']
    value=request_data['value']

    if info == "power":
        power_status(id, value)
    elif info == "pump_status":
        pump_status(id, value)
    elif info == "measure":
        measure(id, value)

    return '201'

# -----------------------------------------------------------------------------
if __name__ == '__main__':
    def delay():
        # update_id = get_updates()[-1]['update_id']
        update_id =requests.get(f'{URL}{TOKEN}/getUpdates').json()['result'][-1]['update_id']
        while True:
            update_id=check_message(update_id)
            time.sleep(10)
    d= threading.Thread(target=delay, daemon = True)
    d.start() #фоновый процесс
    app.run()
    d.join()
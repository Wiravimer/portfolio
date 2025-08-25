from socket import AF_INET, socket, SOCK_STREAM
from threading import Thread
import tkinter
from unicodedata import name
import random

prime_number_list=[2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,
127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,
283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,
467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,
661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,
877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997]

nickname = False
session_key = 123

def symmetric_encryption(message):
    global session_key
    crypt = ''
    for i in message:
        crypt += chr(ord(i)^session_key)
    return crypt

def Diffie_Hellman (id):
    global session_key
    if id == 0:
        N = random.choice(prime_number_list)
        g = random.choice(prime_number_list)
        private_key = random.choice(prime_number_list)
        public_key = g**private_key % N
        client_socket.send(f'{N}:{g}:{public_key}'.encode('utf8'))
        msg = client_socket.recv(BUFSIZ).decode("utf8")
        split = msg.split(':')
        _public_key_ = int(split[1])

    else:
        msg = client_socket.recv(BUFSIZ).decode("utf8")
        split = msg.split(':')
        N = int(split[1])
        g = int(split[2])
        _public_key_ = int(split[3])
        private_key = random.choice(prime_number_list)
        public_key = g**private_key % N
        client_socket.send(f'{public_key}'.encode('utf8')) 
       
    session_key = _public_key_**private_key % N
    print('Session key: ', session_key)


# получения сообщений
def receive():
    while True:
        try:
            msg = client_socket.recv(BUFSIZ).decode("utf8")#recv () является блокирующей частью. Он останавливает выполнение до тех пор, пока не получит сообщение,            
            split = msg.split(':') 

            if split[0] == 'Server':
                msg = split[1]

            elif split[0] == 'id':
                id=int(split[1])
                top.title(f"id: {id}")
                msg = 0
            elif split[0] == 'Join':  
                msg_list.insert(tkinter.END, split[1])
                Diffie_Hellman(id)
                msg_list.insert(tkinter.END, "Шифрование установлено")
                msg = ' '
            else:
                msg = split[0] + ': ' + symmetric_encryption(split[1])

            if msg:
                msg_list.insert(tkinter.END, msg)
            
                
        except OSError:
            break

# обработка отправленных сообщений
def send(event=None):
    global nickname
    msg = my_msg.get()# my_msg - это поле ввода в графическом интерфейсе, и поэтому мы извлекаем сообщение для отправки
    my_msg.set("")# очищаем поле.
    
    if msg == "{quit}": # Если это сообщение о выходе, мы закрываем сокет, а затем приложение с графическим интерфейсом (через top.close ())
        client_socket.close()
        top.quit()

    if nickname:
        msg_list.insert(tkinter.END, 'Вы: '+msg)
        msg = symmetric_encryption(msg)#
    else:
        nickname = msg
        top.title(nickname)

    client_socket.send(msg.encode('utf8'))#отправляем сообщение на сервер
# Эта функция вызывается когда закрывается окно
def on_closing(event=None):
    my_msg.set("{quit}")
    send()

top = tkinter.Tk()
top.title("TkMessenger")

messages_frame = tkinter.Frame(top)
my_msg = tkinter.StringVar()
# my_msg.set("Введите ваше сообщение здесь")
scrollbar = tkinter.Scrollbar(messages_frame)
msg_list = tkinter.Listbox(messages_frame, height=15, width=50, yscrollcommand=scrollbar.set)
scrollbar.pack(side=tkinter.RIGHT, fill=tkinter.Y)
msg_list.pack(side=tkinter.LEFT, fill=tkinter.BOTH)
msg_list.pack()
messages_frame.pack()

entry_field = tkinter.Entry(top, textvariable=my_msg)
entry_field.bind("<Return>", send)
entry_field.pack()
send_button = tkinter.Button(top, text="отправить", command=send)
send_button.pack()

top.protocol("WM_DELETE_WINDOW", on_closing)


# HOST = input('Введите хост: ')
# PORT = input('Введите порт: ')
# if not PORT:
#     PORT = 33000
# else:
#     PORT = int(PORT)

# if not HOST:
#     HOST = '127.0.0.1'

PORT = 33000
HOST = '127.0.0.1'

BUFSIZ = 1024
ADDR = (HOST, PORT)


client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect(ADDR)


# Как только мы получаем адрес и создаем сокет для подключения к нему, 
# мы запускаем поток для получения сообщений, а затем основной цикл для нашего приложения с графическим интерфейсом
receive_thread = Thread(target=receive)
receive_thread.start()
tkinter.mainloop()

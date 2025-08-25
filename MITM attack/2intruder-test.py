from socket import AF_INET, socket, SOCK_STREAM
from threading import Thread
from time import sleep

session_key = [0, 1]

# Симмитричное шифрование
#====================================================================
def symmetric_encryption(message, id):
    crypt = ''
    for i in message:
        crypt += chr(ord(i)^session_key[id])
    return crypt
#====================================================================


# Протокол Диффи-Хеллмана
#====================================================================
def Diffie_Hellman (id):
    client_socket = list_clients[id]
    N = 557
    g = 577
    private_key = 919

    if id == 0:
        msg = client_socket.recv(BUFSIZ).decode("utf8")
        split = msg.split(':')
        N = int(split[0])
        g = int(split[1])
        _public_key_ = int(split[2])
        public_key = g**private_key % N
        client_socket.send(f'{list_name[id]}:{public_key}'.encode('utf8'))
        session_key[id] = _public_key_**private_key % N
        print(f'Session key {list_name[id]}: {session_key[id]}' )
    else:
        public_key = g**private_key % N
        client_socket.send(f'{list_name[id]}:{N}:{g}:{public_key}'.encode('utf8'))
        msg = client_socket.recv(BUFSIZ).decode("utf8")
        _public_key_ = int(msg)
        session_key[id] = _public_key_**private_key % N
        print(f'Session key {list_name[id]}: {session_key[id]}', )
#====================================================================


# принятия соединений
#====================================================================
def accept_incoming_connections():
    while True:
        client, client_address = SERVER.accept()
        print("%s:%s соединено" % client_address)

        msg = "Добро пожаловать , введите своё имя и нажмите Enter"
        sendServer(msg,client)

        list_clients.append(client)
        list_addresses.append(client_address)          

        Thread(target=handle_client, args=(client,)).start()
#====================================================================


# запускает поток обработки для клиента
#====================================================================
def handle_client(client):

    id = list_clients.index(client)   
    sendServer(id, client, 'id') 

    name = client.recv(BUFSIZ).decode("utf8")
    list_name.append(name)

    msg = f'Добро пожаловать {name}!'
    sendServer(msg,client)

    From_id = id
    To_id = 0 if id == 1 else 1

    if len(list_name) < 2:
        msg = "Собеседников нет"
        sendServer(msg, client)

    else:
        msg = f'{list_name[From_id]} вступил в переписку'
        sendServer(msg, list_clients[To_id], 'Join')
        Diffie_Hellman(To_id)
        Thread(target=forward, args=(To_id, From_id)).start()
        
        msg = f"{list_name[To_id]} в сети"
        sendServer(msg, list_clients[From_id], 'Join')
        Diffie_Hellman(From_id)
        Thread(target=forward, args=(From_id, To_id)).start() 
#====================================================================


# переправка сообщения от клиента
#====================================================================
def forward(From_id, To_id):
    msg = list_clients[From_id].recv(BUFSIZ)
    msg = msg.decode('utf8')

    msg = symmetric_encryption(msg, From_id)   
    print(f"{list_name[From_id]}->{msg}")
    msg = symmetric_encryption(msg, To_id)

    list_clients[To_id].send(f'{list_name[From_id]}:{msg}'.encode('utf8'))
#====================================================================


# отправка сообщений сервера
#====================================================================
def sendServer(msg, client ,prefix = 'Server'):
    sleep(0.5)
    client.send(f'{prefix}:{msg}'.encode('utf8'))
#====================================================================
        
list_clients = []
list_addresses = []
list_name = []

HOST = '127.0.0.1'#локальный хост
PORT = 33000
BUFSIZ = 1024
ADDR = (HOST, PORT)

SERVER = socket(AF_INET, SOCK_STREAM)
SERVER.bind(ADDR)

if __name__ == "__main__":
    SERVER.listen(5)    
    print(f"Старт сервера на {HOST}:{PORT} \nОжидание соединения")
    ACCEPT_THREAD = Thread(target=accept_incoming_connections)
    ACCEPT_THREAD.start()# Бесконечный цикл.
    ACCEPT_THREAD.join()
    SERVER.close()

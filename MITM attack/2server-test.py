from socket import AF_INET, socket, SOCK_STREAM
from threading import Thread
from time import sleep

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

        msg = f"{list_name[To_id]} в сети"
        sendServer(msg, list_clients[From_id], 'Join')  

        msg = f'{list_name[From_id]} вступил в переписку'
        sendServer(msg, list_clients[To_id], 'Join')
        
    while True:
        msg = client.recv(BUFSIZ)

        if msg != bytes("{quit}", "utf8"):
            forward(msg, From_id, To_id)
        else:
            client.send(bytes("{quit}", "utf8"))
            client.close()

            msg = f"{list_name[To_id]} покинул переписку"
            sendServer(msg, To_id)

            list_name.pop(id)
            list_clients.pop(id)
            list_addresses.pop(id)
            
            break
#====================================================================


# переправка сообщения от клиента
#====================================================================
def forward(msg, From_id, To_id):
    msg = msg.decode('utf8')   
    print(f"{list_name[From_id]}->{msg}")
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

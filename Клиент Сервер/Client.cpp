//#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>


using namespace std;
#pragma warning(disable: 4996)

const char* idServ1 = "127.0.0.1";
const char* idServ2 = "127.0.0.2";

const u_short portServ1 = 1111;
const u_short portServ2 = 1112;

bool connect1 = false;
bool connect2 = false;



void CreateConnect(int numServ) {

    // структура для хранения адреса
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);

    //адрес и порт для подключения устанавливаются в соответствии с номером сервера
    addr.sin_addr.s_addr = numServ == 1 ? inet_addr(idServ1) : inet_addr(idServ2);//ip - local host
    addr.sin_port = numServ == 1 ? htons(portServ1) : htons(portServ2);//незарезервированный хост
    addr.sin_family = AF_INET;//константа для интернет протокола

    //создание сокета
    SOCKET Connection = socket(
        AF_INET,//семейство интернет протоколов
        SOCK_STREAM,//протокод соединения
        NULL);

    //осуществление подключение и проверка на успех
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cout << "unable to connect.\n";
        return;
    }

    cout << "connected to " << numServ << " server\n";
    char msg[256];

    //если это сервер1 отправляем ему рандомные координату для перемещения окна
    if (numServ == 1) {
        connect1 = true;
        while (true) {

            if (recv(Connection, msg, sizeof(msg), NULL) == SOCKET_ERROR)break;
            else cout << msg << endl;
        }

            }
    else {
        connect2 = true;

        //ждём первое сообщение сервера
        if (recv(Connection, msg, sizeof(msg), NULL) == SOCKET_ERROR) return;
        else cout << msg << endl;

        if (recv(Connection, msg, sizeof(msg), NULL) == SOCKET_ERROR) return;
        else cout << msg << endl;

        // отправляем выбор
        int num; cin >> num;
        char mess[256];
        sprintf(mess, "%d", num);
        send(Connection, mess, sizeof(mess), NULL);

        // получаем сообщения от сервера каждые n секунд
        while (true)
        {
            //чтение всех сообщений и вывод их на экран
            if (recv(Connection, msg, sizeof(msg), NULL) == SOCKET_ERROR) return;
            else cout << msg << endl;
        }

    }
}


//Выполняется в главном потоке рекурсивно непрерывно, для распознования команд пользователя
void Menu() {

    int result;
    cin >> result;

    switch (result)
    {
        //для подключения к двум серверам используются отдельные потоки, которые выполняют функции подключения
    case 1: {
        //логическая переменная connect1 позволяет проверить создано ли уже подключение
        if (!connect1) {
            //в поток передается функция для подключения (LPTHREAD_START_ROUTINE)CreateConnect и номер сервера  (LPVOID)(1)
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CreateConnect, (LPVOID)(1), NULL, NULL);


        }
        else {
            cout << "cannot connect to server again!";
        }
        Menu();
        break;
    }
    case 2: {
        //логическая переменная connect2 позволяет проверить создано ли уже подключение
        if (!connect2) {
            //в поток передается функция для подключения (LPTHREAD_START_ROUTINE)CreateConnect и номер сервера (LPVOID)(2)
            //CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CreateConnect, (LPVOID)(2), NULL, NULL);
            CreateConnect(2);
        }
        else {
            cout << "cannot connect to server again!";
        }
        Menu();
        break;
    }

    default:
        Menu();
        break;
    }
}


int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "Russian");

    //Загрузка библиотеки для осуществления подключния
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cout << "Error" << endl;
        exit(1);
    }

    //вывод меню для работы с приложением
    cout << "\nДобро пожаловать в клиент серверное приложение\n\nВыберите к какому серверу нужно подключиться:\n";
    cout << "\nДля подключения к первому серверу нажмите 1\n\nДля подключения к второму серверу нажмите 2\n";
    Menu();

    //окончание работы
    system("pause");
    return 0;
}
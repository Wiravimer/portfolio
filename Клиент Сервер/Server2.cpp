//#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <tlhelp32.h>
using namespace std;

#pragma warning(disable: 4996)


int MaxClientsCount = 10;
SOCKET Sockets[10];
int SockCount = 0;

int CharToInt(char* str)
{
    int result = 0;
    while (*str != '\0')
    {
        result *= 10;
        result += *str - '0';
        ++str;
    }

    return result;
}




int Information[10];

string GetInformation();
int GetInformation(int vibor) {

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    int memory;
    if (vibor == 1)
        memory = statex.ullAvailPhys;
    else if (vibor == 2)
        memory = statex.ullAvailPhys / 1024 / 1024;
    else if (vibor == 3)
        memory = statex.ullAvailPhys / 1024 / 1024 / 1024;
    else memory = -1;

    return memory;
}


void PrintTime() {

    auto mytime = chrono::system_clock::now();
    time_t timeSent = chrono::system_clock::to_time_t(mytime);
    cout << "Отправка сообщения клиенту выполнена в " << ctime(&timeSent) << "\n";
}



void SentParameters(int index) {

    
    wchar_t bufClient[256];
    GetModuleFileNameW(NULL, bufClient, 256);
    char bufChar[256];
    for (int i = 0; i < sizeof(bufClient); i++)bufChar[i] = (char)bufClient[i];
    send(Sockets[index], bufChar, sizeof(bufChar), NULL);


    char msg[] = "input type: 1 - bytes, 2 - mb, 3 - gb";
    //отправка сообщения
    send(Sockets[index], msg, sizeof(msg), NULL);
    //вывод времени отправки
    PrintTime();


    //получение сообщений от клиента
    char buf[256];
    recv(Sockets[index], buf, sizeof(buf), NULL);
    int vibor = CharToInt(buf);
    cout << vibor << endl;

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    int memory;

    if (vibor == 1)
        memory = statex.ullAvailPhys;
    else if (vibor == 2)
        memory = statex.ullAvailPhys / 1024 / 1024;
    else if (vibor == 3)
        memory = statex.ullAvailPhys / 1024 / 1024 / 1024;
    else memory = -1;

    char otvet[50];
    char strNum[50] = "";
    itoa(memory, otvet, 10);
    send(Sockets[index], otvet, sizeof(otvet), NULL);

    Information[index] = memory;

    //каждые 10 секунд сервер вычисляет информацю заново и если она изменилась, то отправляет снова клиенту
    while (true) {

        Sleep(10000);
        int inf = GetInformation(vibor);

        if (Information[index] != inf) {


            Information[index] = inf;
            // strcpy(msg, Information[index].c_str());
            sprintf(msg, "%d", inf);

            //если клиент отключися перестает отправляться
            if (send(Sockets[index], msg, sizeof(msg), NULL) == SOCKET_ERROR) {
                cout << "Прервано\n";
                return;
            }
            //если соединение нормальное и отправка завершена, печатается время отправления
            else { PrintTime(); }
        }
    }
}


int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "Russian");


    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cout << "Error" << endl;
        exit(1);
    }

    HANDLE hMutex = CreateMutexW(NULL, TRUE, L"MutexForServer1");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        cout << "Уже есть один экземпляр сервера!";
        exit(0);
    }

    //создание адреса
    SOCKADDR_IN addr;// структура для хранения адреса
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.2");//ip - local host
    addr.sin_port = htons(1112);//незарезервированный хост
    addr.sin_family = AF_INET;//константа для интернет протокола

    SOCKET sListen = socket(AF_INET,// семейство интернет протоколов
        SOCK_STREAM,//протокод соединения
        NULL);

    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

    listen(sListen, MaxClientsCount);

    SOCKET newConnection;
    for (int i = 0; i < MaxClientsCount; i++) {

        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if (newConnection == 0) {
            cout << "Error connection with client " << i + 1 << "\n";
        }
        else
        {
            cout << "Client " << i + 1 << " connected!" << "\n";
            Sockets[i] = newConnection;
            SockCount++;
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SentParameters, (LPVOID)(i), NULL, NULL);
        }
    }


    //окончание работы
    system("pause");
    return 0;
}
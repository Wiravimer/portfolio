#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;

#pragma warning(disable: 4996)


SOCKET Sockets[10];
int SockCount = 0;
int MaxClientsQuantity = 10;//максимальное колличество клиентов, которые могут быть подключены

//глобальные переменные для формирования сообщения


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


void SentParameters(int index) {

	char Descriprion1[20] = "Разрешение экрана: ";
	char Descriprion2[45] = ", Количество мониторов: ";


	//получение параметров

	//перобразование к массиву символов для отправки сообщения
	char mess2[256];
	int X = GetSystemMetrics(SM_CXSCREEN);//иищем размер экрана по Х
	int Y = GetSystemMetrics(SM_CYSCREEN);//Ущем размер экрана по У
	int Num = GetSystemMetrics(SM_CMONITORS);//Ищем кол-во мониторов
	char strX[5] = "";
	char strY[5] = "";
	char strNum[2] = "";
	itoa(X, strX, 10);//перобразуем число в текст в 10 основании и сохраняем в strX
	itoa(Y, strY, 10);
	itoa(Num, strNum, 10);

	//соеденяем все в одну строчку(сообщение для клиента)
	strcpy(mess2, Descriprion1);
	strcat(mess2, strX);
	strcat(mess2, "X");
	strcat(mess2, strY);
	strcat(mess2, Descriprion2);
	strcat(mess2, strNum);



	//отправка
	send(Sockets[index], mess2, sizeof(mess2), NULL);

	//вывод времени отправки
	auto timesent = chrono::system_clock::now();
	time_t timeSent = chrono::system_clock::to_time_t(timesent);
	cout << "Отправка сообщения клиенту №" << index + 1 << " выполнена в " << ctime(&timeSent) << "\n";

}



int main(int argc, char* argv[]) {

	//устаовка русского языка на консоли
	setlocale(LC_ALL, "Russian");
	//Загрузка библиотеки 
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	HANDLE hMutex = CreateMutex(NULL, TRUE, L"MutexForServer2");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		cout << "Уже есть один экземпляр сервера!";
		exit(0);
	}

	//создание адреса
	SOCKADDR_IN addr;// структура для хранения адреса
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//ip - local host
	addr.sin_port = htons(1111);//незарезервированный хост
	addr.sin_family = AF_INET;//константа для интернет протокола

	//создание сокета
	SOCKET sListen = socket(
		AF_INET,// семейство интернет протоколов
		SOCK_STREAM,//протокод соединения
		NULL);

	//привязка адреса сокету
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	//ожидание соединения
	listen(sListen, MaxClientsQuantity);

	SOCKET newConnection;
	for (int i = 0; i < MaxClientsQuantity; i++) {

		//для каждого нового соединения открывается новый поток для отправки сообщений
		//в него передается функция отправки (LPTHREAD_START_ROUTINE)SentParameters и номер соединения (LPVOID)(i) по которому отправлять
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
	system("pause");
	return 0;
}
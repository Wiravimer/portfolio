// green_pea.cpp: определяет точку входа для приложения.

#include "stdafx.h"
#include "green_pea.h"

#define MAX_LOADSTRING 100
//=============================================================================================
INT_PTR CALLBACK   ViewDlgProc(HWND, UINT, WPARAM, LPARAM);//окно обзора информации
INT_PTR CALLBACK   GetDataDlgProc(HWND, UINT, WPARAM, LPARAM);//окно ввода
INT_PTR CALLBACK   DlgPercent(HWND, UINT, WPARAM, LPARAM);//окно обзора городов

INFO  obrabotka  (HWND);//функция чтение информации из полей ввода
INFO opros={ TEXT(""),0,0,0,0,0};//заполнить структуру 0 значениями


void Stroka(INFO_ZAPIS&);//функция вывода информации в Список (List Box) 


void Draw_Logo( HDC, RECT, POINT);//функция рисунка

INFO_ZAPIS  obrabotkaInfo( INFO );//переводит из INFO в INFO_ZAPIS для записи текста


const char* name = "1.bin";

int len = sizeof(INFO_ZAPIS);

//=============================================================================================


// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
 
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GREEN_PEA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GREEN_PEA));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GREEN_PEA));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GREEN_PEA);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//

//Главное меню
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_COMMAND://отклик кнопок в меню
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Разобрать выбор в меню:
			switch (wmId)
			{
				case IDM_VIEW: //кнопка обзора информации
					DialogBox(hInst, MAKEINTRESOURCE(IDD_VIEW), hWnd, ViewDlgProc);
					break; 

				case IDM_ABOUT: //о программе
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;

				case IDM_EXIT: 
					DestroyWindow(hWnd);
					break;

				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;

		case WM_PAINT:
		{ 
		hdc = BeginPaint(hWnd, &ps);
		//получить DC
		// TODO: добавьте любой код отрисовки...
		RECT rect;
		rect.top=300;
		rect.right=300;
		rect.bottom =450;
		rect.left= 10;
	    GetClientRect(hWnd,&rect);
	    POINT beg={0,0};

		Draw_Logo( hdc, rect, beg);
		EndPaint(hWnd, &ps);//Освободить DC
		}break;
	
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;


		case WM_COMMAND:
		switch (LOWORD(wParam))
		{    	
			case IDOK:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
                  
			case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

	}
	return (INT_PTR)FALSE;
}


//Диалоговое окно - Информация об опросе
INT_PTR CALLBACK  ViewDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

//static INFO_ZAPIS InfZapMasU[100]; // В этом массиве будет храниться информация об опросе
INFO_ZAPIS itemU,sortU;
static HWND hListBox;
static LOGFONT lf;
HFONT	hFont1;
int kol=0;//количество записей
 
fstream fail(name, ios::in | ios::out | ios::binary);




	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG://при открывания окна выводит информацию

			hListBox	=	GetDlgItem(hDlg,IDC_LIST1);

			lf.lfHeight = 30;//размер текста в listbox
			lstrcpy((LPWSTR)&lf.lfFaceName,TEXT("Courier"));//выбор шрифта

			hFont1 = CreateFontIndirect(&lf);

			SendMessage(hListBox, WM_SETFONT, (WPARAM)hFont1, TRUE);

			for (int i	= 0;fail.read((char*)&itemU,len); ++i)
			{SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)itemU.str);}

		return (INT_PTR)TRUE;



		case WM_COMMAND:
			switch (LOWORD(wParam))
			{    	
				case IDC_ADD:

				DialogBox((HINSTANCE)GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_GET),hDlg,GetDataDlgProc);

				if(*opros.city)       
				{	
					itemU = obrabotkaInfo(opros);
					fail.seekg(0,ios::end);
					fail.write((char*)&itemU, len);
					SendMessage	(hListBox,LB_ADDSTRING,0,(LPARAM)itemU.str);
				}
				break;


				case IDC_DELETE:
				{
     				int curItem = SendMessage(hListBox, LB_GETCURSEL, 0, 0);//определяем позицию удаления записи
					fstream copy("2.bin",ios::app| ios::binary);
					fail.clear();
					if (curItem  !=  LB_ERR )
					{
						SendMessage(hListBox, LB_DELETESTRING, curItem, 0);
						int i=0;
						while (true)
						{
							fail.seekg(len*i,ios::beg);
							fail.read((char*) &itemU,len);
							if(fail.eof()==true){break;}
							if(i!=curItem)
							{
								copy.write((char*) &itemU,len);
							}
							i++;
	
						}
						copy.close();
						fail.close();
						remove(name);
						rename("2.bin", name);
						fail.open(name, ios::in | ios::out | ios::binary);
				}
				else 
				{
					MessageBox(hDlg,
					TEXT("сначала надо выделить элемент списка"),
					TEXT("ОШИБКА"),
					MB_OK);
				}
										  
			}
			return (INT_PTR)TRUE;


                  
				case IDC_SORT:
				
				for(kol=0;fail.read((char*)&itemU,len);kol++){}	
				fail.clear();
				fail.seekg(0,ios::beg);
				
				for(int i2=0;i2<kol-1;i2++)
				{
			
					for(int i3=0,i=1,o=0;i3<kol-1;i3++,i++,o++)
					{
						fail.seekg(len*o,ios::beg);
						fail.read((char*) &itemU,len);
						fail.seekg(len*i,ios::beg);
						fail.read((char*) &sortU,len);

						if(itemU.nasilenie<sortU.nasilenie)
						{
							fail.seekg(len*i,ios::beg);
							fail.write((char*) &itemU,len);
							fail.seekg(o*len,ios::beg);
							fail.write((char*) &sortU,len);
					
						}
					}
				}

				//обновляем ListBox
				SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
				fail.seekg(0*len,ios::beg);
				for (int i	= 0;fail.read((char*)&itemU,len); ++i)
				{SendMessage(hListBox, LB_ADDSTRING,0,(LPARAM)itemU.str);}
				return (INT_PTR)TRUE;

						
				case IDC_PERCENT:  
					DialogBox(hInst, MAKEINTRESOURCE(IDD_PERCENT), hDlg, DlgPercent);
				return (INT_PTR)TRUE;

				case IDCANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
	
			}

	}
	fail.close();
	return (INT_PTR)FALSE;
}

//Диалоговое окно - Ввод информации
INT_PTR CALLBACK GetDataDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;


		case WM_COMMAND:
		switch (LOWORD(wParam))
		{    	
			case IDOK:

			opros = obrabotka(hDlg);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
                  
			case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

	}
	return (INT_PTR)FALSE;
}

//Диалоговое окно - Обзор городов >50%
INT_PTR CALLBACK DlgPercent(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

		INFO_ZAPIS iU;
		static HWND hListBox;
		static LOGFONT lf;
		HFONT	hFont1;
		int percent;
		fstream per(name, ios::in | ios::out | ios::binary);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		

		case WM_INITDIALOG:
			hListBox	=	GetDlgItem(hDlg,IDC_LIST1);

			lf.lfHeight = 30;//размер текста в listbox
			lstrcpy((LPWSTR)&lf.lfFaceName,TEXT("Arial"));//выбор шрифта

			hFont1 = CreateFontIndirect(&lf);
			SendMessage(hListBox, WM_SETFONT, (WPARAM)hFont1, TRUE);

			for (int i	= 0;per.read((char*)&iU,len); ++i)
			{	
				percent = (iU.za*100)/iU.nasilenie;
				if(percent>50){SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)iU.InfoThar.city);}
			}
			per.close();

			return (INT_PTR)TRUE;


		case WM_COMMAND:
		switch (LOWORD(wParam))
		{    	
			case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

	}
	return (INT_PTR)FALSE;
}
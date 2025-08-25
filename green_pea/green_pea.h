#pragma once

#include "resource.h"
#include <fstream>
using namespace std;

#define NC 20 // город
#define NS 20 // жителей в городе
#define NI 20 //количество опрошеных
#define NT 20 //довер€ющих
#define NN 20 //не довер€ющих 
#define ND 20 //сомневающиес€



#define NLINE (NC+NS+NI+NT+NN+ND+1)//ќЅў»… –ј«ћ≈– 
#define MAX 2*NLINE //max размер хранимой информации

extern int len;

//куда будем записывать данные с полей ввода
struct INFO { 	
				TCHAR city[NC];		// город
				UINT  sitizen;		// жителей в городе
				UINT  interviewee;	//количество опрошеных
				UINT  trust;		//довер€ющих
				UINT  notTrust;		//не довер€ющих 
				UINT  doubt;		//сомневающиес€
			};

//ƒелаем из структуры INFO полность текстувую структуру
struct INFO_THAR {  	
				TCHAR  city[NC];			// город
				TCHAR  sitizen[NS];			// жителей в городе
				TCHAR  interviewee[NI];		//количество опрошеных
				TCHAR  trust[NT];			//довер€ющих
				TCHAR  notTrust[NN];		//не довер€ющих 
				TCHAR  doubt[ND];			//сомневающиес€
			   };


//структура дл€ вывода информации
struct INFO_ZAPIS{ 	
					int nasilenie;		//количество наcилени€ дл€ сортировки 
					int za;				//количество наcилени€ «ј
					INFO_THAR InfoThar;	//что будем записывать
                	TCHAR str[MAX];		//–азмер записи      
				 };

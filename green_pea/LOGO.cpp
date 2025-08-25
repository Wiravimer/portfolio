#include "stdafx.h"

int strlen(TCHAR* str)
{ int len;
   for ( len=0;*str;len++,str++);
 return len;
}

void Draw_Logo( HDC hDC,RECT rect,POINT beg)
{
	const int yCl=(rect.bottom	- rect.top);
	
	const int xCl=(rect.right	- rect.left);
	
	const double dXPix	= xCl/18;
	const double dYPix	= yCl/16;

	  
	SetMapMode(hDC,MM_ISOTROPIC);
	SetWindowExtEx(hDC,xCl,yCl,NULL);
	SetViewportExtEx(hDC,xCl,-yCl,NULL);
	SetViewportOrgEx(hDC,beg.x,yCl-beg.y,  NULL);



	
	 //палитра
	 COLORREF myCol[]={ 
						RGB(255,255,255), //0 белый
						RGB(133,195,37),  // 1 стебель
						RGB(161,207,92), //2 горошек
						RGB(203,203,203), //3 тень 	  
						RGB(57,112,148), //4 текст
						RGB(0x80,0x80,0x80)//5
					   };


	TCHAR* line[] ={ TEXT("Институт социологически исследований")};



	static LOGFONT lf;
	lf.lfPitchAndFamily	= FIXED_PITCH | FF_MODERN;// Шаг шрифта DEFAULT_PITCH по умолчанию
	lf.lfItalic			= TRUE; // запрашивается курсивный шрифт, если TRUE
	lf.lfWeight			= FW_BOLD;
	lf.lfHeight			= 100;// жирность шрифта 0(FW_DONTCARE),100,200,... 700,..,900
							// значение 0 предписывает выбрать вес по умолчанию
	lf.lfCharSet		= RUSSIAN_CHARSET;// код используемого набора символов


	HPEN hPen	= CreatePen(PS_SOLID,1,myCol[0]);
	HPEN hOldPen	= (HPEN)SelectObject(hDC,hPen);

	HBRUSH brush;

	HFONT hFont0	= CreateFontIndirect(&lf);
	HFONT hOldFont	= (HFONT)SelectObject(hDC,hFont0);
//====================================================================================================================


		SetTextColor(
 hDC, // дескриптор контекста устройства
myCol[4] ); // цвет 


		TextOut(
 hDC, // дескриптор контекста устройства
0*dXPix , // x-координата начала вывода текста
 4*dYPix, // y-координата начала вывода текста
line[0], // указатель на строку текста
strlen(line[0])); // количество символов для вывода



DeleteObject(SelectObject(hDC,hFont0));










brush=CreateSolidBrush(myCol[2]);
SelectObject(hDC,brush);
Ellipse(hDC, 3.8*dXPix,11.6*dYPix,5.4*dXPix,9*dYPix);
DeleteObject(brush);

brush=CreateSolidBrush(myCol[2]);
SelectObject(hDC,brush);
Ellipse(hDC, 5.6*dXPix,10.6*dYPix,7.3*dXPix,7.8*dYPix);
DeleteObject(brush);

brush=CreateSolidBrush(myCol[2]);
SelectObject(hDC,brush);
Ellipse(hDC, 7.6*dXPix,10.8*dYPix,9.5*dXPix,7.6*dYPix);
DeleteObject(brush);

brush=CreateSolidBrush(myCol[2]);
SelectObject(hDC,brush);
Ellipse(hDC, 9.8*dXPix,11.2*dYPix,11.5*dXPix,8.3*dYPix);
DeleteObject(brush);

brush=CreateSolidBrush(myCol[2]);
SelectObject(hDC,brush);
Ellipse(hDC, 11.7*dXPix,12.1*dYPix,13.5*dXPix,9.1*dYPix);
DeleteObject(brush);

POINT p1[]	= {	
				{9*dXPix,   5.5*dYPix},		

				{ 3.6*dXPix,    9.6*dYPix},	
				{ 5.3*dXPix,    8.9*dYPix},	
				{ 7.5*dXPix,    8.5*dYPix},	
				{ 9.6*dXPix,    8.6*dYPix},	
				{ 11.7*dXPix,   9.4 *dYPix},	
				{ 14*dXPix,    10*dYPix},	

				{9*dXPix,   5.5*dYPix},
			  };
brush=CreateSolidBrush(myCol[0]);
SelectObject(hDC,brush);
	Polygon(hDC, p1,sizeof(p1)/sizeof(POINT));
DeleteObject(brush);



brush=CreateSolidBrush(myCol[3]);
SelectObject(hDC,brush);
Ellipse(hDC, 2.9*dXPix,6.5*dYPix,15.9*dXPix,5.5*dYPix);
DeleteObject(brush);


	hPen= CreatePen(PS_SOLID,1,myCol[1]);
	DeleteObject(SelectObject(hDC,hPen));


POINT p2[]	= {	
				{2*dXPix,   11*dYPix},			//1		
				{2.5*dXPix,   10*dYPix},		//2
				{3.1*dXPix,   8.9*dYPix},		//3
				{4.1*dXPix,   7.9*dYPix},		//4
				{5.1*dXPix,   7*dYPix},			//5
				{6.2*dXPix,6.6*dYPix},			//6
				{7*dXPix,6.5*dYPix},			//7
												//8
				{8*dXPix,   6.4*dYPix},			//9			
				{8.8*dXPix,   6.3*dYPix},		//10

				{9.7*dXPix,   6.5*dYPix},			//11		
				{11.1*dXPix,   7*dYPix},		//12
				{12.2*dXPix,   7.5*dYPix},		//13
				{13.9*dXPix,   8.8*dYPix},		//14
				{15*dXPix,   10*dYPix},			//15
				{15.6*dXPix,10.4*dYPix},			//16
				{16*dXPix,10.5*dYPix},			//17
				{17*dXPix,   10*dYPix},			//18
				{16*dXPix,   12*dYPix},			//19			
				{15.3*dXPix,   12.7*dYPix},		//20

				{14.6*dXPix,   13.2*dYPix},			//21		
				{13.7*dXPix,   13.6*dYPix},		//22
				{13*dXPix,   13.7*dYPix},		//23
				{11.6*dXPix,   13.5*dYPix},		//24
				{9.1*dXPix,  12.4*dYPix},			//25
				{8*dXPix,12*dYPix},			//26
				{7*dXPix,12*dYPix},			//27
				{8*dXPix,   11.3*dYPix},			//28
				{9*dXPix,   11.1*dYPix},			//29			
				{10*dXPix,   11.5*dYPix},		//30

				{11.5*dXPix,   12.1*dYPix},			//31		
				{12.8*dXPix,   12.5*dYPix},		//32
				{13.6*dXPix,   12.4*dYPix},		//33
				{14.5*dXPix,   12*dYPix},		//34
				{15.3*dXPix,   11*dYPix},			//35
				{14*dXPix,10*dYPix},			//36
				{13*dXPix,9.5*dYPix},			//37
				{11.5*dXPix,   9*dYPix},			//38
				{9.6*dXPix,   8.3*dYPix},			//39			
				{8*dXPix,   8*dYPix},		//40

				{6.5*dXPix,   8.1*dYPix},			//41		
				{5*dXPix,   8.5*dYPix},		//42
				{3.6*dXPix,   9.2*dYPix},		//43
				{2.8*dXPix,   10*dYPix},		//44
				{2*dXPix,   11*dYPix},			//45

				

			  };
brush=CreateSolidBrush(myCol[1]);
SelectObject(hDC,brush);
	Polygon(hDC, p2,sizeof(p2)/sizeof(POINT));
DeleteObject(brush);




//---------------------------------------------------------------------------------------------------------------------
			//hPen	= CreatePen(PS_DOT,1,RGB(0,0,0));//цвет сетки
			//DeleteObject(SelectObject(hDC,hPen));
			//for (int i=0;i<=20;i++)
			//{	//сетка
			//	POINT goz[]	= { 
			//						{0*dXPix,   i*dYPix},
			//						{20*dXPix,   i*dYPix}
			//				  };	
			//	POINT ver[]	= { 
			//					{i*dXPix,   0*dYPix},
			//					{i*dXPix,   20*dYPix}
			//				  };

			//	//ресуем сетку
			//	Polyline(hDC, goz,sizeof(goz)/sizeof(POINT));
			//	Polyline(hDC, ver,sizeof(ver)/sizeof(POINT));
			//}

	}


	
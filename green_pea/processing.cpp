#include "stdafx.h"
#include "green_pea.h"

//чтение информации из полей ввода
INFO  obrabotka  (HWND hDlg)
{	   
		INFO zap;   
		TCHAR buf[500]=TEXT("");       
		BOOL 	lpCity=TRUE,lpSitizen,lpInterviewee,lpTrust,lpNotTrust,lpDoubt;


		GetDlgItemText(hDlg,IDC_CITY,zap.city,20);
		if(*zap.city== 0)
		{
			wcscpy(buf,  TEXT("  ошибка ввода названия города!"));
			lpCity=FALSE;
		}



		zap.sitizen  =  GetDlgItemInt(hDlg,IDC_CITIZEN,&lpSitizen,FALSE);
        if (lpSitizen ==FALSE||zap.sitizen <0)
		{wcscpy(buf+wcslen(buf),  TEXT("  ошибка ввода числа жителей!"));}

		zap.trust  =  GetDlgItemInt(hDlg,IDC_TRUST,&lpTrust,FALSE);
		if (lpTrust ==FALSE||zap.trust  <0)
		{wcscpy(buf+wcslen(buf),  TEXT("  ошибка ввода числа согласных!"));}

		zap.notTrust  =  GetDlgItemInt(hDlg,IDC_NOT_TRUST,&lpNotTrust,FALSE);
        if (lpNotTrust ==FALSE||zap.notTrust <0)
		{wcscpy(buf+wcslen(buf),  TEXT("  ошибка ввода числа несогласных!"));}

		zap.doubt =  GetDlgItemInt(hDlg,IDC_DOUBT,&lpDoubt,FALSE);
        if (lpDoubt ==FALSE||zap.doubt  <0)
		{wcscpy(buf+wcslen(buf),  TEXT("  ошибка ввода числа сомневающихся!"));}

		zap.interviewee=zap.trust+zap.notTrust+zap.doubt;
		if(zap.interviewee>zap.sitizen)
		{wcscpy(buf+wcslen(buf),  TEXT("  Опрошеных больше чем жителей в городе"));}

		if (lpCity==FALSE||zap.sitizen<0||zap.interviewee<0||zap.trust<0||zap.notTrust<0||zap.doubt<0||zap.interviewee>zap.sitizen)
		{ 
			MessageBox(hDlg,buf, TEXT("Сообщение об ошибке ввода"), MB_OK);

			// установки признака пустой не введенной информации         
			*zap.city = 0;
			zap.sitizen = 0;
			zap.interviewee = 0;
			zap.trust = 0;
			zap.notTrust = 0;
			zap.doubt = 0;
		} 

return  zap;
} 

//сохраняет строку
void Stroka(INFO_ZAPIS& zap)
{   
// запись информации из  трех строк данного  zap.InfoThar
//в одну строку zap.str  
	
swprintf(zap.str, 
		TEXT("%-10s║%-8s║%-8s║%-8s║%-8s║%-5s"),
		zap.InfoThar.city,
		zap.InfoThar.sitizen,
		zap.InfoThar.interviewee,
		zap.InfoThar.trust,
		zap.InfoThar.notTrust,
		zap.InfoThar.doubt);
}

//переодит все в строку
INFO_ZAPIS  obrabotkaInfo( INFO studBeg )
{
INFO_ZAPIS u;
wcscpy(u.InfoThar.city,studBeg.city);
swprintf(u.InfoThar.sitizen,TEXT("%d"),studBeg.sitizen);
swprintf(u.InfoThar.interviewee,TEXT("%d"),studBeg.interviewee);
swprintf(u.InfoThar.trust,TEXT("%d"),studBeg.trust);
swprintf(u.InfoThar.notTrust,TEXT("%d"),studBeg.notTrust);
swprintf(u.InfoThar.doubt,TEXT("%d"),studBeg.doubt);

Stroka (u);
u.nasilenie=studBeg.sitizen;
u.za=studBeg.trust;
return u;
}
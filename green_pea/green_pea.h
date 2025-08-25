#pragma once

#include "resource.h"
#include <fstream>
using namespace std;

#define NC 20 // �����
#define NS 20 // ������� � ������
#define NI 20 //���������� ���������
#define NT 20 //����������
#define NN 20 //�� ���������� 
#define ND 20 //�������������



#define NLINE (NC+NS+NI+NT+NN+ND+1)//����� ������ 
#define MAX 2*NLINE //max ������ �������� ����������

extern int len;

//���� ����� ���������� ������ � ����� �����
struct INFO { 	
				TCHAR city[NC];		// �����
				UINT  sitizen;		// ������� � ������
				UINT  interviewee;	//���������� ���������
				UINT  trust;		//����������
				UINT  notTrust;		//�� ���������� 
				UINT  doubt;		//�������������
			};

//������ �� ��������� INFO �������� ��������� ���������
struct INFO_THAR {  	
				TCHAR  city[NC];			// �����
				TCHAR  sitizen[NS];			// ������� � ������
				TCHAR  interviewee[NI];		//���������� ���������
				TCHAR  trust[NT];			//����������
				TCHAR  notTrust[NN];		//�� ���������� 
				TCHAR  doubt[ND];			//�������������
			   };


//��������� ��� ������ ����������
struct INFO_ZAPIS{ 	
					int nasilenie;		//���������� ��c������ ��� ���������� 
					int za;				//���������� ��c������ ��
					INFO_THAR InfoThar;	//��� ����� ����������
                	TCHAR str[MAX];		//������ ������      
				 };

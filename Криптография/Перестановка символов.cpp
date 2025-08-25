#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

string text("столбцевойперестановочныйшифр");
//string text("Я памятник себе воздвиг нерукотворный, к нему не зарастёт народная тропа");
string code(string, int);
string decode(string, int);

void main()
{	setlocale(LC_ALL, "rus");
	int key = 6;
	//string text;cout<<"Введите текст: "; cin >> text;code(text, key, 1);
	//code(text, key);
	decode(code(text, key),key);
	
	cout << endl << endl;
	system("pause");
}

string code(string text, int k)
{
	vector<string> table;
	table.reserve(0);
	int len = text.size();
	int pointer=0, pos=0, count=k;
	int tmp1=0, tmp2=0;
	string str;

			
		while(pos<len)
		{
			table.push_back(text.substr(pos, count));
			pos+=k;
			tmp1++;
		}
	

	for(int i=0; i<k; i++)
	{
		for(int j=0; j<tmp1; j++)
		{
			if(tmp2 < len)
			{
				str.push_back(table[j][i]);
				//cout<<table[j][i];
				tmp2++;
			}
		}
		
	}
	cout<<str<<endl;
	return str;

}



string decode(string text, int k)
{
	vector<string> table;
	table.reserve(0);
	int len = text.size();
	int pointer=0, pos=0, count;
	int tmp1=0, tmp2=0;
	string str;
	float tmp3 = len/k;
	
		//k=ceil(tmp3);
		count=k-1;
		while(pos<len)
		{
			table.push_back(text.substr(pos, count));
			pos+=k-1;
			tmp1++;
		}


		for(int i=0; i<k; i++)
	{
		for(int j=0; j<tmp1; j++)
		{
			if(tmp2 < len)
			{
				str.push_back(table[j][i]);
				//cout<<table[j][i];
				tmp2++;
			}
		}
		
	}

	cout<<str<<endl;
	return str;
}

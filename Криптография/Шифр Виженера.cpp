#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string text("HELLO");
string key ("XMCKL");
string alphabetU("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
int  alphabet_size = alphabetU.length();
string str;

int find(char);


void main()
{	setlocale(LC_ALL, "rus");
	int t,k,c;
	
	for(int i = 0; i < text.length(); i++)
	{
		t=find((char)text[i]);
		k=find((char)key[i]);
		c=(t + k) % alphabet_size;
		

		str.push_back(alphabetU[c]);
		cout<<str[i];
	}
	cout<<endl;

	for(int i = 0; i < text.length(); i++)
	{
		t=find((char)str[i]);
		k=find((char)key[i]);
		if(t-k < 0) c=(t-k) % alphabet_size + alphabet_size;
		else c=(t-k) % alphabet_size;

		text[i]=(alphabetU[c]);
		cout<<text[i];
		
	}
	
	
	cout << endl << endl;
	system("pause");
}

int find(char num)
{
	for(int i = 0; i < alphabet_size; i++)
		if(num == alphabetU[i])
			return i;
	return -1;
}


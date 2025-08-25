#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string text("HELLO");
string key ("XMCKL");
string alphabetU("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
int  alphabet_size = alphabetU.length();
string cypher;

int find(char);
string encode_pad(string);
string decode_pad(string);
string xor(string);


void main()
{	setlocale(LC_ALL, "rus");
	
	cout<<"TEXT: "<<text<<endl;
	decode_pad(xor(xor(encode_pad(text))));
	
	cout << endl << endl;
	system("pause");
}


string encode_pad(string text)
{
	int t,k,c;
	string str;

	cout<<"enPAD: ";

	for(int i = 0; i < text.length(); i++)
	{
		t=find((char)text[i]);
		k=find((char)key[i]);
		c=(t + k) % alphabet_size;

		str.push_back(alphabetU[c]);
		cout<<str[i];
	}
	cout<<endl;
	return str;
}

string decode_pad(string text)
{
	int t,k,c;
	string str;

	cout<<"dePAD: ";

	for(int i = 0; i < text.length(); i++)
	{
		t=find((char)text[i]);
		k=find((char)key[i]);
		if(t-k < 0) c=(t-k) % alphabet_size + alphabet_size;
		else c=(t-k) % alphabet_size;

		str.push_back(alphabetU[c]);
		cout<<str[i];
		
	}
	cout<<endl;
	return str;
}

int find(char num)
{
	for(int i = 0; i < alphabet_size; i++)
		if(num == alphabetU[i])
			return i;
	return -1;
}

string xor(string text)
{
	string str;
	cout<<"XOR: ";

	for(int i = 0; i < text.length(); i++)
	{
		str.push_back( (text[i] ^ key[i % key.length()]));
		cout<<str[i];
	}
	cout<<endl;

	return str;
}

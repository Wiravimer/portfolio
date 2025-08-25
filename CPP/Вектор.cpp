#include <iostream>
#include <math.h>
using namespace std;

class DVector
{
	double *data;
	int size;

public:

	DVector()
	{ 
		data = 0;
		size = 0; 
	}

	DVector(const DVector &external)
	{ 
		this->size = external.size;

		this->data = new double[external.size];
		for (int i = 0; i < external.size; i++)
		{	
			this->data[i] = external.data[i];
		}
	}

	DVector(int Size)
	{ 
		data = new double[Size];
		for(int i=0;i<Size;i++)
		{
			data[i]=0.0; 
			size = Size;
		}
	}


	~DVector()
	{ 
		delete [] data;
	}


	double& operator [](int);
	friend ostream& operator << (ostream&,DVector&);
	DVector& operator = (DVector);
	friend DVector operator*(float,DVector);
	friend DVector operator/(DVector,float);
	friend DVector operator+(DVector,DVector);
	friend float min(DVector &a);
};




double& DVector::operator[] (int a)
{
	return data[a];
}

ostream& operator << (ostream & vivod, DVector &a)
	{
		vivod << '[';
		for (int i=0; i<a.size; i++)
		{
			vivod << a[i];
			if(i<a.size-1){cout<<' ';}
		}
		vivod << ']';
		return vivod;
	}

DVector& DVector::operator = (DVector external)
{
	this->size = external.size;
	delete [] this->data;

	this->data = new double[external.size];
	for (int i = 0; i < external.size; i++)
	{	
		this->data[i] = external.data[i];
	}

	return *this;
}

DVector operator * (float number,DVector a)
{
	for (int i=0; i < a.size; i++)
	{
		a.data[i] = a.data[i]*number;
	}
	return a;
}

DVector operator / (DVector a,float number)
{
	for (int i=0; i < a.size; i++)
	{
		a.data[i] = a.data[i]/number;
	}
	return a;
}

DVector operator + (DVector l,DVector r)
{
	int size;
	if(l.size>r.size)
	{size = l.size;}
	else size = r.size;

	double *vector = new double[size];

	for (int i=0; i < size; i++)
		vector[i]=l.data[i]+r.data[i];

		DVector a;
		a.data = vector; 
		a.size = size;
		return a;
}


float min(DVector &a)
{
	float temp=a.data[0];
	for(int i=1; i<a.size; i++)
	{
		if(temp>a.data[i]){temp=a.data[i];}
	}
	return temp;
}



void main()
{setlocale(LC_ALL, "rus");

DVector Y(2),V(4),U(4);
float z;

for (int i=0; i < 4; i++)
{
	V[i] = i+2;
	U[i] = i+1;
}

cout<<"Y:"<<Y<<endl;
cout<<"V:"<<V<<endl;
cout<<"U:"<<U<<endl;


Y=U[3]*V+U/V[0];
z=min(U)*U[1];

cout<<endl;
cout<<"Y:"<<Y<<endl;
cout<<"z="<<z<<endl;

cout<<endl;system("pause");
} 




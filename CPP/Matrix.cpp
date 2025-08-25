#include <iostream>
using namespace std;


class DMatrix
{
double** data;
int line;
int colum;

public:

	DMatrix()
	{
		data=0;
		line=colum=0;
	}

	DMatrix(const DMatrix &other)
	{ 
		this->line = other.line;
		this->colum = other.colum;

		this->data = new double*[other.line];
		for(int k=0; k<line;k++)
		{
			data[k] = new double[colum];
		}
		for (int i = 0; i < other.line; i++)
		{	
			for (int j = 0; j < other.colum; j++)
			{
				this->data[i][j] = other.data[i][j];
			}
		}
	}

	DMatrix(int col,int row)
	{ 
		data = new double*[row];
		for(int i=0; i<row;i++)
		{
			data[i] = new double[col];
		}

		for (int i = 0; i < row; i++)
		{	
			for (int j = 0; j < col; j++)
			{
				data[i][j]=0.0; 
			}
		}

		colum = col;
		line=row;
	}


	~DMatrix()
	{
		for (int i = 0; i < line; i++)
			delete[]data[i];
		delete[]data;
	}

	

	double*& operator[](int);
	DMatrix& operator = (DMatrix );
	friend ostream& operator << (ostream&,DMatrix&);
	friend DMatrix operator * (int, DMatrix);
	friend DMatrix operator + (DMatrix,DMatrix);
};


	double*& DMatrix::operator[](int r)
	{
		return data[r];
	}

DMatrix& DMatrix::operator = (DMatrix a)
{
	if (this == &a) return *this;

	for (int i = 0; i < line; i++)
			delete[]data[i];
		delete[]data;

	line=a.line;
	colum=a.colum;

	data = new double*[line];
	for(int i=0; i<line;i++)
	{
		data[i] = new double[colum];
	}

	for(int i=0; i<line; i++)
	{
		for(int j=0; j<colum; j++)
		{
			data[i][j]=a.data[i][j];
		}
	}

	return *this;
}

ostream& operator << (ostream & vivod, DMatrix &a)
{
	vivod<<endl;
	for (int i=0; i<a.line; i++)
	{
		vivod << '|';
		for (int j=0; j<a.colum; j++)
		{
			vivod << a.data[i][j];
			if(j<a.colum-1){vivod<<' ';}
		}
		vivod << '|'<<endl;
	}
	
	return vivod;
}

DMatrix operator * (int number,DMatrix a)
{
	for (int i=0; i < a.line; i++)
	{
		for (int j=0; j<a.colum; j++)
		{
			a.data[i][j] = a.data[i][j]*number;
		}
	}
	return a;
}

DMatrix operator + (DMatrix l,DMatrix r)
{

	for (int i=0; i < l.line; i++)
	{
		for (int j=0; j<l.colum; j++)
		{
			l.data[i][j] = l.data[i][j]+r.data[i][j];
		}
	}
		return l;
}

void main()
{setlocale(LC_ALL, "rus");
	int c,r,x;

cout<<"Введите размерность матриц"<<endl;
cout<<"Столбцы: ";cin>>c;
cout<<"Строки: ";cin>>r;
cout<<"Введите x: ";cin>>x;
cout<<endl;

DMatrix V(c,r),U(c,r),Z,Y;
for (int i = 0; i < r; i++)
		{	
			for (int j = 0; j < c; j++)
			{
				double d=i;
				V[i][j] = rand()%10;
				U[i][j] = rand()%10;
			}
		}

cout<<"V: "<<V<<endl;
cout<<"U: "<<U<<endl;
cout<<endl;

Y=x*V+2*U;
Z=V[1][2]*U+U[2][1]*V;

cout<<"Y: "<<Y<<endl;
cout<<"Z: "<<Z<<endl;

cout<<endl;system("pause");
}

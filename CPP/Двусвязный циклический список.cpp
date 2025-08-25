#include <iostream>
#include <math.h>
using namespace std;

class Element 
{
public:
	int data;
	Element* next;
	Element* prev;
	Element(int setData, Element* nextElm, Element* prevElm)
	{
		data = setData;
		next = nextElm;
		prev = prevElm;
	}

	friend class List;
	friend class Iterator;
};

class List
{
public:
	List();
	~List();
	List(const List&);
	int peek() { return head->data; }
	void addT(int );
	void addH(int );
	void delT();
	void delH();
	void clear();
	friend ostream& operator<<(ostream&, List&);
	List& operator=(List&);
	friend class Iterator;
private:
Element* head;
Element* tail;
int size;
};


class Iterator
{
List* D;
Element* cur;
public:
Iterator(List d)
{
D = new List();
*D = d;
cur = D->head;
}
int peek() { return cur->data; }
void next() { cur = cur->next; }
void prev() { cur = cur->prev; }
void reset() { cur = D->head; }
Element* current() { return cur; }
Element* isEmpty() { if (cur == nullptr) return 0; else return cur; }
void set(Element* p = 0) { cur = p; }
};

List::List()
{
	size=0;
	head=tail=0;
}

List::~List()
{
	clear();
}

List::List(const List& lst)
{
	size=0;
	head=tail=0;
	Element* cur = lst.head;
	while(	size != lst.size)
	{
		addT(cur->data);
		cur=cur->next;
	}

}

void List::addT(int value=rand())
{
	if(head == 0)
	{
		head = new Element (value, head, head);
		head->next = head;
		head->prev = head;
		tail = head;
	}
	else if(size==1)
	{		
		
			tail = new Element (value, head, head);
			head->next = tail;
			head->prev = tail;
	}
	else 
	{
			tail->next = new Element (value, head, tail);
			tail = tail->next;
			head->prev = tail;

	}
	size++;
}

void List::addH(int value=rand())
{
	if(head == 0)
	{
		head = new Element (value, head, head);
		head->next = head;
		head->prev = head;
		tail = head;
	}
	else if(size==1)
	{		
		
			head = new Element (value, tail, tail);
			tail->next = head;
			tail->prev = head;
	}
	else 
	{
			head->prev = new Element (value, head, tail);
			head = head->prev;
			tail->next = head;
	}
	size++;
}

void List::delT()
{
	Element *temp = tail;
	tail = tail->prev;
	tail->next = head;
	head->prev = tail;
	delete temp;
	size--;
}

void List::delH()
{
	Element *temp = head;
	head = head->next;
	tail->next = head;
	head->prev = tail;
	delete temp;
	size--;
}

void List::clear()
{
	while(size!=0)
	{
		delH();
	} 
	head=0;
	tail=0;
}

ostream& operator<<(ostream& cout, List& a)
{
	do	
	{
		if(a.head==0){return cout;}
		cout << a.head->data << ' ';
		a.head = a.head->next;
	} while (a.head != a.tail->next);
	
	return cout;
}

List& List::operator=(List& lst)
{
	Element* cur = lst.head;
	this->clear();

	do {
		addT(cur->data);
		cur = cur->next;
	} while (cur != lst.head);

	return *this;
}

void main()
{setlocale(LC_ALL, "rus");

List lst1;
List lst2;
int n1,n2;
cout<<"Количество элементов для 1го списка: ";cin>>n1;
cout<<"Количество элементов для 2го списка: ";cin>>n2;
for(int i=1; i<=n1;i++)
{
	lst1.addH(i);
	if(i!=1){i++;lst1.addT(i);}
}

for(int i=0; i<n2;i++)
{
	lst2.addH(rand()%10);
}

List lst3(lst2);
cout<<"Список1: "<<lst1<<endl;
cout<<"Список2: "<<lst2<<endl; 
cout<<"Список3: "<<lst3<<endl; 

lst2=lst1;

cout<<endl;
cout<<"Список1: "<<lst1<<endl;
cout<<"Список2: "<<lst2<<endl; 
cout<<"Список3: "<<lst3<<endl;

cout<<endl;system("pause");
} 

#include <iostream>
using namespace std;

class Element
{
	int data;
	Element* next;
	
public:
	Element(int data, Element* next = nullptr)
	{
		this->data = data;
		this->next = next;
	}

	int Data() { return data; }
	Element* Next() { return next; }
	
	friend class List;
	friend class Iterator;
};

class List
{
public:
	List();
	~List();
	int peek() { return last->data; }
	Element* search(int a);
	void add(int a);
	void del(int a);
	friend ostream& operator<<(ostream&, List&);
	List& operator=(List& s);
	List(const List&);
	friend class Iterator;
private:
	Element* last;
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
		cur = D->last;
	}
	int peek() { return cur->data; }
	void next() { cur = cur->next; }
	void reset() { cur = D->last; }
	Element* current() { return cur; }
	Element* isEnd() {
		if (cur == D->last) return 0;
		else return cur;
	}
	void set(Element* p = 0) { cur = p; }
};

ostream& operator<<(ostream& cout, List& a)
{
	Element* current = a.last->Next();
	do	{
		cout << current->Data() << ' ';
		current = current->Next();
	} while (current != a.last->Next());
	return cout;
}

List::List()
{
	last = nullptr;
}

List::~List()
{
	Element* current = last;
	do	{
		Element* current_last = current;
		current = current->next;
		delete current_last;
	} while (current != last);
}


void List::del(int a)
{
	Element* p = search(a);
	if (p->next->data == a)
	{
		Element* q = p->next;
		p->next = q->next;
		delete q;
	}
}


void List::add(int value)
{
	if (last == nullptr)
	{
		last = new Element(value, nullptr);
		last->next = last;
	}
	else
	{
		Element* tmp = search(value);
		if (tmp == last && last->data < value)
		{
			last->next = new Element (value, last->next);
			last = last->next;
		}
		else 
		{
			tmp->next = new Element(value, tmp->next);
		}
	}
}

Element* List::search(int value)
{
	Element* tmp1 = last;
	Element* tmp2 = last->next;
	
	while(tmp2->data < value)
	{
		tmp1 = tmp2;
		tmp2 = tmp2->next;
		if (tmp2 == last->next) {return tmp1;}
	}
	return tmp1;
}

List& List:: operator=(List& tmp)
{
	if (this == &tmp) {return *this;}
	this->~List();

	Element* cur = tmp.last;
	do 
	{
		add(cur->data);
		cur = cur->next;
	} while (cur != tmp.last);
	return *this;
}

List::List(const List& list1)
{
	last = nullptr;
	Element* cur = list1.last;
	do
	{
		add(cur->data);
		cur = cur->next;
	} while (cur != list1.last);
}

int find(int el, List& D1)
{
	Iterator I1(D1);
	int el1 = I1.peek();
	I1.reset();
	do {
		if (el == el1) return 1;
		el1 = I1.peek();
		I1.next();
	} while (I1.isEnd() != 0);
	if (el == el1) return 1;
	return 0;
}


void main()
{
	List lst;
	for (int i = 0; i < 10; i++)
	{
		lst.add(rand() % 10 );
	}

	cout << lst << endl << endl;
	Iterator I(lst);

	List D1;
	int el = I.peek();
	D1.add(el);
	for (I.next(); I.isEnd() != 0; I.next())
	{
		el = I.peek();
		if (find(el, D1) == 0)
			D1.add(el);
	}
	cout << D1;
	cout<<endl;system("pause");
}
//реализация оносвязного списка
#include <iostream>
using namespace std;


template<typename T>//создаем шаблонный класс
class List//класс списка
{
public:

	List();
	~List();

	void removeAt(int);//удаление элемента по индексу
	void insert(T, int);//добавления элемента по индексу
	void push_front(T);//добавить элемент в начало списка
	void clear();//удаляет весь список
	/* pop_front(); можно таже использовать для освобождения динамической памяти (удалить весь список) попутно выполним 2 задачи */
	void pop_front();//удаляет самый 1й элемент 
	void push_back(T data);//добавление элемента(данные) в конец списка push_back-затолкать назад
	int GetSize(){return Size;}//это "геттер" 

	T& operator[](const int index);//для итерации по списку(возращаем через ссылку чтобы была возмоно изменять)

private:

	//об классе Node знает только класс List и все взаемодействие с Node будет через List
	template<typename T>//создаем шаблонный класс
	class Node//класс элемента списка Node-узел
	{
	public:
		Node* pNext;//адрес следующего элемента
		T data;
		
		Node(T data=T(), Node* pNext=nullptr)//конструктор присваивания с значениями по умолчанию(Например последней элемент мы будем передовать только данные без указания адреса на следующий элемент)
		{
			this->data=data;
			this->pNext=pNext;
		}
	};

	//используем указатель пому ,что все элементы односвязного списка будут выделяться в денамической памяти
	Node<T>* head;//чтобы List знал есть ли первый элемент списка  head-голова
	int Size;//количество элементов в списке
};

//List:: показывает к какому классу относить метод/коструктор/деструктор
//<T> шаблонный тип данных
	template<typename T>
	List<T>::List()//конструктор по умолчанию
	{
		Size=0;
		head=nullptr;
	}

	template<typename T>
	List<T>::~List()//деструктор
	{
		clear();
	}

	template<typename T>
	void List<T>::push_back(T data)
	{
		//добавление самого 1го элемента
		if(head==nullptr)//проверяет пустой ли этот элемент(если пустой то будет указывать на NULL)
		{
			/* В денамической памяти создаем новый объект типа Node, 
			туда помещаем наши данные и в head помещаем указатель на этот адрес памяти*/

			head= new Node<T>(data);//создать новый элемент Node и бередать в конструктор данные
		}
		//добавление следующего элемента
		else
		{
			/* Текущий элемент с которым мы работаем мы присваиваем адрес нашего head 
			и смотрим у текущего нашего элемента поле который указывает на следующий адрес 
			если оно не NULL ,то мы должны присвоить этот следующий адрес текущему элементу */

			Node<T>* current = this->head;//current и head одинаковые

			while(current->pNext != nullptr)//перемещение к последниму элементу
			{
				current=current->pNext;
			}

			/* создаем новый элемент(новую Node) и присваиваем адрес динамической памяти этой ноде указателю pNext 
			который указывал на NULL*/

			current->pNext = new Node<T>(data);
		}

		Size++;
	}

	template<typename T>
	T& List<T>::operator[](const int index)
	{
		/* временный объект current который отвечает за в какой конкретном элементе мы сейчас находимся чтобы проверить адрес следующего элемента */
		Node<T>* current = this->head;
		int counter = 0;//счетчик (в каком конкретном элементе мы сейчас находимся по счету)

		/* счетчик будет рабоатть до тех пор пока указатель на текущий элемент не равен NULL */
		while(current != nullptr)
		{
			if(counter == index)//если счетчик равен тому индексу который мы хотим вызвать
			{
				return current->data;//у текущего элемента current заберем значение из поля data
			}

			//если мы не шали этот элемент по индексу ,то присваиваем в current адрес следующего элемента
			current=current->pNext;//спрашиваем у этойже переменной адрес следующей переменной
			counter++;
		}
		
	}


	template<typename T>
	void List<T>::pop_front()
	{
		Node<T> *temp=head;//временный объект который хранит адрес хеда(адрес 0 элемента)
		head=head->pNext;//в хед присвоим адрес адрес следующего элемента который идет за хед
		delete temp;//передаем указатель на наш бывший хед
		Size--;
	}

	template<typename T>
	void List<T>::clear()
	{
		while(Size)//для while Size=0 будет фолс(если переменная >0 или <0 то это тру)
 		{
			pop_front();
		}
	}

	//сначала должен создался объект в динамической памяти чтобы мы могли присвоить его в head
	//сначала передаем информацию из поля data который был во входящем параметре,а также указатель на текущий head
	template<typename T>
	void List<T>::push_front(T data)
	{
		//старыйадрес в конструкторе принимается 2м параметром
		head=new Node<T>(data,head);//для этого указателя(который *head) который будет хранить объект в динамической памяти ,вот для этого указателя создаем новый элемент типа Node и в конструктор пердем данные(data) которые будут храниться в этом элементе 
		size++;
	}

	template<typename T>
	void List<T>::insert(T value, int index)
	{

		if(index == 0)
		{
			push_fron(value);
		}
		else
		{
			Node<T>* previous = this->head;

			// -1 значит предыдущий
			for (int i=0; i<index-1; i++)//найти по индексу элемент предшествующий этому который мы хотим поместить этот элемент 
			{
				previous = previous->pNext;
			}

			Node<T>* newNode = new Node<T>(value, previous->pNext);//создаем объект типа Node и пердаем ему в конструктор данные и у предыдушего элемента берем поле pNext
			previous->pNext = newNode;//так где у  нашего предыдущего объекта относительно нашего элемета который мы добавляем , в его поле pNext добавляем адрес нашего текущего объекта 
			//эти 2 строчки можно записать в одну без буффера (newNode)
			//previous->pNext=new Node<T>(value, previous->pNext);
		}
	}


	template<typename T>
	void List<T>::removeAt(int index)
	{
		if(index == 0)
		{
			pop_fron();
		}
		else
		{
			Node<T>* previous = this->head;
			for (int i = 0; i<index-1; i++)
			{
				previous = previous->pNext;
			}
			
			Node<T>* toDelete = previous->pNext;
			previous->pNext = toDelete->pNext;

			delete toDelete;
			Size--;
		}
	}

void main()
{

	List<int> lst; // создаем список который будет хранить целые числа 

	lst.push_back(5);//вызываем у списка метод и передаем занчение
	lst.push_back(10);//это так создаеться новый элемент в списке
	lst.push_back(22);//это так создаеться новый элемент в списке

	cout<<lst.GetSize()<<endl;
	cout<<lst[1]<<endl;
cout<<endl;system("pause");
}
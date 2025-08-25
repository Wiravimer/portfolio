//���������� ����������� ������
#include <iostream>
using namespace std;


template<typename T>//������� ��������� �����
class List//����� ������
{
public:

	List();
	~List();

	void removeAt(int);//�������� �������� �� �������
	void insert(T, int);//���������� �������� �� �������
	void push_front(T);//�������� ������� � ������ ������
	void clear();//������� ���� ������
	/* pop_front(); ����� ���� ������������ ��� ������������ ������������ ������ (������� ���� ������) ������� �������� 2 ������ */
	void pop_front();//������� ����� 1� ������� 
	void push_back(T data);//���������� ��������(������) � ����� ������ push_back-��������� �����
	int GetSize(){return Size;}//��� "������" 

	T& operator[](const int index);//��� �������� �� ������(��������� ����� ������ ����� ���� ������� ��������)

private:

	//�� ������ Node ����� ������ ����� List � ��� �������������� � Node ����� ����� List
	template<typename T>//������� ��������� �����
	class Node//����� �������� ������ Node-����
	{
	public:
		Node* pNext;//����� ���������� ��������
		T data;
		
		Node(T data=T(), Node* pNext=nullptr)//����������� ������������ � ���������� �� ���������(�������� ��������� ������� �� ����� ���������� ������ ������ ��� �������� ������ �� ��������� �������)
		{
			this->data=data;
			this->pNext=pNext;
		}
	};

	//���������� ��������� ���� ,��� ��� �������� ������������ ������ ����� ���������� � ������������ ������
	Node<T>* head;//����� List ���� ���� �� ������ ������� ������  head-������
	int Size;//���������� ��������� � ������
};

//List:: ���������� � ������ ������ �������� �����/����������/����������
//<T> ��������� ��� ������
	template<typename T>
	List<T>::List()//����������� �� ���������
	{
		Size=0;
		head=nullptr;
	}

	template<typename T>
	List<T>::~List()//����������
	{
		clear();
	}

	template<typename T>
	void List<T>::push_back(T data)
	{
		//���������� ������ 1�� ��������
		if(head==nullptr)//��������� ������ �� ���� �������(���� ������ �� ����� ��������� �� NULL)
		{
			/* � ������������ ������ ������� ����� ������ ���� Node, 
			���� �������� ���� ������ � � head �������� ��������� �� ���� ����� ������*/

			head= new Node<T>(data);//������� ����� ������� Node � �������� � ����������� ������
		}
		//���������� ���������� ��������
		else
		{
			/* ������� ������� � ������� �� �������� �� ����������� ����� ������ head 
			� ������� � �������� ������ �������� ���� ������� ��������� �� ��������� ����� 
			���� ��� �� NULL ,�� �� ������ ��������� ���� ��������� ����� �������� �������� */

			Node<T>* current = this->head;//current � head ����������

			while(current->pNext != nullptr)//����������� � ���������� ��������
			{
				current=current->pNext;
			}

			/* ������� ����� �������(����� Node) � ����������� ����� ������������ ������ ���� ���� ��������� pNext 
			������� �������� �� NULL*/

			current->pNext = new Node<T>(data);
		}

		Size++;
	}

	template<typename T>
	T& List<T>::operator[](const int index)
	{
		/* ��������� ������ current ������� �������� �� � ����� ���������� �������� �� ������ ��������� ����� ��������� ����� ���������� �������� */
		Node<T>* current = this->head;
		int counter = 0;//������� (� ����� ���������� �������� �� ������ ��������� �� �����)

		/* ������� ����� �������� �� ��� ��� ���� ��������� �� ������� ������� �� ����� NULL */
		while(current != nullptr)
		{
			if(counter == index)//���� ������� ����� ���� ������� ������� �� ����� �������
			{
				return current->data;//� �������� �������� current ������� �������� �� ���� data
			}

			//���� �� �� ���� ���� ������� �� ������� ,�� ����������� � current ����� ���������� ��������
			current=current->pNext;//���������� � ������ ���������� ����� ��������� ����������
			counter++;
		}
		
	}


	template<typename T>
	void List<T>::pop_front()
	{
		Node<T> *temp=head;//��������� ������ ������� ������ ����� ����(����� 0 ��������)
		head=head->pNext;//� ��� �������� ����� ����� ���������� �������� ������� ���� �� ���
		delete temp;//�������� ��������� �� ��� ������ ���
		Size--;
	}

	template<typename T>
	void List<T>::clear()
	{
		while(Size)//��� while Size=0 ����� ����(���� ���������� >0 ��� <0 �� ��� ���)
 		{
			pop_front();
		}
	}

	//������� ������ �������� ������ � ������������ ������ ����� �� ����� ��������� ��� � head
	//������� �������� ���������� �� ���� data ������� ��� �� �������� ���������,� ����� ��������� �� ������� head
	template<typename T>
	void List<T>::push_front(T data)
	{
		//����������� � ������������ ����������� 2� ����������
		head=new Node<T>(data,head);//��� ����� ���������(������� *head) ������� ����� ������� ������ � ������������ ������ ,��� ��� ����� ��������� ������� ����� ������� ���� Node � � ����������� ������ ������(data) ������� ����� ��������� � ���� �������� 
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

			// -1 ������ ����������
			for (int i=0; i<index-1; i++)//����� �� ������� ������� �������������� ����� ������� �� ����� ��������� ���� ������� 
			{
				previous = previous->pNext;
			}

			Node<T>* newNode = new Node<T>(value, previous->pNext);//������� ������ ���� Node � ������� ��� � ����������� ������ � � ����������� �������� ����� ���� pNext
			previous->pNext = newNode;//��� ��� �  ������ ����������� ������� ������������ ������ ������� ������� �� ��������� , � ��� ���� pNext ��������� ����� ������ �������� ������� 
			//��� 2 ������� ����� �������� � ���� ��� ������� (newNode)
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

	List<int> lst; // ������� ������ ������� ����� ������� ����� ����� 

	lst.push_back(5);//�������� � ������ ����� � �������� ��������
	lst.push_back(10);//��� ��� ���������� ����� ������� � ������
	lst.push_back(22);//��� ��� ���������� ����� ������� � ������

	cout<<lst.GetSize()<<endl;
	cout<<lst[1]<<endl;
cout<<endl;system("pause");
}
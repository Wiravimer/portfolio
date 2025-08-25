# include <iostream>
# include <fstream>
# include <string>
using namespace std ;

//статус	  0		1	  2      3       4       5         6         7
enum Status { H, KEYWORD, ID, NUMBER, ASSIGN, COMPARE, DELIMITER, UNKNOWN };

//Текс который будет выводиться 
string NameSimbol[] =
					{ "H" ,      //0
					"KEYWORD" ,  //1 КЛЮЧЕВОЕ СЛОВО do while
					"ID" ,		 //2 ID  переменная или значение перменной
					"NUMBER" ,   //3 НОМЕР 0...9
					"ASSIGN" ,   //4 НАЗНАЧИТЬ :=
					"COMPARE" ,  //5 СРАВНИВАТЬ  > < =
					"DELIMITER" ,//6 ОГРАНИЧИТЕЛЬ  ;
					"UNKNOWN" }; //7 НЕИЗВЕСТНЫЙ  ,.sdg,.sdg;





void function ()
{
 char c;//куда будет считываться  символ
string slovo ;//куда будет считываться  слово из символ

ifstream fail ("1.txt") ; //открыть файл в режиме чтения

Status status_simbol = H;//начальный статус

fail>>c;//записываем первый симво в пеерменную 

	 while(!fail.eof())//.eof() определяет конец файла
	 {
		switch(status_simbol)
		{

			case H:
			{
				
				if(((c >= 'A') && (c <= 'Z')) ||((c >= 'a') && (c <= 'z')) || (c == '_'))
				{
					status_simbol = ID;
				}
				else if(((c >= '0') && (c <= '9')) )
				{
					status_simbol = NUMBER;
				}
				else if(c == ':')
				{
					status_simbol = ASSIGN;
				}
				else if((c==';')||(c=='(')||(c==')'))
				{
					status_simbol =DELIMITER;
				}

				else{
					status_simbol = UNKNOWN;
					}
			break;
			}// case H

//=======================================================================================================================================================
			case ID:
			{
				
				slovo+=c;
				fail>>c;

				while(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') &&(c <= 'z')) || (c == '_'))
				{
					if(slovo=="do" || slovo == "while")
					{
					cout<<slovo<<" KEYWORD"<<endl;
					slovo.clear();
					}
					//slovo+=c;
					fail>>c;

					if((c >= '0') && (c <= '9') )
					{
					slovo+=c;
					cout<<slovo<<" ID"<<endl;
					slovo.clear();
					status_simbol = NUMBER;
					}
				}

				
				if(slovo=="do" || slovo == "while")
				{
					cout<<slovo<<" KEYWORD"<<endl;
					slovo.clear();
					fail>>c;
					status_simbol = H;
				}
				else if (c==':')
				{	
					cout<<slovo<<" ID"<<endl;
					slovo.clear();
					status_simbol = ASSIGN;
				}
				else if((c==';')||(c=='(')||(c==')'))
				{
					cout<<slovo<<" ID"<<endl;
					slovo.clear();
				
					/*cout<<c<<" DELIMITER"<<endl;*/
					status_simbol = DELIMITER;
					/*	fail>>c;
					status_simbol = H;*/
				}
				else if(c=='<')
				{
					cout<<slovo<<" ID"<<endl;
					slovo.clear();

					//slovo+=c;
					fail>>c;
					if(c=='=')
					{
						slovo+=c;
						//status_simbol =COMPARE;
						cout<<slovo<<" COMPARE"<<endl;
						slovo.clear();
							fail>>c;
							status_simbol = H;
					}
					else{
							//cout<<slovo<<" COMPARE"<<endl;
							slovo.clear();
							fail>>c;
							status_simbol = H;
						}
				}
				else if(c=='=')
				{
					cout<<slovo<<" ID"<<endl;
					slovo.clear();

					slovo+=c;
					fail>>c;
					if(c=='>')
					{	
						slovo+=c;
						//status_simbol =COMPARE;
						cout<<slovo<<" COMPARE"<<endl;
							slovo.clear();
							fail>>c;
							status_simbol = H;
					}
					else{
							cout<<slovo<<" COMPARE"<<endl;
							slovo.clear();
							fail>>c;
							status_simbol = H;
						}
				}
				else{
					cout<<slovo<<" UNKNOWN"<<endl;
					slovo.clear();
					fail>>c;
					status_simbol = H;
					}
			break;
			}//case ID
			

			case ASSIGN:
			{
				slovo+=c;
				fail>>c;

				if(c == '=')
				{
					slovo+=c;
					cout<<slovo<<" ASSIGN"<<endl;
					slovo.clear();
					fail>>c;
					status_simbol = H;
				}
				else
					{
					cout<<slovo<<" UNKNOWN"<<endl;
					slovo.clear();
					fail>>c;
					status_simbol = H;
					}
			break;
			}// case ASSIGN 

			case UNKNOWN:
			{
				cout<<c<<" UNKNOWN"<<endl;
				slovo.clear();
				fail>>c;
				status_simbol = H;

			break;
			} // case UNKNOWN

			case DELIMITER:
			{
				cout<<c<<" DELIMITER"<<endl;
				fail>>c;
				status_simbol = H;
			break;
			} // case DELIMITER
							

			case NUMBER:
			{
				slovo+=c;
				fail>>c;

				while(((c >= '0') && (c <= '9')) || (c == '.') ||(c == '+') || (c == '-')||c=='e'||c=='E')
				{
					slovo+=c;
					fail>>c;
				}
					cout<<slovo<<" NUMBER"<<endl;
					slovo.clear();
					fail>>c;
					status_simbol = H;
			break;
			}//NUMBER
			
		}//switch

	 }//while(!fail.eof())
fail.close(); //закрыть файл 
}//void function ()




int main () 
{

	function();

	cout<<endl;system("pause");
 return 0 ;
} 
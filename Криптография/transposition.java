import java.util.ArrayList;
public class transposition1
{
    public static void main(String[] args)
	{
			String strText = "Карл у Клары украл кораллы";
			String strCipher = "";
			String strTemp = "";
			char tmp;
			 ArrayList<Character> masChar = new ArrayList<Character>();
			 ArrayList<Character> masCipher = new ArrayList<Character>();
			 ArrayList<Character> masTemp = new ArrayList<Character>();
			 ArrayList<Character> slovo = new ArrayList<Character>();
			 
			for(int i = 0; i<strText.length(); i++)masChar.add(strText.charAt(i));//преобразуем в массив сомволов
			
			//шифрование
			for (int i = 0; i < masChar.size(); i++) 
			{
				if (masChar.get(i) == ' ' || i == masChar.size()-1) 
				{
					if((slovo.size()/2) % 1 == 0)//проверям делиться ли слово ровно по пополам
					for(int j = 0; j < slovo.size()/2; j++){tmp = slovo.get(0); slovo.remove(0); slovo.add(tmp);}
					else for(int j = 0; j < (slovo.size()/2)+1; j++){tmp = slovo.get(0); slovo.remove(0); slovo.add(tmp);}
					
					for (int z = 0; z < slovo.size(); z++) masCipher.add(slovo.get(z));//добавляем измененое слово к шифру
					masCipher.add(' ');//добавляем пробел
					slovo.clear();//очищаем слово
				}
				else slovo.add(masChar.get(i));
			}
				for (int i = 0; i < masCipher.size(); i++) System.out.print(masCipher.get(i));//вывод
			
			System.out.println();
			masChar.clear();
			slovo.clear();
			//деширование
			for (int i = 0; i < masCipher.size(); i++) 
			{
				if (masCipher.get(i) == ' ' || i == masCipher.size()-1) 
				{
					if((slovo.size()/2) % 1 == 0)//проверям делиться ли шифр ровно по пополам
							for(int j = 0; j < slovo.size()/2; j++){tmp = slovo.get(0); slovo.remove(0); slovo.add(tmp);}
					else  for(int j = 0; j < (slovo.size()/2)-1; j++){tmp = slovo.get(0); slovo.remove(0); slovo.add(tmp);}
					
					for (int z = 0; z < slovo.size(); z++) masChar.add(slovo.get(z));//добавляем измененое слово к Тексту
					masChar.add(' ');//добавляем пробел
					slovo.clear();//очищаем слово
				}
				else slovo.add(masCipher.get(i));
			}
				for (int i = 0; i < masChar.size(); i++) System.out.print(masChar.get(i));//вывод
			
		
		
	System.out.println();
   }//main   
}//transposition






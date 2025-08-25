//cls && javac -encoding UTF-8 EP.java && java EP
import java.math.BigInteger;

public class monoalphabetic2
{	
	public static  String alphU ="АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
	public static  String alphD ="абвгдеёжзийклмнопрстуфхцчшщьыъэюя";
	public static  String alphC ="!@#$%^&*()-=\";:?_+/\\,.|><{}[]`~'";
	
    public static void main(String[] args)
	{
		String strText = "Карл у Клары украл кораллы";
		String strCiphr = "";
		
		strText = strText.replaceAll("\\s+","");//убираем пробелы
		for(int i = 0; i < strText.length(); i++) strCiphr = strCiphr+alphC.charAt(find(strText.charAt(i)));
		System.out.println(strCiphr );
		
		strText = "";
		for(int i = 0; i < strCiphr.length(); i++) strText = strText+alphU.charAt(find(strCiphr.charAt(i)));
		System.out.println(strText);
		
		
	System.out.println();
   }//main   
   
public static  int find(char symbol)//возвращает порядковый номер в алфавите
{
	for(int i = 0; i < alphU.length(); i++)
		if(symbol == alphU.charAt(i) || symbol == alphD.charAt(i) || symbol == alphC.charAt(i))
			return i;
	return -1;
}
   
}//